#include "project.h"
#include "simulation.h"
#include <iostream>
#include <string>
using namespace std;

int main()
{
    //je crois que ici on doit faire avec les argc argv 
    string nom_fichier;
    cin >> nom_fichier;
    Lecture(nom_fichier);
    return 0;
}
