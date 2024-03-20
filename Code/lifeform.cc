#include "lifeform.h"
#include "shape.h"
#include <string>

Lifeform::Lifeform(double age, double x, double y){
    age = age;
    pos_x = x;
    pos_y = y;
}

Lifeform::int update_age(double age_max){
    if (age++ == age_max){
        return 0; //age est incremente de 1 ou pas ?
    }else{
        return 1; //tjrs en vie
        //est ce que c'est juste de retourner un int
    }
}

///double age_getter(){
///    return age;
///}
///void age_setter(double age){
///    age = age;
///}

Corail::Corail(int statut, int sens_rot, int st_dev){
    statut = statut;
    sens_rotation = sens_rot;
    st_developpement = st_dev;
}

Scavenger::Scavenger(int etat){
    etat = etat;
}