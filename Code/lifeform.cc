#include "lifeform.h"
#include "shape.h"
#include "constantes.h"
#include "message.h"
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

void Lifeform::test_age(int age)
{
    if (age <= 0)
    {
    message::lifeform_age(age);
    exit(EXIT_FAILURE);
    }
}

void Lifeform::test_pos(double x, double y)
{
    if ((x < 1) or (x > (dmax - 1)) or (y < 1) or (y > (dmax - 1))) 
    {
    message::lifeform_center_outside(x, y);
    exit(EXIT_FAILURE);
    }
}//max est ambigu car c'est une constantes mais aussi un truc dans std peut etre

Algue::Algue(istringstream &data)
{
    double pos_x, pos_y;
    if (!(data >> pos_x >> pos_y >> age))
        erreur_lecture("algue");
        test_pos(pos_x, pos_y);
        test_age(age);
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
        test_pos(pos_x, pos_y);
        test_age(age);
    base = Carre(pos_x, pos_y, d_cor);

    // TODO: Detection d'erreurs
    // Test_Lifeform(pos_x, pos_y, age);
    // Test_Corail();
}

void Corail::addSeg(istringstream &data, int id)
{
    double angle, length;
    if (!(data >> angle >> length))
        erreur_lecture("segment");
        test_longueur_segment(id, length);
        test_angle(id, angle);

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
    inclusion_segment(id, base_pos);
    Segment new_seg = Segment(base_pos, angle, length);
    S2d extremite(new_seg.extremity());
    inclusion_segment(id, extremite);
    if (size != 0 && new_seg.superposition(segs[size - 1], true))
    {
        cout << message::segment_superposition(id, size - 1, size);
        exit(EXIT_FAILURE);
    }

    segs.push_back(new_seg);
}

void Corail::test_longueur_segment(int id, double l_seg)
{
    double l0(l_repro - l_seg_interne);
    if ( (l_seg < l0) or (l_seg >= l_repro))
    {
    message::segment_length_outside(id, l_seg);//le l_seg attendu devrait etre un unsigned
    exit(EXIT_FAILURE);
    }
}

void Corail::test_angle(int id, double angle)
{
    if((angle < -M_PI) or (angle > M_PI))
    {
        message::segment_angle_outside(id, angle);
        exit(EXIT_FAILURE);
    }
}

void Corail::inclusion_segment(int id,S2d pos)
{
    if ((pos.x <= epsil_zero) or (pos.x >= (dmax - epsil_zero)) 
    or  (pos.y <= epsil_zero) or (pos.y >= (dmax - epsil_zero)))
    {
        message::lifeform_computed_outside(id, x, y);
        exit(EXIT_FAILURE);
    }
}

Scavenger::Scavenger(istringstream &data)
{
    double pos_x, pos_y, rayon;
    if (!(data >> pos_x >> pos_y >> age >> rayon >> etat))
        erreur_lecture("scavenger");
        test_pos(pos_x, pos_y);
        test_age(age);
        test_rayon(rayon);
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

void Scavenger::test_rayon(double r)
{
    if ((r < r_sca) or (r >= r_sca_repro))
    {
        message::scavenger_radius_outside(r); //ca demande un unsigned donc y'a un probleme je pense
        exit(EXIT_FAILURE);
    }
    
}

/* 
 * Tests à effectuer: 
 * Daniel:
 * [x] unicité des identificateurs de coraux 
 * [x] existence d’un corail identifié avec l’identificateur mémorisé par un scavenger dans l’état MANGE 
 * [x] intersection des coraux
 * [x] superposition des coraux
 * 
 * Joshua:
 * l’age est strictement positif 
 * la longueur des segments est comprise dans [l_repro-l_seg_interne, l_repro[ 
 * l’angle des segments est compris dans [-π, π] 
 * le rayon des scavengers est compris dans [r_sca, r_sca_repro[ 
 * inclusion des centres des algues et scavengers, et la base des coraux dans le domaine [1, max-1]
 * inclusion de la base des segments de coraux et de l’extrémité du dernier segment dans ]epsil_zero, max – epsil_zero[
*/
