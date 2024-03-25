#ifndef LIFEFORM_H
#define LIFEFORM_H
#include "shape.h"
#include <vector>
#include <sstream>

class Lifeform
{
public:
    // Nécessaire pour initialiser un Corail vide
    Lifeform() = default;
    Lifeform(int age);

protected:
    int age;
    void erreur_lecture(std::string type);
    void test_age(int age);

};

class Algue : Lifeform
{
public:
    Algue(std::istringstream &data);

private:
    Cercle cercle;
};

class Corail : Lifeform
{
public:
    // Nécessaire pour initialiser corail_actuel dans decodage_line de Lifeform
    Corail() = default;
    Corail(std::istringstream &data);
    void test_longueur_segment(double seg);
    void test_angle(double angle);
    int getNbSeg() const { return nb_seg; };
    int getId() const { return id; };
    std::vector<Segment> getSegs() const { return segs; };
    void addSeg(std::istringstream &data);

private:
    Carre base;
    int id;
    int statut;
    int sens_rot;
    int st_dev;
    int nb_seg;
    std::vector<Segment> segs;
};

class Scavenger : Lifeform
{
public:
    Scavenger(std::istringstream &data);
    int getEtat() const { return etat; };
    int getCible() const { return id_cible; };

private:
    Cercle cercle;
    int etat;
    int id_cible;
};

#endif