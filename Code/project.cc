#include "simulation.h"
#include <iostream>
#include <string>
using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        // Le nom de fichier est manquant.
        cout << "Missing filename" << endl;
        exit(EXIT_FAILURE);
    }

    Simulation simulation;
    simulation.lecture(argv[1]);
    return 0;
}
