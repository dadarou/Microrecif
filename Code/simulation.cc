// simulation.cc : Gestion de la simulation
// Auteurs : Daniel Roulin (30%) & Joshua Hurlimann (70%)
// Version 2 

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <random>
#include "simulation.h"
#include "message.h"
#include "lifeform.h"
#include "shape.h"
#include "constantes.h"
using namespace std;

void Simulation::lecture(string nom_fichier)
{
    reset();

    string ligne;
    ifstream l_fichier(nom_fichier);

    if (!l_fichier.fail())
    {
        while (getline(l_fichier >> ws, ligne))
        {
            if (ligne[0] == '#')
            {
                continue;
            }
            decodage(ligne);
            if (lecture_error)
            {
                reset();
                break;
            }
            if (lecture_finie)
            {
                cout << message::success();
                break;
            }
        }
    }
    else
    {
        cout << "Error opening file" << endl;
        reset();
    }
    l_fichier.close();
}

// Fonction appelée pour chaque ligne.
void Simulation::decodage(string ligne)
{
    istringstream data(ligne);

    switch (etat)
    {
    case NbAlg:
    {
        total_entite = read_nb(data, "nbAlg");
        if (total_entite == 0) etat = NbCor;
        else etat = Alg;
    }
    break;
    case Alg:
    {
        ++compteur_entite;
        Algue algue(data, lecture_error);
        ajouter_algue(algue);
        if (compteur_entite == total_entite) etat = NbCor;
    }
    break;
    case NbCor:
    {
        compteur_entite = 0;
        total_entite = read_nb(data, "nbCor");
        if (total_entite == 0) etat = NbSca;
        else etat = Cor;
    }
    break;
    case Cor:
    {
        ++compteur_entite;
        compteur_segments = 0;
        corail_actuel = Corail(data, lecture_error);
        if (lecture_error) return;
        total_segments = corail_actuel.get_nb_seg();
        if (total_segments == 0)  
        {
            ajouter_corail(corail_actuel);
            if (compteur_entite == total_entite) etat = NbSca;   
        }
        else etat = Seg;
    }
    break;
    case Seg:
    {
        ++compteur_segments;
        corail_actuel.add_seg(data, lecture_error);
        if (compteur_segments == total_segments) 
        {
            ajouter_corail(corail_actuel);
            if (compteur_entite == total_entite) etat = NbSca; 
            else etat = Cor; 
        }
    }
    break;
    case NbSca:
    {
        compteur_entite = 0;
        total_entite = read_nb(data, "nbSca");
        if (total_entite == 0) lecture_finie = true;
        else etat = Sca;
    }
    break;
    case Sca:
    {
        ++compteur_entite;
        Scavenger scavenger(data, lecture_error);
        ajouter_scavenger(scavenger);
        if (compteur_entite == total_entite) lecture_finie = true;
    }
    break;
    }
}

void Simulation::ajouter_algue(Algue algue)
{
    algues.push_back(algue);
}

void Simulation::ajouter_corail(Corail corail)
{
    // Unicité de l'identificateur de coraux
    int id = corail.get_id();
    if (id_corail_existe(id))
    {
        cout << message::lifeform_duplicated_id(id);
        lecture_error = true;
        return;
    }

    corails.push_back(corail);

    test_intersection_coraux(corail, true);
}

// Intersections intra ou inter corail
// L'agorithme actuel est en O(n^3)
// On pourrait l'optimiser mais ce n'est pas demandé pour l'instant ¯\_(ツ)_/¯
bool Simulation::test_intersection_coraux(Corail corail, bool lecture)
{
    auto segs = corail.get_segs();
    for (unsigned int i = 0; i < segs.size(); i++) 
    {
        Segment seg = segs[i];
        for (auto& autre_cor : corails)
        {
            auto other_segs = autre_cor.get_segs();
            for (unsigned int j = 0; j < other_segs.size(); j++) 
            {
                Segment autre_seg = other_segs[j];
                int id1 = corail.get_id();
                int id2 = autre_cor.get_id();
                // On ne teste pas l'intersection entre le même segments ou des 
                // segments consecutifs d'un même corail.
                bool consec = (id1 == id2) && (i == j || i == j + 1 || i == j - 1);
                if (!consec && seg.intersection(autre_seg, lecture))
                {
                    if (lecture)
                    {
                        cout << message::segment_collision(id1, i, id2, j);
                        lecture_error = true;
                    }
                    return true;
                }
            }
        }
    }
    return false;
}

