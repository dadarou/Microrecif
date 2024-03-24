#include "lifeform.h"
#include "shape.h"
#include "constantes.h"
#include <sstream>
#include <iostream>
#include <vector>
using namespace std;

Lifeform::Lifeform(int age)
    : age(age) {}

// Algue::Algue(double x, double y, int age)
//     : Lifeform(x, y, age){}

// Corail::Corail(double x, double y, int age, int id, int statut, int sens_rot, int st_dev, int nb_seg)
//     : Lifeform(x, y, age), identite(id), statut(statut), sens_rotation(sens_rot), st_developpement(st_dev), nb_segment(nb_seg){}

// Scavenger::Scavenger(double x, double y, int age, int r, int etat, int id_cible)
//     : Lifeform(x, y, age), rayon(r), etat(etat), identite_cible(id_cible){}

Algue::Algue(istringstream &data)
{
    double pos_x, pos_y;
    if (!(data >> pos_x >> pos_y >> age))
    {
        // Les données de l'algue sont invalides.
        cout << "Error reading algue data" << endl;
        exit(EXIT_FAILURE);
    }
    cercle = Cercle(pos_x, pos_y, r_alg);

    // TODO: Detection d'erreurs
    // Test_Lifeform(pos_x, pos_y, age);
}

Corail::Corail(istringstream &data)
{
    double pos_x, pos_y;
    if (!(data >> pos_x >> pos_y >> age >> id >> statut >> sens_rot >> st_dev >> nb_seg))
    {
        // Les données du corail sont invalides.
        cout << "Error reading coral data" << endl;
        exit(EXIT_FAILURE);
    }
    base = Carre(pos_x, pos_y, d_cor);

    // TODO: Detection d'erreurs
    // Test_Lifeform(pos_x, pos_y, age);
    // Test_Corail();
}

void Corail::addSeg(istringstream &data)
{
    double angle, length;
    if (!(data >> angle >> length))
    {
        // Les données du segment sont invalides.
        cout << "Error reading segment data" << endl;
        exit(EXIT_FAILURE);
    }

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
    if (!(data >> pos_x >> pos_y >> age >> rayon >> etat >> id_cible))
    {
        // Les données du scavenger sont invalides.
        cout << "Error reading scavenger data" << endl;
        exit(EXIT_FAILURE);
    }
    cercle = Cercle(pos_x, pos_y, rayon);

    // TODO: Detection d'erreurs
    // Test_Lifeform(pos_x, pos_y, age);
    // Test_Scavenger();
}