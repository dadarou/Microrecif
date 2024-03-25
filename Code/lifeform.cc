#include "lifeform.h"
#include "shape.h"
#include "constantes.h"
#include <sstream>
#include <iostream>
#include <vector>
using namespace std;

Lifeform::Lifeform(int age)
    : age(age) {}

void Lifeform::erreur_lecture(string type)
{
    cout << "Error reading " << type << " data" << endl;
    exit(EXIT_FAILURE);   
}

Algue::Algue(istringstream &data)
{
    double pos_x, pos_y;
    if (!(data >> pos_x >> pos_y >> age))
        erreur_lecture("algue");
    cercle = Cercle(pos_x, pos_y, r_alg);

    // TODO: Detection d'erreurs
    // Test_Lifeform(pos_x, pos_y, age);
}

Corail::Corail(istringstream &data)
{
    double pos_x, pos_y;
    if (!(data >> pos_x >> pos_y >> age >> id 
               >> statut >> sens_rot >> st_dev >> nb_seg))
        erreur_lecture("coral");
    base = Carre(pos_x, pos_y, d_cor);

    // TODO: Detection d'erreurs
    // Test_Lifeform(pos_x, pos_y, age);
    // Test_Corail();
}

void Corail::addSeg(istringstream &data)
{
    double angle, length;
    if (!(data >> angle >> length))
        erreur_lecture("segment");

    S2d base_pos;
    int size = segs.size();
    if (size == 0)
    {
        // La base du premier segment est la position du corail.
        base_pos = base.getPos();
    }
    else
    {
        // Sinon, c'est l’extrémité du segment précédent.
        base_pos = segs[size - 1].extremity();
    }
    segs.push_back(Segment(base_pos, angle, length));
}

Scavenger::Scavenger(istringstream &data)
{
    double pos_x, pos_y, rayon;
    if (!(data >> pos_x >> pos_y >> age >> rayon >> etat))
        erreur_lecture("scavenger");
    if (etat == MANGE)
        if (!(data >> id_cible))
            erreur_lecture("scavenger");
            
    cercle = Cercle(pos_x, pos_y, rayon);

    // TODO: Detection d'erreurs
    // Test_Lifeform(pos_x, pos_y, age);
    // Test_Scavenger();
}