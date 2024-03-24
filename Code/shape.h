#ifndef SHAPE_H
#define SHAPE_H

constexpr double epsil_zero(0.5);

struct S2d
{
    double x;
    double y; // test
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