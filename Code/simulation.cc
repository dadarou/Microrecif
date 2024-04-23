// simulation.cc : Gestion de la simulation
// Auteurs : Daniel Roulin & Joshua Hurlimann
// Version 1 

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "simulation.h"
#include "message.h"
#include "lifeform.h"
#include "shape.h"
#include "constantes.h"
using namespace std;

void Simulation::lecture(string nom_fichier)
{
    string ligne;
    ifstream l_fichier(nom_fichier);

    if (!l_fichier.fail())
    {
        // getline donne un bool vrai si la ligne n'est pas la dernière et
        // envoie la ligne dans la variable ligne.
        while (getline(l_fichier >> ws, ligne))
        {
            if (ligne[0] == '#')
            {
                continue;
            }
            decodage(ligne);
        }
    }
    else
    {
        // Si l'ouverture du fichier marche pas on arrête le code.
        cout << "Error opening file" << endl;
        exit(EXIT_FAILURE);
    }
    l_fichier.close();
}

// Fonction appelée pour chaque ligne.
void Simulation::decodage(string ligne)
{
    istringstream data(ligne);
    enum Etat_decodage {NbAlg, Alg, NbCor, Cor, Seg, NbSca, Sca};
    static int etat(NbAlg);
    static int compteur_entite(0);
    static int total_entite(0);
    static Corail corail_actuel;
    static int compteur_segments(0);
    static int total_segments(0);

    switch (etat)
    {
    case NbAlg:
    {
        total_entite = read_nb(data, "nbAlg");
        if (total_entite == 0) etat = NbCor;
        else etat = Alg;
    }
    break;
    case Alg:
    {
        ++compteur_entite;
        Algue algue(data);
        ajouter_algue(algue);
        if (compteur_entite == total_entite) etat = NbCor;
    }
    break;
    case NbCor:
    {
        compteur_entite = 0;
        total_entite = read_nb(data, "nbCor");
        if (total_entite == 0) etat = NbSca;
        else etat = Cor;
    }
    break;
    case Cor:
    {
        ++compteur_entite;
        compteur_segments = 0;
        corail_actuel = Corail(data);
        total_segments = corail_actuel.get_nb_seg();
        if (total_segments == 0)  
        {
            ajouter_corail(corail_actuel);
            if (compteur_entite == total_entite) etat = NbSca;   
        }
        else etat = Seg;
    }
    break;
    case Seg:
    {
        ++compteur_segments;
        corail_actuel.add_seg(data, corail_actuel.get_id());
        if (compteur_segments == total_segments) 
        {
            ajouter_corail(corail_actuel);
            if (compteur_entite == total_entite) etat = NbSca; 
            else etat = Cor; 
        }
    }
    break;
    case NbSca:
    {
        compteur_entite = 0;
        total_entite = read_nb(data, "nbSca");
        if (total_entite == 0) succes_lecture();
        else etat = Sca;
    }
    break;
    case Sca:
    {
        ++compteur_entite;
        Scavenger scavenger(data);
        ajouter_scavenger(scavenger);
        if (compteur_entite == total_entite) succes_lecture();
    }
    break;
    }
}

void Simulation::ajouter_algue(Algue algue)
{
    algues.push_back(algue);
}

void Simulation::ajouter_corail(Corail corail)
{
    // Unicité de l'identificateur de coraux
    int id = corail.get_id();
    if (id_corail_existe(id))
    {
        cout << message::lifeform_duplicated_id(id);
        exit(EXIT_FAILURE);
    }

    corails.push_back(corail);

    test_intersection_coraux(corail);
}

// Intersections intra ou inter corail
// L'agorithme actuel est en O(n^3)
// On pourrait l'optimiser mais ce n'est pas demandé pour l'instant ¯\_(ツ)_/¯
void Simulation::test_intersection_coraux(Corail corail)
{
    auto segs = corail.get_segs();
    for (unsigned int i = 0; i < segs.size(); i++) 
    {
        Segment seg = segs[i];
        for (auto& autre_cor : corails)
        {
            auto other_segs = autre_cor.get_segs();
            for (unsigned int j = 0; j < other_segs.size(); j++) 
            {
                Segment autre_seg = other_segs[j];
                int id1 = corail.get_id();
                int id2 = autre_cor.get_id();
                // On ne teste pas l'intersection entre le même segments ou des 
                // segments consecutifs d'un même corail.
                bool consec = (id1 == id2) && (i == j || i == j + 1 || i == j - 1);
                if (!consec && seg.intersection(autre_seg, true))
                {
                    cout << message::segment_collision(id1, i, id2, j);
                    exit(EXIT_FAILURE);
                }
            }
        }
    }
}

bool Simulation::id_corail_existe(int id)
{
    for (auto& corail : corails)
    {
        if (id == corail.get_id())
        {
            return true;
        }
    }
    return false;
}

void Simulation::ajouter_scavenger(Scavenger scavenger)
{
    // Test d'existence du corail mémorisé par le scavenger
    int id = scavenger.get_cible();
    if (scavenger.get_etat() == EATING && !id_corail_existe(id))
    {
        cout << message::lifeform_invalid_id(id);
        exit(EXIT_FAILURE);
    }
    scavengers.push_back(scavenger);
}

int Simulation::read_nb(istringstream &data, string section)
{
    int nb;
    if (!(data >> nb) or nb < 0)
    {
        cout << "Error reading " << section << endl;
        exit(EXIT_FAILURE);
    }
    return nb;
}

void Simulation::succes_lecture()
{
    cout << message::success();
    // exit(0);
}

void Simulation::sauvegarde(string nom_fichier)
{
    ofstream fichier(nom_fichier);
    if(!fichier.fail())
    {
        fichier << algues.size() << endl;
        for (auto& algue : algues)
        {
            fichier << "    " << algue.ecriture() << endl;
        }

        fichier << corails.size() << endl;
        for (auto& corail : corails)
        {
            fichier << "    " << corail.ecriture() << endl;
            for (auto& segment : corail.get_segs())
            {
                fichier << "        " << segment.ecriture() << endl;
            }
        }

        fichier << scavengers.size() << endl;
        for (auto& scavenger : scavengers)
        {
            fichier << "    " << scavenger.ecriture() << endl;
        }
    }
    fichier.close();
}

void Simulation::dessin()
{
    for (auto& algue : algues)
    {
        algue.dessin();
    }
    for (auto& corail : corails)
    {
        corail.dessin();
    }
    for (auto& scavenger : scavengers)
    {
        scavenger.dessin();
    }
}