bool Simulation::id_corail_existe(int id)
{
    for (auto& corail : corails)
    {
        if (id == corail.get_id())
        {
            return true;
        }
    }
    return false;
}

void Simulation::ajouter_scavenger(Scavenger scavenger)
{
    // Test d'existence du corail mémorisé par le scavenger
    int id = scavenger.get_cible();
    if (scavenger.get_etat() == EATING && !id_corail_existe(id))
    {
        cout << message::lifeform_invalid_id(id);
        lecture_error = true;
        return;
    }
    scavengers.push_back(scavenger);
}

int Simulation::read_nb(istringstream &data, string section)
{
    int nb;
    if (!(data >> nb) or nb < 0)
    {
        cout << "Error reading " << section << endl;
        lecture_error = true;
        return 0;
    }
    return nb;
}

void Simulation::sauvegarde(string nom_fichier)
{
    ofstream fichier(nom_fichier);
    if(!fichier.fail())
    {
        fichier << algues.size() << endl;
        for (auto& algue : algues)
        {
            fichier << "    " << algue.ecriture() << endl;
        }

        fichier << corails.size() << endl;
        for (auto& corail : corails)
        {
            fichier << "    " << corail.ecriture() << endl;
            for (auto& segment : corail.get_segs())
            {
                fichier << "        " << segment.ecriture() << endl;
            }
        }

        fichier << scavengers.size() << endl;
        for (auto& scavenger : scavengers)
        {
            fichier << "    " << scavenger.ecriture() << endl;
        }
    }
    fichier.close();
}

void Simulation::dessin()
{
    for (auto& algue : algues)
    {
        algue.dessin();
    }
    for (auto& corail : corails)
    {
        corail.dessin();
    }
    for (auto& scavenger : scavengers)
    {
        scavenger.dessin();
    }
}

template <typename T>
void Simulation::disparition(vector<T> &entites, unsigned int max_life)
{
    for (unsigned int i = 0; i < entites.size(); i++) 
    {
        T& entite = entites[i];
        entite.update_age();
        if (entite.get_age() >= max_life)
        {
            swap(entite, entites.back());
            entites.pop_back();
            i--;
        }
    }
}

void Simulation::mort_corails()
{
    for (auto &corail : corails)
    {
        corail.update_age();
        if (corail.get_age() >= max_life_cor and corail.get_status() == ALIVE)
        {
            corail.set_status(DEAD);
            dead_corails.push_back(&corail);
        }
    }
}

// Trouve l'algue la plus proche entre l'effecteur et l'angle.
// On renvoie un pointer car le success n'est pas garanti.
// En cas d'echec, retourne nullptr
Algue* Simulation::closest_algue(Corail &corail, double &closest_angle)
{
    Algue* closest = nullptr;
    Segment& dernier = corail.get_segs().back();
    for (auto &algue : algues)
    {
        // On ignore les algues trop lointaines
        if (distance(dernier.get_base(), algue.get_pos()) > dernier.get_length())
            continue;

        double angle = dernier.angular_gap(algue.get_pos());
        // On ignore les algues derrière et sur l'effecteur
        if ((corail.get_sens_rot() == TRIGO and angle <= 0)
        or (corail.get_sens_rot() == INVTRIGO and angle >= 0))
            continue;
        
        // On garde le meilleur que l'on a trouvé
        if (abs(angle) < abs(closest_angle))
        {
            closest = &algue;
            closest_angle = angle;
        }
    }
    return closest;
}

