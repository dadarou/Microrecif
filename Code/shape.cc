// shape.cc : Bibliothèque de formes
// Auteurs : Daniel Roulin (100%)
// Version 2

#include <cmath>
#include <cassert>
#include "shape.h"
#include "graphic.h"
using namespace std;

std::string to_string(const S2d &pos)
{
    return to_string(pos.x) + " " + to_string(pos.y);
}

double distance(const S2d& pos1, const S2d& pos2)
{
    double dx = pos2.x - pos1.x;
    double dy = pos2.y - pos1.y;
    return sqrt(dx*dx + dy*dy);
}

void Carre::dessin(Color color)
{
    set_color(color);
    dessin_carre(pos.x - side/2., pos.y - side/2., side);
}

void Cercle::dessin(Color color)
{
    set_color(color);
    dessin_cercle(pos.x, pos.y, rayon);
}

// Renvoie l’extrémité du segment.
S2d Segment::get_extremity()
{
    S2d extremity;
    extremity.x = base.x + length * cos(angle);
    extremity.y = base.y + length * sin(angle);
    return extremity;
}

// Renvoie l’écart angulaire entre un segment et un vecteur
// construit à partir de la base du segment et d’un point.
double Segment::angular_gap(S2d point)
{
    double angle_point = atan2(point.y - base.y, point.x - base.x);
    double gap = angle_point - angle;
    return normalize_angle(gap);
}

// Renvoie l’écart angulaire dans l’intervalle [-π, π] entre 2 segments (section 2.1)
double Segment::angular_gap(Segment other)
{
    double gap = angle - other.angle + M_PI;
    return normalize_angle(gap);
}

// Normalize l'angle dans l’intervalle [-π, π]
double Segment::normalize_angle(double angle_)
{
    while (angle_ > M_PI)
    {
        angle_ -= 2 * M_PI;
    }
    while (angle_ < -M_PI)
    {
        angle_ += 2 * M_PI;
    }
    return angle_;
}

// Le booléen de superposition de 2 segments ayant la meme base (section 2.1).
// En lecture de fichier la tolérance est nulle.
// Renvoie vrai si l'angle entre les deux segments est proche de zéro.
bool Segment::superposition_lecture(Segment other)
{
    double gap = angular_gap(other);
    return gap == 0;
}

// Renvoie la norme du vecteur p1->p2
double Segment::norme(S2d p1, S2d p2)
{
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

// Source: https://www.geeksforgeeks.org/orientation-3-ordered-points/
// Length est la longueur de pq, c'est la longeur du segment.
int Segment::orientation(S2d p, S2d q, S2d r, double tolerance)
{
    double val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y); 
    double d = val/norme(p, q);
    if (abs(d) <= tolerance)
        return 0;
    return (val > 0) ? 1 : 2;
}

// Renvoie vrai si le point r est dans le segment pq.
// On suppose pq colinaire a r.
bool Segment::on_segment(S2d p, S2d q, S2d r, double tolerance)
{
    S2d pr;
    pr.x = r.x - p.x;
    pr.y = r.y - p.y;

    S2d pq;
    pq.x = r.x - q.x;
    pq.y = r.y - q.y;

    // Produit scalaire pr•pq
    double s = pr.x * pq.x + pr.y * pq.y;

    // Norme de pr
    double norme_pr = sqrt(pr.x * pr.x + pr.y * pr.y);

    // Norme de la projection de pq sur pr
    double x = s / norme_pr;

    return -tolerance <= x && x <= norme_pr + tolerance;
}

// Renvoie le booléen d’intersection ou de superposition de 2 segments indépendants
// Si lecture_fichier est vrai, epsil_zero est mis a zéro
// Source: https://www.geeksforgeeks.org/orientation-3-ordered-points/
bool Segment::intersection(Segment other, bool lecture_fichier)
{
    double tolerance = lecture_fichier ? 0 : epsil_zero;
    S2d p1 = base;
    S2d q1 = get_extremity();
    S2d p2 = other.get_base();
    S2d q2 = other.get_extremity();

    // Find the four orientations needed for general and special cases
    int o1 = orientation(p1, q1, p2, tolerance);
    int o2 = orientation(p1, q1, q2, tolerance);
    int o3 = orientation(p2, q2, p1, tolerance);
    int o4 = orientation(p2, q2, q1, tolerance);

    // General case
    // Condition adapté, voir https://edstem.org/eu/courses/1163/discussion/109642
    if (o1 && o2 && o3 && o4 && o1 != o2 && o3 != o4)
        return true;

    // Special Cases
    // p1, q1 and p2 are collinear and p2 lies on segment p1q1
    if (o1 == 0 && on_segment(p1, p2, q1, tolerance))
        return true;

    // p1, q1 and q2 are collinear and q2 lies on segment p1q1
    if (o2 == 0 && on_segment(p1, q2, q1, tolerance))
        return true;

    // p2, q2 and p1 are collinear and p1 lies on segment p2q2
    if (o3 == 0 && on_segment(p2, p1, q2, tolerance))
        return true;

    // p2, q2 and q1 are collinear and q1 lies on segment p2q2
    if (o4 == 0 && on_segment(p2, q1, q2, tolerance))
        return true;

    return false; // Doesn't fall in any of the above cases
}

void Segment::dessin(Color color)
{
    S2d extremity = get_extremity();
    set_color(color);
    dessin_line(base.x, base.y, extremity.x, extremity.y);
}

std::string Segment::ecriture()
{
    // On renvoie l'angle dans [0, 2PI]
    return to_string(fmod(angle, 2*M_PI)) + " " + to_string(length);
}

void Segment::turn(double delta)
{
    angle = angle + delta;
}

void Segment::grow(int amount)
{
    length += amount;
}