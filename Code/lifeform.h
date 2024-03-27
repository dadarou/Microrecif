#ifndef LIFEFORM_H
#define LIFEFORM_H

#include <vector>
#include <sstream>
#include "shape.h"
#include "constantes.h"
    
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
    void test_pos(double x, double y);

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
    void test_longueur_segment(int id, double seg);
    void test_angle(int id, double angle);
    int getNbSeg() const { return nb_seg; };
    int getId() const { return id; };
    std::vector<Segment> getSegs() const { return segs; };
    void addSeg(std::istringstream &data, int id);
    void inclusion_segment(int id, S2d base);

private:
    Carre base;
    int id;
    Status_cor statut;
    Dir_rot_cor sens_rot;
    Status_dev st_dev;
    int nb_seg;
    std::vector<Segment> segs;
};

class Scavenger : Lifeform
{
public:
    Scavenger(std::istringstream &data);
    Status_sca getEtat() const { return etat; };
    int getCible() const { return id_cible; };
    void test_rayon(double r);

private:
    Cercle cercle;
    Status_sca etat;
    int id_cible;
};

#endif