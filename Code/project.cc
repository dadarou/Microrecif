#include "simulation.h"
#include <iostream>
#include <string>
using namespace std;

int main(int argc, char* argv[])
{
    if (argc != 2){
        exit(EXIT_FAILURE);
    }
    Lecture(argv[1]);
    return 0;
}
