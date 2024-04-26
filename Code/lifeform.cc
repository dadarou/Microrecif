// lifeform.cc : Entités de la simulation
// Auteurs : Daniel Roulin & Joshua Hurlimann
// Version 1 

#include <sstream>
#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include "lifeform.h"
#include "shape.h"
#include "constantes.h"
#include "message.h"
using namespace std;

void Lifeform::erreur_lecture(string type, bool &erreur)
{
    cout << "Error reading " << type << endl;
    erreur = true;
}

void Lifeform::test_age(unsigned int age, bool &erreur)
{
    if (age <= 0)
    {
        cout << message::lifeform_age(age);
        erreur = true;
    }
}

void Lifeform::test_pos(double x, double y, bool &erreur)
{
    if ((x < 1) or (x > (dmax - 1)) or (y < 1) or (y > (dmax - 1)))
    {
        cout << message::lifeform_center_outside(x, y);
        erreur = true;
    }
}

void Lifeform::update_age()
{
    age += 1;
}

Algue::Algue(istringstream &data, bool &erreur)
{
    double pos_x, pos_y;
    if (!(data >> pos_x >> pos_y >> age))
    {
        erreur_lecture("algue", erreur);
        return;
    }

    test_pos(pos_x, pos_y, erreur);
    test_age(age, erreur);

    cercle = Cercle(pos_x, pos_y, r_alg);
}

void Algue::dessin()
{
    cercle.dessin(VERT);
}

string Algue::ecriture()
{
    return to_string(cercle.get_pos()) + " " + to_string(age);
}


Corail::Corail(istringstream &data, bool &erreur)
{
    double pos_x, pos_y;
    int statut_int, sens_rot_int, st_dev_int;
    if (!(data >> pos_x >> pos_y >> age >> id 
               >> statut_int >> sens_rot_int >> st_dev_int >> nb_seg))
    {
        erreur_lecture("coral", erreur);
        return;
    }

    statut   = static_cast<Status_cor>(statut_int);
    sens_rot = static_cast<Dir_rot_cor>(sens_rot_int);
    st_dev   = static_cast<Status_dev>(st_dev_int);

    test_pos(pos_x, pos_y, erreur);
    test_age(age, erreur);

    base = Carre(pos_x, pos_y, d_cor);
}

void Corail::add_seg(istringstream &data, int id, bool &erreur)
{
    double angle;
    int length;
    if (!(data >> angle >> length))
    {
        erreur_lecture("segment", erreur);
        return;
    }

    test_longueur_segment(id, length, erreur);
    test_angle(id, angle, erreur);

    S2d base_pos;
    int size = segs.size();
    if (size == 0)
        base_pos = base.get_pos();
    else
        base_pos = segs[size - 1].get_extremity();

    inclusion_segment(id, base_pos, erreur);
    Segment new_seg = Segment(base_pos, angle, length);
    S2d extremite(new_seg.get_extremity());
    inclusion_segment(id, extremite, erreur);

    if (size != 0 && new_seg.superposition(segs[size - 1], true))
    {
        cout << message::segment_superposition(id, size - 1, size);
        erreur = true;
    }
    segs.push_back(new_seg);
}

void Corail::test_longueur_segment(int id, unsigned int l_seg, bool &erreur)
{
    double l0(l_repro - l_seg_interne);
    if ((l_seg < l0) or (l_seg >= l_repro))
    {
        cout << message::segment_length_outside(id, l_seg);
        erreur = true;
    }
}

void Corail::test_angle(int id, double angle, bool &erreur)
{
    if ((angle < -M_PI) or (angle > M_PI))
    {
        cout << message::segment_angle_outside(id, angle);
        erreur = true;
    }
}

// Vérifie que le segment est dans la simulation
void Corail::inclusion_segment(int id, S2d pos, bool &erreur)
{
    if ((pos.x <= epsil_zero) or (pos.x >= (dmax - epsil_zero)) 
    or  (pos.y <= epsil_zero) or (pos.y >= (dmax - epsil_zero)))
    {
        cout << message::lifeform_computed_outside(id, pos.x, pos.y);
        erreur = true;
    }
}

void Corail::dessin()
{
    base.dessin(BLEU);
    for (auto& seg : segs)
    {
        seg.dessin(BLEU);
    }
}

string Corail::ecriture()
{
    return to_string(base.get_pos()) + " " + to_string(age) + " " + to_string(id)
         + " " + to_string(statut) + " " + to_string(sens_rot) + " "
         + to_string(st_dev) + " " + to_string(segs.size());
}


Scavenger::Scavenger(istringstream &data, bool &erreur)
{
    double pos_x, pos_y;
    int rayon, etat_int;
    if (!(data >> pos_x >> pos_y >> age >> rayon >> etat_int))
    {
        erreur_lecture("scavenger", erreur);
        return;
    }

    etat = static_cast<Status_sca>(etat_int);
    if (etat == EATING && !(data >> id_cible))
    {
        erreur_lecture("id_cible", erreur);
        return;
    }

    test_pos(pos_x, pos_y, erreur);
    test_age(age, erreur);
    test_rayon(rayon, erreur);

    cercle = Cercle(pos_x, pos_y, rayon);
}

void Scavenger::test_rayon(unsigned int r, bool &erreur)
{
    if ((r < r_sca) or (r >= r_sca_repro))
    {
        cout << message::scavenger_radius_outside(r);
        erreur = true;
    }
}

void Scavenger::dessin()
{
    cercle.dessin(ROUGE);
}

string Scavenger::ecriture()
{
    string scavenger = to_string(cercle.get_pos()) + " " + to_string(age) + " "
                     + to_string(cercle.get_rayon()) + " " + to_string(etat);
    if (etat == EATING)
        return scavenger + " " + to_string(id_cible);
    return scavenger;
}