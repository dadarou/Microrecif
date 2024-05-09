// project.cc : Point d'entrée du projet
// Auteurs : Daniel Roulin (50%) & Joshua Hurlimann (50%)
// Version 2

#include <iostream>
#include <string>
#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include "simulation.h"
#include "gui.h"
using namespace std;

int main(int argc, char *argv[])
{
    Simulation simulation;
    if (argc == 2)
    {
        simulation.lecture(argv[1]);
    }
    else if (argc > 2)
    {
        cout << "Error: too many arguments" << endl;
        exit(EXIT_FAILURE);
    }

    auto app = Gtk::Application::create();
    return app->make_window_and_run<Window>(1, argv, simulation);
}
