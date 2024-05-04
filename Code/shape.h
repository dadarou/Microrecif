// shape.h : Entête de shape.cc
// Auteurs : Daniel Roulin
// Version 2 

#ifndef SHAPE_H
#define SHAPE_H

#include "graphic.h"



#include <iostream>
using namespace std;


#include <string>

constexpr double epsil_zero(0.5);

struct S2d
{
    double x;
    double y;
};

std::string to_string(const S2d& pos);
double distance(const S2d& pos1, const S2d& pos2);

class Carre
{
public:
    Carre() = default;
    Carre(S2d pos, double side)
        : pos(pos), side(side){};
    Carre(double pos_x, double pos_y, double side)
        : pos({pos_x, pos_y}), side(side){};
    S2d get_pos() const { return pos; }
    double get_side() const { return side; }
    void dessin(Color color);

private:
    S2d pos;
    double side;
};

class Cercle
{
public:
    Cercle() = default;
    Cercle(S2d pos, int rayon)
        : pos(pos), rayon(rayon){};
    Cercle(double pos_x, double pos_y, int rayon)
        : pos({pos_x, pos_y}), rayon(rayon){};
    S2d get_pos() const { return pos; }
    int get_rayon() const { return rayon; }
    void dessin(Color color);

private:
    S2d pos;
    int rayon;
};

class Segment
{
public:
    Segment(S2d base, double angle, int length)
    : base(base), angle(angle), length(length){};
    int get_length() { return length; };
    S2d get_base() { return base; };
    S2d get_extremity();
    double angular_gap(S2d point);
    double angular_gap(Segment other);
    bool superposition(Segment other, bool lecture_fichier = false);
    bool intersection(Segment other, bool lecture_fichier = false);
    void dessin(Color color);
    std::string ecriture();
    void turn(double angle);

private:
    S2d base;
    double angle;
    int length;
    double normalize_angle(double angle);
    int orientation(S2d p, S2d q, S2d r, int length, double tolerance);
    bool on_segment(S2d p, S2d q, S2d r, double tolerance);
};

#endif