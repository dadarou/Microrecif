#include "../Code/shape.h"
#include <iostream>
#include <cmath>
#include <cassert>
using namespace std;

int main()
{
    /// Segment::angularGap(Segment segment) ///
    cout << "Testing Segment::angularGap(Segment segment) ..." << endl;

    S2d base = {0, 0};
    Segment seg1 = Segment(base, 0, 1);
    Segment seg2 = Segment(base, 0, 1);
    assert(seg1.angularGap(seg2) == M_PI);

    seg1 = Segment(base, 0, 1);
    seg2 = Segment(base, -M_PI, 1);
    assert(seg1.angularGap(seg2) == 0);

    seg1 = Segment(base, M_PI / 4, 1);
    seg2 = Segment(base, M_PI / 2, 1);
    assert(seg1.angularGap(seg2) == 3 * M_PI / 4);

    seg1 = Segment(base, M_PI / 4, 1);
    seg2 = Segment(base, -M_PI / 4, 1);
    assert(seg1.angularGap(seg2) == -M_PI / 2);

    seg1 = Segment(base, -M_PI / 4, 1);
    seg2 = Segment(base, M_PI / 4, 1);
    assert(seg1.angularGap(seg2) == M_PI / 2);

    seg1 = Segment(base, -M_PI / 4, 1);
    seg2 = Segment(base, -M_PI / 2, 1);
    assert(seg1.angularGap(seg2) == -3 * M_PI / 4);

    cout << "Tested  Segment::angularGap(Segment segment) !" << endl;

    /// Segment::angularGap(S2d point) ///
    cout << "Testing Segment::angularGap(S2d point) ..." << endl;

    S2d point = {0, 1};
    seg1 = Segment(base, 0, 1);
    assert(seg1.angularGap(point) == M_PI / 2);

    point = {1, 1};
    seg1 = Segment(base, 0, 1);
    assert(seg1.angularGap(point) == M_PI / 4);

    point = {1, -1};
    seg1 = Segment(base, 0, 1);
    assert(seg1.angularGap(point) == -M_PI / 4);

    base = {1, 1};
    point = {0, 0};
    seg1 = Segment(base, 0, 1);
    assert(seg1.angularGap(point) == -3 * M_PI / 4);

    base = {1, 1};
    point = {0, 2};
    seg1 = Segment(base, M_PI / 4, 1);
    assert(seg1.angularGap(point) == M_PI / 2);

    cout << "Tested  Segment::angularGap(S2d point) !" << endl;

    /// Segment::superposition(Segment other, bool lecture_fichier) ///
    cout << "Testing Segment::superposition(Segment other, bool lecture_fichier) ..." << endl;
    base = {10, 10};
    seg1 = Segment(base, M_PI / 4, 1);
    seg2 = Segment(base, M_PI / 4, 1);
    assert(seg1.superposition(seg2) == false);

    base = {0, 0};
    seg1 = Segment(base, 3 * M_PI / 4, 1);
    seg2 = Segment(base, M_PI / 4, 1);
    assert(seg1.superposition(seg2) == false);

    base = {10, 0};
    seg1 = Segment(base, 3 * M_PI / 4, 1);
    seg2 = Segment(base, M_PI / 4, 1);
    assert(seg1.superposition(seg2) == false);

    S2d base1 = {0, 0};
    S2d base2 = {10, 0};
    seg1 = Segment(base1, 0, 10);
    seg2 = Segment(base2, M_PI, 10);
    assert(seg1.superposition(seg2, true) == true);

    cout << "Tested  Segment::superposition(Segment other, bool lecture_fichier) !" << endl;

    /// Segment::intersection(Segment other, bool lecture_fichier) ///
    cout << "Testing Segment::intersection(Segment other, bool lecture_fichier) ..." << endl;

    seg1 = Segment({1, 1}, M_PI / 4, 10);
    seg2 = Segment({1, 3}, -M_PI / 4, 10);
    assert(seg1.intersection(seg2) == true);
    assert(seg2.intersection(seg1) == true);

    seg1 = Segment({1, 1}, M_PI / 4, 10);
    seg2 = Segment({3, 1}, 3 * M_PI / 4, 10);
    assert(seg1.intersection(seg2) == true);
    assert(seg2.intersection(seg1) == true);

    seg1 = Segment({1, 3}, -M_PI / 4, 10);
    seg2 = Segment({3, 3}, -3 * M_PI / 4, 10);
    assert(seg1.intersection(seg2) == true);
    assert(seg2.intersection(seg1) == true);

    seg1 = Segment({3, 3}, -3 * M_PI / 4, 10);
    seg2 = Segment({3, 1}, 3 * M_PI / 4, 10);
    assert(seg1.intersection(seg2) == true);
    assert(seg2.intersection(seg1) == true);

    cout << "Tested  Segment::intersection(Segment other, bool lecture_fichier) !" << endl;
    cout << "All tests passed!";
}