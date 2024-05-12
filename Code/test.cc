// test.cc : Teste les fonctions de lecture/écriture de la simulation
//           À compiler séparément avec "make test"
// Auteurs : Daniel Roulin & Joshua Hurlimann
// Version 2

#include <iostream>
#include <cmath>
#include "shape.h"

using namespace std;

int main()
{
    S2d base1 = {50, 120};
    S2d base2 = {50, 190};
    Segment s1(base1, 1.562500, 24);
    Segment s2(base2, -1.562500, 24);

    cout << boolalpha << endl;
    cout << s1.intersection(s2, false) << endl;
}