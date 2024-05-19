// lifeform.cc : Entités de la simulation
// Auteurs : Daniel Roulin (50%) & Joshua Hurlimann (50%)
// Version 2 

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

void Lifeform:: update_age()
{
    age += 1;
}

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

    status   = static_cast<Status_cor>(statut_int);
    sens_rot = static_cast<Dir_rot_cor>(sens_rot_int);
    st_dev   = static_cast<Status_dev>(st_dev_int);

    test_pos(pos_x, pos_y, erreur);
    test_age(age, erreur);

    base = Carre(pos_x, pos_y, d_cor);
}

void Corail::add_seg(istringstream &data, bool &erreur)
{
    double angle;
    int length;
    if (!(data >> angle >> length))
    {
        erreur_lecture("segment", erreur);
        return;
    }

    test_longueur_segment(length, erreur);
    test_angle(angle, erreur);

    S2d base_pos;
    int size = segs.size();
    if (size == 0)
        base_pos = base.get_pos();
    else
        base_pos = segs[size - 1].get_extremity();

    Segment new_seg = Segment(base_pos, angle, length);
    segs.push_back(new_seg);
    if (!inclusion_dernier_segment(true))
    {
        erreur = true;
        return;
    }
    if (size != 0 && new_seg.superposition_lecture(segs[size - 1]))
    {
        cout << message::segment_superposition(id, size - 1, size);
        erreur = true;
    }
}

void Corail::add_seg(Segment &seg)
{
    segs.push_back(seg);
    nb_seg += 1;
}

void Corail::test_longueur_segment(unsigned int l_seg, bool &erreur)
{
    if ((l_seg < l_nv_seg) or (l_seg >= l_repro))
    {
        cout << message::segment_length_outside(id, l_seg);
        erreur = true;
    }
}

void Corail::test_angle(double angle, bool &erreur)
{
    if ((angle < -M_PI) or (angle > M_PI))
    {
        cout << message::segment_angle_outside(id, angle);
        erreur = true;
    }
}

// Vérifie que le segment est dans la simulation
bool Corail::inclusion_dernier_segment(bool lecture)
{
    Segment dernier_segment = segs.back();
    S2d pos = dernier_segment.get_extremity();
    double tolerance = lecture ? 0 : epsil_zero;
    if ((pos.x <= tolerance) or (pos.x >= (dmax - tolerance)) 
    or  (pos.y <= tolerance) or (pos.y >= (dmax - tolerance)))
    {
        if (lecture)
        {
            cout << message::lifeform_computed_outside(id, pos.x, pos.y);
        }
        return false;
    }
    return true;
}

void Corail::dessin()
{
    Color couleur;
    if (status == ALIVE)
        couleur = BLEU;
    else
        couleur = NOIR;

    base.dessin(couleur);
    for (auto& seg : segs)
    {
        seg.dessin(couleur);
    }
}

string Corail::ecriture()
{
    return to_string(base.get_pos()) + " " + to_string(age) + " " + to_string(id)
         + " " + to_string(status) + " " + to_string(sens_rot) + " "
         + to_string(st_dev) + " " + to_string(segs.size());
}

void Corail::switch_rot()
{
    if (sens_rot == TRIGO)
        sens_rot = INVTRIGO;
    else
        sens_rot = TRIGO;
}

void Corail::new_seg()
{
    Segment &dernier = segs.back();
    dernier.set_length(l_seg_interne);
    Segment nouveau_segment(dernier.get_extremity(), dernier.get_angle(), l_nv_seg);
    add_seg(nouveau_segment);
}

void Corail::switch_st_dev()
{
    if (st_dev == EXTEND)
        st_dev = REPRO;
    else
        st_dev = EXTEND;
}

void Corail::raccourcissement(S2d pos1, S2d pos2)
{
    Segment& dernier_seg = segs.back();
    int length = dernier_seg.get_length();
    cout << "test, length :" << length << " pos sca:" << pos2.x << "," << pos2.y << endl;
    if (distance(pos1, pos2) > delta_l)
    {
        dernier_seg.grow(-delta_l);    
    }
    else
    {
        nb_seg--;
        segs.pop_back();
    } 
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

void Scavenger::deplacement(S2d arrive)
{
    double dist_x = get_pos().x - arrive.x;
    double dist_y = get_pos().y - arrive.y;
    double teta = atan2(dist_y, dist_x);
    if (distance(get_pos(), arrive) > delta_l)
    {
        double x = get_pos().x - delta_l*cos(teta);//pk avec - ca marche
        double y = get_pos().y - delta_l*sin(teta);
        set_pos({x, y});    
    }
    else
    {
        etat = EATING;
        set_pos(arrive);
    } 
}

bool Scavenger::croissance()
{   
    Cercle& c = cercle;
    unsigned int r = c.get_rayon();
    if(r >= r_sca_repro)
    {
        c.set_rayon(r_sca);
        return true;
    } 
    else
    {
        c.set_rayon(r + delta_r_sca);
        return false;
    } 
} 