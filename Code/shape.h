#ifndef SHAPE_H
#define SHAPE_H

constexpr double epsil_zero(0.5);

struct S2d
{
    double x = 0.;
    double y = 0.;
};

class Segment
{
private:
    S2d base;
    double angle;
    double length;
    int orientation(S2d p, S2d q, S2d r, double length);
    bool onSegment(S2d p, S2d q, S2d r);
    double normalizeAngle(double angle);

public:
    Segment(S2d base, double angle, double length);
    S2d extremity();
    double angularGap(Segment other);
    double angularGap(S2d point);
    bool superposition(Segment other);
    bool doIntersect(Segment other);
};

#endif