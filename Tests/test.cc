#include "../Code/shape.cc"
#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    /// Segment::angularGap() ///
    cout << "Testing Segment::angularGap()..." << endl;

    S2d point;
    Segment seg1 = {point, 0, 10};
    Segment seg2 = {point, 0, 10};

    seg1 = {point, 0, 10};
    seg2 = {point, 0, 10};
    assert(seg1.angularGap(seg2) == M_PI);

    seg1 = {point, 0, 10};
    seg2 = {point, -M_PI, 10};
    assert(seg1.angularGap(seg2) == 0);

    seg1 = {point, M_PI/4, 10};
    seg2 = {point, M_PI/2, 10};
    assert(seg1.angularGap(seg2) == 3*M_PI/4);

    seg1 = {point, M_PI/4, 10};
    seg2 = {point, -M_PI/4, 10};
    assert(seg1.angularGap(seg2) == -M_PI/2);

    seg1 = {point, -M_PI/4, 10};
    seg2 = {point, M_PI/4, 10};
    assert(seg1.angularGap(seg2) == M_PI/2);

    seg1 = {point, -M_PI/4, 10};
    seg2 = {point, -M_PI/2, 10};
    assert(seg1.angularGap(seg2) == -3*M_PI/4);

    cout << "Tested Segment::angularGap()!" << endl;
}