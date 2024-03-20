#ifndef LIFEFORM_H
#define LIFEFORM_H

class Lifeform {
public :
    Lifeform(double age, double x, double y);
    int update_age(double age_max);

private :
    double age;
    double pos_x;
    double pos_y;
};

class Algue {
public :

private :
    
};

class Corail{
public :
    Corail(int statut, int sens_rot, int st_dev);
private :
    int statut;
    int sens_rotation;
    int st_developpement;
};

class Scavenger{
public :
    Scavenger(int etat);
private :
    int etat;
};

#endif