// project.cc : Point d'entrée du projet
// Auteurs : Daniel Roulin & Joshua Hurlimann
// Version 1 


#include <iostream>
#include <string>
#include "simulation.h"
using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        // Le nom de fichier est manquant.
        cout << "Error: missing filename" << endl;
        exit(EXIT_FAILURE);
    }

    Simulation simulation;
    simulation.lecture(argv[1]);
    return 0;
}
