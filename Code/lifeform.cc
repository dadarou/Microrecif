#include "lifeform.h"
#include "shape.h"
#include <sstream>
using namespace std;

Lifeform::Lifeform(int age, double x, double y){
    age = age;
    pos_x = x;
    pos_y = y;
}

Algue::Algue(int age, double x, double y)
    : Lifeform(age, x, y){}

Corail::Corail(int age, double x, double y, int statut, int sens_rot, int st_dev)
    : Lifeform(age, x, y), statut(statut), sens_rotation(sens_rot), st_developpement(st_dev){}

Scavenger::Scavenger(int age, double x, double y, int etat)
    : Lifeform(age, x, y), etat(etat) {}

void Test_Lifeform(int age){
    // Bla bla test
    if (age <= 0){
        //message d'erreur
        exit(EXIT_FAILURE);
    }else{
        //initialisation de l'âge
    }
}

void Test_Corail(){
    
}

void Test_Scavenger(){
    
}
//est ce que faudrais pas faire des méthode à la place ?

void Decodage_Algue(istringstream& data){
    //la faire le decodage de la ligne donné en paramètre

}



//creation de vector pour chaque entité pour stockées les entitées qu'on vq créé
//Passer par référence les vector dans la fonction 

//donner un autre nom que data
//faire toutes les fonctions decodages