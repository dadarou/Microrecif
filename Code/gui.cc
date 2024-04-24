#include <iostream>
#include <string>
#include "gui.h"
#include "simulation.h"
#include "graphic_gui.h"
#include "constantes.h"

using namespace std;

static const unsigned int TIMEOUT = 250; // Time between updates in ms

Window::Window(Simulation &s) : simulation(s),
                                // Horizontal: buttons a droite, dessins a gauche
                                // 0 pixels de marge entre les deux
                                main_box(Gtk::Orientation::HORIZONTAL, 0),
                                // Vertical: buttons de haut en bas
                                // 2 pixels de marge entre les boutons
                                gui_box(Gtk::Orientation::VERTICAL, 2),
                                button_exit("exit"),
                                button_open("open"),
                                button_save("save"),
                                button_start_stop("start"),
                                button_step("step"),
                                button_birth("Naissance des algues"),
                                label_titre("Info : nombre de..."),
                                // label_nb_sim("mise à jour: 0"),
                                // label_nb_algues("algues: 0"),
                                // label_nb_corails("corails: 0"),
                                // label_nb_scavengers("scavengers: 0"),
                                drawing_area(s),
                                timer_exists(false),
                                timer_disconnect(false)
{
    set_title("Microrécif");
    set_child(main_box);
    main_box.append(gui_box);
    main_box.append(drawing_area);

    // Taille minium de la colonne de droite
    gui_box.set_size_request(200, -1);
    gui_box.append(button_exit);
    gui_box.append(button_open);
    gui_box.append(button_save);
    gui_box.append(button_start_stop);
    gui_box.append(button_step);
    gui_box.append(button_birth);

    gui_box.append(label_titre);
    gui_box.append(label_nb_sim);
    gui_box.append(label_nb_algues);
    gui_box.append(label_nb_corails);
    gui_box.append(label_nb_scavengers);

    button_exit.signal_clicked().connect(
        sigc::mem_fun(*this, &Window::on_button_clicked_exit));

    button_open.signal_clicked().connect(
        sigc::mem_fun(*this, &Window::on_button_clicked_open));

    button_save.signal_clicked().connect(
        sigc::mem_fun(*this, &Window::on_button_clicked_save));

    button_start_stop.signal_clicked().connect(
        sigc::mem_fun(*this, &Window::on_button_clicked_start_stop));
    
    button_step.signal_clicked().connect(
        sigc::mem_fun(*this, &Window::on_button_clicked_step));
    
    button_birth.signal_toggled().connect(sigc::mem_fun(*this,
              &Window::on_button_clicked_birth));
    
    update_labels();
}

Window::~Window()
{
}

void Window::on_button_clicked_exit()
{
    exit(EXIT_SUCCESS);
}

void Window::on_button_clicked_open()
{
    auto dialog = new Gtk::FileChooserDialog("Selectioner un fichier",
                                    Gtk::FileChooser::Action::OPEN);

    dialog->set_transient_for(*this);
    dialog->set_modal(true);
    dialog->signal_response().connect(sigc::bind(
        sigc::mem_fun(*this, &Window::on_file_dialog_response), dialog, false));
    
    dialog->add_button("_Stop", Gtk::ResponseType::CANCEL);
    dialog->add_button("_Ouvrir", Gtk::ResponseType::OK);

    //Add filters, so that only certain file types can be selected:
    auto filter_text = Gtk::FileFilter::create();
    filter_text->set_name("Text files");
    filter_text->add_mime_type("text/plain");
    dialog->add_filter(filter_text);

    auto filter_cpp = Gtk::FileFilter::create();
    filter_cpp->set_name("C/C++ files");
    filter_cpp->add_mime_type("text/x-c");
    filter_cpp->add_mime_type("text/x-c++");
    filter_cpp->add_mime_type("text/x-c-header");
    dialog->add_filter(filter_cpp);

    auto filter_any = Gtk::FileFilter::create();
    filter_any->set_name("Any files");
    filter_any->add_pattern("*");
    dialog->add_filter(filter_any);

    //Show the dialog and wait for a user response:
    dialog->show();
}