void Simulation::update_corails()
{
    for (unsigned i = 0; i < corails.size(); i++)
    {
        if (corails[i].get_status() == DEAD)
            continue;
        if (corails[i].get_segs().back().get_length() < l_repro)
        {
            alimentation_corail(corails[i]);
        }
        else
        {
            allongement_corail(corails[i]);
            corails[i].switch_st_dev();
        }
    }
}

void Simulation::alimentation_corail(Corail &corail)
{
    double angle;
    if (corail.get_sens_rot() == TRIGO)
        angle = delta_rot;
    else
        angle = -delta_rot;
    Algue* algue_ptr = closest_algue(corail, angle);
    if (!turn_corail(corail, angle) or !eat_algue(corail, algue_ptr))
        // Si on arrive pas à tourner ou à manger 
        // on change la direction de rotation
        corail.switch_rot();
}

void Simulation::allongement_corail(Corail &corail)
{
    if (corail.get_status_dev() == EXTEND)
    {
        corail.new_seg();
    }
    else
    {
        reproduction_corail(corail);
    }
}

void Simulation::reproduction_corail(Corail &corail)
{
    Segment& dernier = corail.get_segs().back();
    dernier.set_length(l_seg_interne);
    int id = nouveau_id_corail();
    Carre nouvelle_base(dernier.get_extremity(), d_cor);
    Corail nouveau_corail(nouvelle_base, id,
                          corail.get_status(), corail.get_sens_rot(), EXTEND);
    Segment nouveau_segment(dernier.get_extremity(), dernier.get_angle(), l_nv_seg);
    nouveau_corail.add_seg(nouveau_segment);
    corails.push_back(nouveau_corail);
    dernier.set_length(l_repro/2);
}

int Simulation::nouveau_id_corail()
{
    int id = 1;
    while (id_corail_existe(id))
    {
        id += 1;
    }
    return id;
}

// Essaye de tourner le corail. Renvoie false en cas de collision
bool Simulation::turn_corail(Corail &corail, double delta)
{
    vector<Segment>& segs = corail.get_segs();
    int size = segs.size();
    Segment &dernier = segs[size - 1];
    if (size > 1)
    {
        // Test de superposition pendant la mise à jour de la simulation
        Segment &avant_dernier = segs[size - 2];
        double previous_angle = dernier.angular_gap(avant_dernier);
        dernier.turn(delta);
        double angle = dernier.angular_gap(avant_dernier);

        if (angle <= delta_rot and angle >= -delta_rot and previous_angle*angle < 0)
        {
            // L'angle appartient à l'intervalle  [-delta_rot, delta_rot] et 
            // change de signe
            dernier.turn(-delta);
            return false;
        }
    }
    else
    {
        dernier.turn(delta);
    }

    if (collision(corail)) 
    {
        dernier.turn(-delta);
        return false;
    }
    return true;
}

bool Simulation::collision(Corail corail)
{
    return test_intersection_coraux(corail, false)
    or    !corail.inclusion_dernier_segment(false);
}

// Essaie de manger l'algue. Renvoie false en cas de collision
bool Simulation::eat_algue(Corail &corail, Algue *algue_ptr)
{
    if (algue_ptr == nullptr)
        return true;

    Segment &dernier = corail.get_segs().back();
    dernier.grow(delta_l);

    if (collision(corail))
    {
        dernier.grow(-delta_l);
        return false;
    }

    // On supprime l'algue mangée
    swap(*algue_ptr, algues.back());
    algues.pop_back();
    return true;
}
void Simulation::verif_corail_eaten(Scavenger &sca)
{
    if (dead_corails.size()!= 0)
    {
        Corail *c_who_dead = dead_corails[0];
        if ((sca.get_cible() == c_who_dead->get_id()) and sca.get_etat() == EATING)
        {
            corails_attaque.push_back(c_who_dead);
            swap(c_who_dead, dead_corails.back());
            dead_corails.pop_back();
        }
    }
}

