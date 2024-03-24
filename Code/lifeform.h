#ifndef LIFEFORM_H
#define LIFEFORM_H
#include "shape.h"
#include <sstream>
using namespace std;

class Lifeform
{
public:
    // Nécessaire pour initialiser un Corail vide
    Lifeform() = default;
    Lifeform(int age);

protected:
    int age;
};

class Algue : Lifeform
{
public:
    Algue(istringstream &data);

private:
    Cercle cercle;
};

class Corail : Lifeform
{
public:
    // Nécessaire pour initialiser corail_actuel dans decodage_line de Lifeform
    Corail() = default;
    Corail(istringstream &data);
    // Corail(double x, double y, int age, int id,
    //        int statut, int sens_rot, int st_dev, int nb_seg);
    int getNbSeg() const { return nb_seg; };
    void addSeg(istringstream &data);

private:
    Carre base;
    int id;
    int statut;
    int sens_rot;
    int st_dev;
    int nb_seg;
    vector<Segment> segs;
};

class Scavenger : Lifeform
{
public:
    // Scavenger(double x, double y, int age, int r, int etat, int id_cible);
    Scavenger(istringstream &data);

private:
    Cercle cercle;
    int etat;
    int id_cible;
};

#endif