// simulation.cc : Gestion de la simulation
// Auteurs : Daniel Roulin (30%) & Joshua Hurlimann (70%)
// Version 2 

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <random>
#include "simulation.h"
#include "message.h"
#include "lifeform.h"
#include "shape.h"
#include "constantes.h"
using namespace std;

void Simulation::lecture(string nom_fichier)
{
    reset();

    string ligne;
    ifstream l_fichier(nom_fichier);

    if (!l_fichier.fail())
    {
        while (getline(l_fichier >> ws, ligne))
        {
            if (ligne[0] == '#')
            {
                continue;
            }
            decodage(ligne);
            if (lecture_error)
            {
                reset();
                break;
            }
            if (lecture_finie)
            {
                cout << message::success();
                break;
            }
        }
    }
    else
    {
        cout << "Error opening file" << endl;
        reset();
    }
    l_fichier.close();
}

// Fonction appelée pour chaque ligne.
void Simulation::decodage(string ligne)
{
    istringstream data(ligne);

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
        Algue algue(data, lecture_error);
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
        corail_actuel = Corail(data, lecture_error);
        if (lecture_error) return;
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
        corail_actuel.add_seg(data, corail_actuel.get_id(), lecture_error);
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
        if (total_entite == 0) lecture_finie = true;
        else etat = Sca;
    }
    break;
    case Sca:
    {
        ++compteur_entite;
        Scavenger scavenger(data, lecture_error);
        ajouter_scavenger(scavenger);
        if (compteur_entite == total_entite) lecture_finie = true;
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
        lecture_error = true;
        return;
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
                    lecture_error = true;
                    return;
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
        lecture_error = true;
        return;
    }
    scavengers.push_back(scavenger);
}

int Simulation::read_nb(istringstream &data, string section)
{
    int nb;
    if (!(data >> nb) or nb < 0)
    {
        cout << "Error reading " << section << endl;
        lecture_error = true;
        return 0;
    }
    return nb;
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

template <typename T>
void Simulation::mort_naturelle(vector<T> &entites, unsigned int max_age)
{
    for (unsigned int i = 0; i < entites.size(); i++) 
    {
        T& entite = entites[i];
        entite.update_age();
        if (entite.get_age() >= max_age)
        {
            swap(entite, entites.back());
            entites.pop_back();
            i--;
        }
    }
}

void Simulation::step()
{
    nb_sim += 1;

    mort_naturelle(algues, max_life_alg);

    if (naissance_algue)
    {
        spawn_algue();
    }

    mort_naturelle(corails, max_life_cor);

    mort_naturelle(scavengers, max_life_sca);
}

void Simulation::spawn_algue()
{
    double p(alg_birth_rate);
    bernoulli_distribution b(p);
    if (b(random_engine))
    {
        uniform_int_distribution<unsigned> u(1, dmax-1);
        double x = u(random_engine);
        double y = u(random_engine);
        Algue nouvelle_algue(x, y);
        ajouter_algue(nouvelle_algue);
    }
}

void Simulation::reset()
{
    algues.clear();
    corails.clear();
    scavengers.clear();
    random_engine.seed(1);

    nb_sim = 0;
    naissance_algue = false;

    lecture_finie = false;
    lecture_error = false;

    etat = NbAlg;
    compteur_entite = 0;
    total_entite = 0;
    compteur_segments = 0;
    total_segments = 0;
}