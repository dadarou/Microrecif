#ifndef GUI_H
#define GUI_H

#include <gtkmm.h>
#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/drawingarea.h>
#include "simulation.h"

class DrawingArea : public Gtk::DrawingArea
{
public:
    DrawingArea(Simulation &s);

private:
    Simulation& simulation;
    void on_draw(const Cairo::RefPtr<Cairo::Context> &cr, int width, int height);
    void projection(const Cairo::RefPtr<Cairo::Context> &cr, int width, int height);
};


class Window : public Gtk::Window
{
public:
    Window(Simulation &s);
    virtual ~Window();

private:
    Simulation& simulation;
    Gtk::Box main_box;
    Gtk::Box buttons_box;
    Gtk::Button button_exit;
    Gtk::Button button_open;
    Gtk::Button button_save;
    Gtk::Button button_start_stop;
    Gtk::Button button_step;
    Gtk::CheckButton button_birth;
    Gtk::Label titre;
    Gtk::Label nb_misaj;
    Gtk::Label nb_algue;
    Gtk::Label nb_corail;
    Gtk::Label nb_scavenger;


    DrawingArea drawing_area;

    // Button signal handlers
    void on_button_clicked_exit();
    void on_button_clicked_open();
    void on_button_clicked_save();
    void on_button_clicked_start_stop();
    void on_button_clicked_step();
    void on_button_clicked_birth();
    void on_file_dialog_response(int response_id, Gtk::FileChooserDialog* dialog, bool saving);
};

#endif