void Simulation::sca_who_eat()
{
    for (auto &sca : scavengers)
    {   
        if (dead_corails.size() != 0) //Cette cond est pas utile je crois
        {
            Corail* c_who_eaten = dead_corails[0];
            if (sca.get_etat() == FREE)
            {   
                sca.set_cible(c_who_eaten->get_id());        
                mouvement_sca(sca, c_who_eaten);
            }
            verif_corail_eaten(sca);
        }
    }
}

void Simulation::mouvement_sca(Scavenger &sca, Corail *c_who_eaten)
{
    Segment& dernier_seg = c_who_eaten->get_segs().back();
    S2d pos = dernier_seg.get_extremity();
    sca.deplacement(pos);
    if (sca.get_etat() == EATING)
    {
        eating_sca.push_back((&sca));
    }
}

void Simulation::manger_corail()
{
    for(auto &corail : corails_attaque)
    {
        for(auto &sca : eating_sca)
        {
            if ((*sca).get_cible() == (*corail).get_id())
                manger_segment(corail, sca);
        }
    }
}

void Simulation::manger_segment(Corail* c_attaque, Scavenger* sca_eat)
{
    int size = c_attaque->get_segs().size();
    if (size != 0 )
    {
        // Racourcissement
        Segment &dernier_seg = c_attaque->get_segs().back();
        S2d pos = dernier_seg.get_base();
        sca_eat->deplacement(pos);
        c_attaque->raccourcissement(pos, sca_eat->get_pos());
    }
    else
    {
        // Disparition

        // //swap((*c_attaque), corails_attaque.back());
        // //corails_attaque.pop_back();
        // (*sca_eat).set_etat(FREE);
        // (*sca_eat).set_cible(0);
        // //swap((*sca_eat), eating_sca.back());
        // //eating_sca.pop_back();
        // //cout << "(*c_attaque)" << (*c_attaque).get_id() << endl;
        // //cout << "Avant changement :" << corails[corails.size() -1].get_id() << endl;
        // swap((*c_attaque), corails.back());
        // //cout << "Apres changement :" << corails[corails.size() -1].get_id() << endl;
        // corails.pop_back();
    }
}

void Simulation::bebe_sca(Scavenger &sca)
{
    bool repro = sca.croissance();
    if (repro)
    {
        Cercle c(sca.get_pos(), r_sca); // la pos doit etre decallée
        Scavenger bebe(c, FREE, 0);
        scavengers.push_back(bebe);
    }
}

/*void Simulation::verif_sca_free()
{
    if (sca.get_pos() == pos)
    {
        sca.set_etat(FREE);

    }
}*/

void Simulation::step()
{
    nb_sim += 1;

    disparition(algues, max_life_alg);
    spawn_algue();

    mort_corails();   
    update_corails();

    disparition(scavengers, max_life_sca);
    sca_who_eat();
    manger_corail();
}

void Simulation::spawn_algue()
{
    if (!naissance_algue) return;
    double p(alg_birth_rate);
    bernoulli_distribution b(p);
    if (b(random_engine))
    {
        uniform_int_distribution<unsigned> u(1, dmax-1);
        double x = u(random_engine);
        double y = u(random_engine);
        Algue nouvelle_algue(x, y);
        ajouter_algue(nouvelle_algue);
    }
}


void Simulation::reset()
{
    algues.clear();
    corails.clear();
    scavengers.clear();
    dead_corails.clear();
    corails_attaque.clear();
    eating_sca.clear();
    random_engine.seed(1);

    nb_sim = 0;
    naissance_algue = false;

    lecture_finie = false;
    lecture_error = false;

    etat = NbAlg;
    compteur_entite = 0;
    total_entite = 0;
    compteur_segments = 0;
    total_segments = 0;
}