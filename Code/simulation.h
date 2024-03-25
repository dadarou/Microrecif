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
    void ajouter_algue(Algue algue);
    void ajouter_corail(Corail corail);
    void ajouter_scavenger(Scavenger scavenger);
    bool id_corail_existe(int id);
    void test_intersection_coraux(Corail corail);
    std::vector<Algue> algues;
    std::vector<Corail> corails;
    std::vector<Scavenger> scavengers;
};

#endif