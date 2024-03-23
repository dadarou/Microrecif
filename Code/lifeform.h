#ifndef LIFEFORM_H
#define LIFEFORM_H

class Lifeform {
public :
    Lifeform(int age, double x, double y);

private :
    int age;
    double pos_x;
    double pos_y;
};

class Algue : public Lifeform {
public :
    Algue(int age, double x, double y);
private :
    
};

class Corail : public Lifeform {
public :
    Corail(int age, double x, double y, int statut, int sens_rot, int st_dev);
private :
    int statut;
    int sens_rotation;
    int st_developpement;
};

class Scavenger : public Lifeform {
public :
    Scavenger(int age, double x, double y, int etat);
private :
    int etat;
};

void Test_Lifeform(double x, double y, int age);
void Test_Algue();
void Test_Corail();
void Test_Scavenger();

void Decodage_Algue(istringstream& data);


#endif