#include "lifeform.h"
#include "shape.h"
#include <sstream>
using namespace std;

Lifeform::Lifeform(double x, double y, int age){
    pos_x = x;
    pos_y = y;
    age = age;
}

Algue::Algue(double x, double y, int age)
    : Lifeform(x, y, age){}

Corail::Corail(double x, double y, int age, int id, int statut, int sens_rot, int st_dev, int nb_seg)
    : Lifeform(x, y, age), identite(id), statut(statut), sens_rotation(sens_rot), st_developpement(st_dev), nb_segment(nb_seg){}

Scavenger::Scavenger(double x, double y, int age, int r, int etat, int id_cible)
    : Lifeform(x, y, age), rayon(r), etat(etat), identite_cible(id_cible){}

void Test_Lifeform(double x, double y, int age){
    //il manque verif position
    if (age <= 0){
        //message d'erreur
        exit(EXIT_FAILURE);
    }
}

void Test_Corail(){
    
}

void Test_Scavenger(){
    
}
//est ce que faudrais pas faire des méthode à la place ?

void Decodage_Algue(istringstream& data){
    double pos_x;
    double pos_y;
    int age;
    if (!(data >> pos_x >> pos_y >> age)){
        //gestion erreur lecture
    }
    Test_Lifeform(pos_x, pos_y, age);
    Algue algue(pos_x, pos_y, age);
    //inclusion dans vector qui est donné avec &
    //ca va pas causer des porblemes la création d'une algue comme ca ?
    //ca va faire une copie dans le vectore ou mettre l'élément d'origine
}

void Decodage_Corail(istringstream& data){
    double pos_x;
    double pos_y;
    int age;
    int id;
    int statut;
    int sens_rot;
    int st_dev;
    int nb_seg;

    if (!(data >> pos_x >> pos_y >> age >> id >> statut >> sens_rot >> st_dev >> nb_seg)){
        //gestion erreur lecture
    }
    Test_Lifeform(pos_x, pos_y, age);
    Test_Corail();
    Corail corail(pos_x, pos_y, age, id, statut, sens_rot, st_dev, nb_seg);
    //les segment sont sur des lignes différentes
    //on doit faire une fonctio supp pour les seg

}

void Decodage_Scavenger(istringstream& data){
    double pos_x;
    double pos_y;
    int age;
    int r;
    int etat;
    int id_cible;

    if (!(data >> pos_x >> pos_y >> age >> r >> etat >> id_cible)){
        //gestion erreur lecture
    }
    Test_Lifeform(pos_x, pos_y, age);
    Test_Scavenger();
    Scavenger scavenger(pos_x, pos_y, age, r, etat, id_cible);
    //les segment sont sur des lignes différentes
    //on doit faire une fonctio supp pour les seg

}


//creation de vector pour chaque entité pour stockées les entitées qu'on vq créé
//Passer par référence les vector dans la fonction 

//ou initialiser les vector et comment les intégrer
//on pourrati creer un tableau lifeform qui contient un tableau pour chaque entité
//ensuite on retourne ce grand tableau

//donner un autre nom que data
//prendre en comptes le decodage de segments