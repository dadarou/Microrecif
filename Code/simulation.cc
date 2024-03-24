#include "simulation.h"
#include "message.h"
#include "lifeform.h"
#include "shape.h"
#include <iostream>
#include <fstream> // Je crois pas que c'est nesessaire de l'include
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
        // Getline donne un bool vrai si la ligne n'est pas la dernière et
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
    // Convertit la ligne en quelque chose qu'on peut traiter: string -> stream
    istringstream data(ligne);
    enum Etat_decodage
    {
        EtatNbAlgues,
        EtatAlgue,
        EtatNbCoraux,
        EtatCorail,
        EtatSegment,
        EtatNbScavengers,
        EtatScavenger
    };
    static int etat(EtatNbAlgues);
    static int compteur_entite(0);
    static int total_entite(0);

    static Corail corail_actuel;
    static int compteur_segments(0);
    static int total_segments(0);

    switch (etat)
    {
    case EtatNbAlgues:
    {
        if (!(data >> total_entite))
        {
            // Le nombre d'algue est invalide..
            cout << "Error reading nbAlg" << endl;
            exit(EXIT_FAILURE);
        }
        if (total_entite == 0)
        {
            etat = EtatNbCoraux;
        }
        else
        {
            etat = EtatAlgue;
        }
    }
    break;

    case EtatAlgue:
    {
        // Decodage_Algue(data);
        Algue algue(data);
        algues.push_back(algue);

        ++compteur_entite;
        if (compteur_entite == total_entite)
        {
            etat = EtatNbCoraux;
        }
    }
    break;

    case EtatNbCoraux:
    {
        if (!(data >> total_entite))
        {
            // Le nombre de coraux est invalide.
            cout << "Error reading nbCor" << endl;
            exit(EXIT_FAILURE);
        }
        compteur_entite = 0;
        if (total_entite == 0)
        {
            etat = EtatNbScavengers;
        }
        else
        {
            etat = EtatCorail;
        }
    }
    break;

    case EtatCorail:
    {
        corail_actuel = Corail(data);
        total_segments = corail_actuel.getNbSeg();

        if (total_segments == 0)
        {
            corails.push_back(corail_actuel);
            etat = EtatCorail;
        }
        else
        {
            etat = EtatSegment;
        }

        ++compteur_entite;
        if (compteur_entite == total_entite)
        {
            etat = EtatNbScavengers;
        }
    }
    break;

    case EtatSegment:
    {
        corail_actuel.addSeg(data);

        ++compteur_segments;
        if (compteur_segments == total_segments)
        {
            etat = EtatCorail;
        }
    }
    break;

    case EtatNbScavengers:
    {
        if (!(data >> total_entite))
        {
            // Le nombre de scavengers est invalide.
            cout << "Error reading nbSca" << endl;
            exit(EXIT_FAILURE);
        }
        compteur_entite = 0;

        if (total_entite == 0)
        {
            // Fin de la lecture du fichier
            cout << message::success();
            exit(0);
        }
        else
        {
            etat = EtatScavenger;
        }
    }
    break;

    case EtatScavenger:
    {
        // Decodage_Scavenger(data);
        Scavenger scavenger(data);
        scavengers.push_back(scavenger);

        ++compteur_entite;
        if (compteur_entite == total_entite)
        {
            // Fin de la lecture du fichier
            cout << message::success();
            exit(0);
        }
    }
    break;
    }
}