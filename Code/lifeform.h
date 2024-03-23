#ifndef LIFEFORM_H
#define LIFEFORM_H

class Lifeform {
public :
    Lifeform(double x, double y, int age);

private :
    double pos_x;
    double pos_y;
    int age;
};

class Algue : public Lifeform {
public :
    Algue(double x, double y, int age);
private :
    
};

class Corail : public Lifeform {
public :
    Corail(double x, double y, int age, int id, int statut, int sens_rot, int st_dev, int nb_seg);
private :
    int identite;
    int statut;
    int sens_rotation;
    int st_developpement;
    int nb_segment;
};

class Scavenger : public Lifeform {
public :
    Scavenger(double x, double y, int age, int r, int etat, int id_cible);
private :
    int rayon;
    int etat;
    int identite_cible;
};

void Test_Lifeform(double x, double y, int age);
void Test_Algue();
void Test_Corail();
void Test_Scavenger();

void Decodage_Algue(istringstream& data);
void Decodage_Corail(istringstream& data);
void Decodage_Scavenger(istringstream& data);

#endif