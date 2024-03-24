#ifndef SHAPE_H
#define SHAPE_H

constexpr double epsil_zero(0.5);

struct S2d
{
    double x;
    double y;
};

class Carre
{
public:
    Carre() = default;
    Carre(S2d pos, double side)
        : pos(pos), side(side){};
    Carre(double pos_x, double pos_y, double side)
        : pos({pos_x, pos_y}), side(side){};
    S2d getPos() const { return pos; }
    double getSide() const { return side; }

private:
    S2d pos;
    double side;
};

class Cercle
{
public:
    Cercle() = default;
    Cercle(S2d pos, double rayon)
        : pos(pos), rayon(rayon){};
    Cercle(double pos_x, double pos_y, double rayon)
        : pos({pos_x, pos_y}), rayon(rayon){};
    S2d getPos() const { return pos; }
    double getRayon() const { return rayon; }

private:
    S2d pos;
    double rayon;
};

class Segment
{
private:
    S2d base;
    double angle;
    double length;
    int orientation(S2d p, S2d q, S2d r, double length, double tolerance);
    bool onSegment(S2d p, S2d q, S2d r, double tolerance);
    double normalizeAngle(double angle);

public:
    Segment(S2d base, double angle, double length);
    S2d extremity();
    double angularGap(Segment other);
    double angularGap(S2d point);
    bool superposition(Segment other, bool lecture_fichier = false);
    bool intersection(Segment other, bool lecture_fichier = false);
};

#endif