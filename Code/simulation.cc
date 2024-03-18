#include "simulation.h"
#include "message.h"
#include "lifeform.h"
#include "shape.h"
#include <iostream>
#include <fstream>
using namespace std;

void Lecture(string nom_fichier){
    enum Avancement {x0, x1, x2, x3, x4};
    int position(x0);
    int compteur(0);
    string ligne;
    bool donnees;

    ifstream l_fichier(nom_fichier);
    if(!l_fichier.fail()){
        while(getline(l_fichier >> ws, ligne )){
            if(ligne[0] == '#'){
                continue;
            }
            istringstream data(ligne); //convertit la ligne en quelque chose qu'on peut tratier
            while(data >> donnees){
                //data>>donnees est pareil qu'un cin>> mais pour les fichier 
                cout << donnees;
                //appel des fonctions vérifiant les erreurs 
            }
        } // le getline donne un bool vrai si la ligne n'est pas la derniere et envoie la ligne dans la variable ligne

    } else{
        exit(EXIT_FAILURE); //j'ai copie de boulic mais jsp comment le exit marche
    }
    l_fichier.close()
}