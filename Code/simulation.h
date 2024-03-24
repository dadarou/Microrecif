#ifndef SIMULATION_H
#define SIMULATION_H
#include <string>
#include <vector>
#include "lifeform.h" // Pour utiliser les types dans les vectors.
using namespace std;

class Simulation
{
public:
    void lecture(string nom_fichier);

private:
    void decodage(string ligne);
    vector<Algue> algues;
    vector<Corail> corails;
    vector<Scavenger> scavengers;
};

#endif