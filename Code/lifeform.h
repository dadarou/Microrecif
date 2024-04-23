// lifeform.h : Entités de la simulation
// Auteurs : Daniel Roulin & Joshua Hurlimann
// Version 1 

#ifndef LIFEFORM_H
#define LIFEFORM_H

#include <vector>
#include <sstream>
#include <string>
#include "shape.h"
#include "constantes.h"
    
class Lifeform
{
public:
    // Nécessaire pour initialiser un Corail vide
    Lifeform() = default;
    Lifeform(int age);
    virtual void dessin() = 0;

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
    void dessin() override;
    std::string ecriture();

private:
    Cercle cercle;
};

class Corail : Lifeform
{
public:
    // Nécessaire pour initialiser corail_actuel dans decodage_line de Lifeform
    Corail() = default;
    Corail(std::istringstream &data);
    void add_seg(std::istringstream &data, int id);
    void test_longueur_segment(int id, unsigned int l_seg);
    void test_angle(int id, double angle);
    void inclusion_segment(int id, S2d base);
    int get_nb_seg() const { return nb_seg; };
    int get_id() const { return id; };
    std::vector<Segment> get_segs() const { return segs; };
    void dessin() override;
    std::string ecriture();

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
    void test_rayon(unsigned int r);
    Status_sca get_etat() const { return etat; };
    int get_cible() const { return id_cible; };
    void dessin() override;
    std::string ecriture();

private:
    Cercle cercle;
    Status_sca etat;
    int id_cible;
};

#endif