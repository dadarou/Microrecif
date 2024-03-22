#include "simulation.h"
#include "message.h"
#include "lifeform.h"
#include "shape.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

void Lecture(string nom_fichier){
    string ligne;
    ifstream l_fichier(nom_fichier);

    if(!l_fichier.fail()){
        while(getline(l_fichier >> ws, ligne )){
            if(ligne[0] == '#'){
                continue;
            }// le getline donne un bool vrai si la ligne n'est pas la derniere et envoie la ligne dans la variable ligne
            Filtrage(ligne);
        }
    }else{
        exit(EXIT_FAILURE); //si l'ouverture du fichier marche pas on arrete le code
    }
    l_fichier.close();
}

void Filtrage(string ligne){
    istringstream data(ligne); //convertit la ligne en quelque chose qu'on peut tratier
    enum Etat_decodage {Nb0, Algue, Nb1, Corail, Nb2, Scavenger};
    static int etat(Nb0);
    static int total(0);

    switch(etat){
        case Nb0:
            if(!(data >> total)){
                //appel de la fonction erreru car le nombre d'algue n'est pas bien précisé
                exit(EXIT_FAILURE);
            }
            if(total==0){
                etat = Nb1;
            }else{
                etat = Algue;
            }
            break;

        case Algue:
            Decodage_Algue(data);
            //changer etat
            
        case Nb1:
            if(!(data >> total)){
                //appel de la fonction erreru car le nombre de Corail n'est pas bien précisé
                exit(EXIT_FAILURE);
            }
            if(total==0){
                etat = Nb2;
            }else{
                etat = Corail;
            }
            break;

        case Corail:


        case Nb2:
            if(!(data >> total)){
                //appel de la fonction erreru car le nombre de Scavenger n'est pas bien précisé
                exit(EXIT_FAILURE);
            }
            if(total==0){
                //fin de la lecture du fichier ;
            }else{
                etat = Scavenger;
            }
            break;
            
        case Scavenger:

    }
}