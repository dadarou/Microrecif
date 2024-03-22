#ifndef LIFEFORM_H
#define LIFEFORM_H

class Lifeform {
public :
    Lifeform(double age, double x, double y);
    int Update_age(double age_max);

private :
    double age;
    double pos_x;
    double pos_y;
};

class Algue : public Lifeform {
public :
    Algue(double age, double x, double y);
//pour appel de constructeur de la super class on pourrakt utiliser nouvelle methode de c++11
private :
    
};

class Corail : public Lifeform {
public :
    Corail(double age, double x, double y, int statut, int sens_rot, int st_dev);
private :
    int statut;
    int sens_rotation;
    int st_developpement;
};

class Scavenger : public Lifeform {
public :
    Scavenger(double age, double x, double y, int etat);
private :
    int etat;
};

#endif