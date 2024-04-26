// test.cc : Teste les fonctions de lecture/écriture de la simulation
//           À compiler séparément avec "make test"
// Auteurs : Daniel Roulin & Joshua Hurlimann
// Version 2

#include <iostream>
#include "simulation.h"

using namespace std;

int main()
{
    Simulation sim;
    sim.lecture("t27.txt");
    sim.sauvegarde("out.txt");
}