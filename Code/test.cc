#include "simulation.h"
#include <iostream>

using namespace std;

int main()
{
    Simulation sim;
    sim.lecture("../Tests/public/t09.txt");
    sim.sauvegarde("out.txt");
}