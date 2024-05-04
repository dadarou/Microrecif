// lifeform.h : Entités de la simulation
// Auteurs : Daniel Roulin & Joshua Hurlimann
// Version 2

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
    Lifeform(unsigned int a) : age(a){};
    void update_age();
    virtual void dessin() = 0;
    unsigned int get_age() const { return age; };

protected:
    unsigned int age;
    void erreur_lecture(std::string type, bool &erreur);
    void test_age(unsigned int age, bool &erreur);
    void test_pos(double x, double y, bool &erreur);
};

class Algue : public Lifeform
{
public:
    Algue(std::istringstream &data, bool &erreur);
    Algue(double pos_x, double pos_y)
     : Lifeform(1), cercle(pos_x, pos_y, r_alg){};
    void dessin() override;
    std::string ecriture();

private:
    Cercle cercle;
};

class Corail : public Lifeform
{
public:
    // Nécessaire pour initialiser corail_actuel dans decodage_line de Lifeform
    Corail() = default;
    Corail(std::istringstream &data, bool &erreur);
    void add_seg(std::istringstream &data, int id, bool &erreur);
    void test_longueur_segment(int id, unsigned int l_seg, bool &erreur);
    void test_angle(int id, double angle, bool &erreur);
    void inclusion_segment(int id, S2d base, bool &erreur);
    void dessin() override;
    std::string ecriture();
    int get_nb_seg() const { return nb_seg; };
    int get_id() const { return id; };
    std::vector<Segment> get_segs() const { return segs; };

private:
    Carre base;
    int id;
    Status_cor statut;
    Dir_rot_cor sens_rot;
    Status_dev st_dev;
    int nb_seg;
    std::vector<Segment> segs;
};

class Scavenger : public Lifeform
{
public:
    Scavenger(std::istringstream &data, bool &erreur);
    void test_rayon(unsigned int r, bool &erreur);
    void dessin() override;
    std::string ecriture();
    Status_sca get_etat() const { return etat; };
    int get_cible() const { return id_cible; };

private:
    Cercle cercle;
    Status_sca etat;
    int id_cible;
};

#endif