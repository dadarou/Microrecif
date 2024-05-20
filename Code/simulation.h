// simulation.h : Entête de simulation.cc
// Auteurs : Daniel Roulin & Joshua Hurlimann
// Version 3 

#ifndef SIMULATION_H
#define SIMULATION_H

#include <string>
#include <vector>
#include <sstream>
#include <random>
#include "lifeform.h" // Pour utiliser les types dans les vectors.

class Simulation
{
public:
    void lecture(std::string nom_fichier);
    void sauvegarde(std::string nom_fichier);
    void dessin();
    void step();
    void spawn_algue();
    void reset();
    void set_birth(bool b) { naissance_algue = b; };
    bool get_birth() { return naissance_algue; };
    int get_nb_sim() { return nb_sim; };
    int get_nb_algues() { return algues.size(); };
    int get_nb_corails() { return corails.size(); };
    int get_nb_scavengers() { return scavengers.size(); };

private:
    void decodage(std::string ligne);
    void ajouter_algue(Algue *algue);
    void ajouter_corail(Corail *corail);
    bool test_intersection_coraux(Corail *corail, bool lecture);
    bool id_corail_existe(int id);
    void ajouter_scavenger(Scavenger *scavenger);
    int read_nb(std::istringstream &data, std::string section);
    template <typename T>
    void disparition(std::vector<T> &entites, unsigned int max_age);
    void mort_corails();
    Algue* closest_algue(Corail *corail, double &closest_angle);
    void update_corails();
    void alimentation_corail(Corail *corail);
    void allongement_corail(Corail *corail);
    void reproduction_corail(Corail *corail);
    int nouveau_id_corail();
    bool turn_corail(Corail *corail, double delta);
    bool collision(Corail *corail);
    bool eat_algue(Corail *corail, Algue *algue);
    void verif_corail_eaten(Scavenger *sca);
    void cible_a_0();
    void sca_who_eat(); 
    void mouvement_sca(Scavenger *sca, Corail *c_who_eaten);
    void manger_corail();
    void manger_segment(Corail *c_attaque, Scavenger *sca_eat);
    void trie_corails_attaque();
    void trie_eating_sca();
    void bebe_sca(Corail *corail, Scavenger *sca);
    
    
    
    template <typename T>
    void vider(std::vector<T*> entites);

    bool lecture_finie;
    bool lecture_error;
    enum Etat_decodage
    {
        NbAlg,
        Alg,
        NbCor,
        Cor,
        Seg,
        NbSca,
        Sca
    };
    Etat_decodage etat;
    int compteur_entite;
    int total_entite;
    Corail* corail_actuel;
    int compteur_segments;
    int total_segments;

    bool naissance_algue = false;
    int nb_sim = 0;

    std::default_random_engine random_engine;
    std::vector<Algue*> algues;
    std::vector<Corail*> corails;
    std::vector<Scavenger*> scavengers;
    std::vector<Corail*> dead_corails;
    std::vector<Corail*> corails_attaque;
    std::vector<Scavenger*> eating_sca;
};

#endif