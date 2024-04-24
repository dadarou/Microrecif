// simulation.h : Gestion de la simulation
// Auteurs : Daniel Roulin & Joshua Hurlimann
// Version 1 

#ifndef SIMULATION_H
#define SIMULATION_H

#include <string>
#include <vector>
#include <sstream>
#include "lifeform.h" // Pour utiliser les types dans les vectors.
#include <random>
using namespace std;

class Simulation
{
public:
    void lecture(std::string nom_fichier);
    void dessin();
    void sauvegarde(std::string nom_fichier);
    void update();
    void spawn_algue();
    void reset();
    void set_birth(bool b) { naissance_algue = b; };

private:
    int nbSim;
    bool naissance_algue;
    default_random_engine random_engine;
    void decodage(std::string ligne);
    void ajouter_algue(Algue algue);
    void ajouter_corail(Corail corail);
    void test_intersection_coraux(Corail corail);
    bool id_corail_existe(int id);
    void ajouter_scavenger(Scavenger scavenger);
    int read_nb(std::istringstream &data, std::string section);
    void succes_lecture();
    std::vector<Algue> algues;
    std::vector<Corail> corails;
    std::vector<Scavenger> scavengers;
};

#endif