void Window::on_button_clicked_save()
{
    auto dialog = new Gtk::FileChooserDialog("Sélectionner un fichier",
		  Gtk::FileChooser::Action::SAVE);
	dialog->set_transient_for(*this);
	dialog->set_modal(true);
	dialog->signal_response().connect(sigc::bind(
	    sigc::mem_fun(*this, &Window::on_file_dialog_response), dialog, true));
	
	//Add response buttons to the dialog:
	dialog->add_button("_Stop", Gtk::ResponseType::CANCEL);
	dialog->add_button("_Ouvrir", Gtk::ResponseType::OK);
	
	//Add filters, so that only certain file types can be selected:
	
	auto filter_text = Gtk::FileFilter::create();
	filter_text->set_name("Text files");
	filter_text->add_mime_type("text/plain");
	dialog->add_filter(filter_text);
	
	auto filter_cpp = Gtk::FileFilter::create();
	filter_cpp->set_name("C/C++ files");
	filter_cpp->add_mime_type("text/x-c");
	filter_cpp->add_mime_type("text/x-c++");
	filter_cpp->add_mime_type("text/x-c-header");
	dialog->add_filter(filter_cpp);
	
	auto filter_any = Gtk::FileFilter::create();
	filter_any->set_name("Any files");
	filter_any->add_pattern("*");
	dialog->add_filter(filter_any);
	
	//Show the dialog and wait for a user response:
	dialog->show();
}

void Window::on_button_clicked_start_stop()
{
    if (not timer_exists)
    {
		sigc::slot<bool()> my_slot = sigc::bind(sigc::mem_fun(*this,
		                                        &Window::on_timer_timeout));
        Glib::signal_timeout().connect(my_slot, TIMEOUT);
		timer_exists = true;
        button_start_stop.set_label("stop");
    }
    else
    {
        timer_disconnect = true;   
		timer_exists = false;
        button_start_stop.set_label("start");
    }
}

bool Window::on_timer_timeout()
{
    if (timer_disconnect)
    {
        timer_disconnect = false;
        return false;
    }
    step();
    return true;
}

void Window::on_button_clicked_step()
{
    step();
}

void Window::on_button_clicked_birth()
{
    simulation.set_birth(button_birth.get_active());
}

void Window::on_file_dialog_response(int response_id, Gtk::FileChooserDialog* dialog, bool saving)
{
    if (response_id == Gtk::ResponseType::OK)
    {
        auto fichier = dialog->get_file()->get_path();
        if (saving)
            simulation.sauvegarde(fichier);
        else
            simulation.lecture(fichier);
    }
    delete dialog;
}

void Window::step()
{
    simulation.step();
    update_labels();
    drawing_area.queue_draw();
}

void Window::update_labels()
{
    string sim_text = "mise à jour: " + to_string(simulation.get_nb_sim());
    string algues_text = "algues: " + to_string(simulation.get_nb_algues());
    string corails_text = "corails: " + to_string(simulation.get_nb_corails());
    string scavengers_text = "charognards: " 
                             + to_string(simulation.get_nb_scavengers());
    
    label_nb_sim.set_text(sim_text);
    label_nb_algues.set_text(algues_text);
    label_nb_corails.set_text(corails_text);
    label_nb_scavengers.set_text(scavengers_text);
}


DrawingArea::DrawingArea(Simulation &s) : simulation(s)
{
    // On choisis arbitrairement que la taille initiale de la fenêtre de dessin
    // soit le double de sa taille minimale
    set_content_width(dmax*2);
    set_content_height(dmax*2);
    // On permet à la zone de dessin de prendre l'espace horizontal
    set_hexpand(true);
    set_draw_func(sigc::mem_fun(*this, &DrawingArea::on_draw));
}

void DrawingArea::on_draw(const Cairo::RefPtr<Cairo::Context> &cr,
                          int width, int height)
{
    graphic_set_context(cr);
    projection(cr, width, height);

    set_color(BLANC);
    background();

    set_color(GRIS);
    dessin_carre(0, 0, 256);

    simulation.dessin();
}

void DrawingArea::projection(const Cairo::RefPtr<Cairo::Context> &cr,
                             int width, int height)
{
    double new_aspect_ratio = (double) width/height;
    double x_max, x_min, y_min, y_max;
    if (new_aspect_ratio > 1.0)
    {
        x_max = dmax/2 + (new_aspect_ratio/1.0)*dmax/2;
        x_min = dmax/2 - (new_aspect_ratio/1.0)*dmax/2;
        y_max = dmax;
        y_min = 0.0;
    }
    else
    {
        x_max = dmax;
        x_min = 0.0;
        y_max = dmax/2 + (1.0/new_aspect_ratio)*dmax/2;
        y_min = dmax/2 - (1.0/new_aspect_ratio)*dmax/2;
    }

    cr->translate(width/2, height/2);
    cr->scale(width/(x_max - x_min), -height/(y_max - y_min));
    cr->translate(-(x_min + x_max)/2, -(y_min + y_max)/2);
}