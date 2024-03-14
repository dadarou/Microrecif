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
public:
    Segment(S2d base, double angle, double length);
    S2d extremity();
    double angularGap(Segment s);
};

#endif