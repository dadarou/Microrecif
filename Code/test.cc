#include "simulation.h"
#include <iostream>

using namespace std;

int main()
{
    Simulation sim;
    sim.lecture("../Tests/public/t27.txt");
    sim.sauvegarde("out.txt");
}