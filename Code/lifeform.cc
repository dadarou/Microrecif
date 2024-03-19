#include "lifeform.h"
#include "shape.h"
#include <string>

class Lifeform {
public :
    Lifeform(double age, double x, double y){
        age = age;
        pos_x = x;
        pos_y = y;
    }
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
    Corail(int statut, string sens_rot, string st_dev){
        statut = statut;
        sens_rotation = sens_rot;
        st_developpement = st_dev;
    }
private :
    int statut;
    string sens_rotation;
    string st_developpement;
};

class Scavenger{
public :
    Scavenger(string etat){
        etat = etat;
    }
private :
    string etat;
};