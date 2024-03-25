#include "simulation.h"
#include "message.h"
#include "lifeform.h"
#include "shape.h"
#include "constantes.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
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
        total_segments = corail_actuel.getNbSeg();
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
        corail_actuel.addSeg(data);
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
    // Collisions

    // Unicité des identificateurs de coraux
    int id = corail.getId();
    if (id_corail_existe(id))
    {
        cout << message::lifeform_duplicated_id(id);
        std ::exit(EXIT_FAILURE) ;
    }
    corails.push_back(corail);
}

bool Simulation::id_corail_existe(int id)
{
    for (const auto& corail : corails)
    {
        if (id == corail.getId())
        {
            return true;
        }
    }
    return false;
}

void Simulation::ajouter_scavenger(Scavenger scavenger)
{
    int id = scavenger.getCible();
    if (scavenger.getEtat() == MANGE and !id_corail_existe(id))
    {
        cout << message::lifeform_invalid_id(id);
        std ::exit(EXIT_FAILURE) ;
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
    exit(0);
}