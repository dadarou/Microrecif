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
    cout << "Error reading " << type << endl;
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
    {
        if (!(data >> id_cible))
            erreur_lecture("id_cible");
    }


    cercle = Cercle(pos_x, pos_y, rayon);

    // TODO: Detection d'erreurs
    // Test_Lifeform(pos_x, pos_y, age);
    // Test_Scavenger();
}


/* 
 * Tests à effectuer: 
 * Daniel:
 * [x] unicité des identificateurs de coraux 
 * existence d’un corail identifié avec l’identificateur mémorisé par un scavenger dans l’état MANGE 
 * intersection/superposition des coraux
 * 
 * Joshua:
 * l’age est strictement positif 
 * la longueur des segments est comprise dans [l_repro-l_seg_interne, l_repro[ 
 * l’angle des segments est compris dans [-π, π] 
 * le rayon des scavengers est compris dans [r_sca, r_sca_repro[ 
 * inclusion des centres des algues et scavengers, et la base des coraux dans le domaine [1, max-1]
 * inclusion de la base des segments de coraux et de l’extrémité du dernier segment dans ]epsil_zero, max – epsil_zero[
*/
