#include "shape.h"
#include <cmath>
#include <cassert>
using namespace std;

Segment::Segment(S2d base, double angle, double length)
    : base(base), angle(angle), length(length)
{
    assert(angle >= -M_PI && angle <= M_PI);
    assert(length >= 0);
}

S2d Segment::extremity()
{
    S2d extremity;
    extremity.x = base.x + length*cos(angle);
    extremity.y = base.y + length*sin(angle);
    return extremity;
}

double Segment::angularGap(Segment s)
{
    double gap = angle - s.angle + M_PI;
    if (gap > M_PI)
    {
        gap -= 2*M_PI;
    } else if (gap < -M_PI)
    {
        gap += 2*M_PI;
    }
    return gap;
}
