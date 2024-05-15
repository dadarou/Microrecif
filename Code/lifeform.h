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

constexpr unsigned l_nv_seg(l_repro - l_seg_interne);

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
    S2d get_pos() { return cercle.get_pos(); };
    void dessin() override;
    std::string ecriture();

private:
    Cercle cercle;
};

class Corail : public Lifeform
{
public:
    Corail() = default;
    Corail(std::istringstream &data, bool &erreur);
    Corail(Carre base, int id, Status_cor status, Dir_rot_cor rot,
           Status_dev st_dev) :  Lifeform(1), base(base), id(id), status(status), sens_rot(rot),
           st_dev(st_dev), nb_seg(0) {};
    
    void add_seg(std::istringstream &data, bool &erreur);
    void add_seg(Segment &seg);

    // TODO: C'est vraiment public les tests?
    void test_longueur_segment(unsigned int l_seg, bool &erreur);
    void test_angle(double angle, bool &erreur);

    bool inclusion_dernier_segment(bool lecture);
    void dessin() override;
    std::string ecriture();
    int get_nb_seg() const { return nb_seg; };
    int get_id() const { return id; };
    std::vector<Segment>& get_segs() { return segs; };
    Status_cor get_status() const { return status; };
    void set_status(Status_cor s) { status = s; };
    Dir_rot_cor get_sens_rot() const { return sens_rot; };
    Status_dev get_status_dev() const { return st_dev; };
    void set_sens_rot(Dir_rot_cor s) { sens_rot = s; };
    void switch_rot();
    void new_seg();
    void switch_st_dev();

private:
    Carre base;
    int id;
    Status_cor status;
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
    void set_cible(int id) {id_cible = id};
    int get_cible() const { return id_cible; };

private:
    Cercle cercle;
    Status_sca etat;
    int id_cible;
};

#endif