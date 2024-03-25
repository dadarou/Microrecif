#ifndef SIMULATION_H
#define SIMULATION_H
#include <string>
#include <vector>
#include <sstream>
#include "lifeform.h" // Pour utiliser les types dans les vectors.

class Simulation
{
public:
    void lecture(std::string nom_fichier);

private:
    void decodage(std::string ligne);
    int read_nb(std::istringstream &data, std::string section);
    void succes_lecture();
    std::vector<Algue> algues;
    std::vector<Corail> corails;
    std::vector<Scavenger> scavengers;
};

#endif