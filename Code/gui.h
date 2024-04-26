// gui.h : Entête de gui.cc
// Auteurs : Daniel Roulin & Joshua Hurlimann
// Version 2

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
    Simulation &simulation;
    Gtk::Box main_box;
    Gtk::Box gui_box;
    Gtk::Button button_exit;
    Gtk::Button button_open;
    Gtk::Button button_save;
    Gtk::Button button_start_stop;
    Gtk::Button button_step;
    Gtk::CheckButton button_birth;
    Gtk::Label label_titre;
    Gtk::Label label_nb_sim;
    Gtk::Label label_nb_algues;
    Gtk::Label label_nb_corails;
    Gtk::Label label_nb_scavengers;
    DrawingArea drawing_area;

    bool button_is_start;
    bool stop_clicked;

    // Button signal handlers
    void on_button_clicked_exit();
    void on_button_clicked_open();
    void on_button_clicked_save();
    void on_button_clicked_step();
    void on_button_clicked_birth();
    void on_button_clicked_start_stop();
    void on_button_clicked_start();
    void on_button_clicked_stop();
    bool on_timer_timeout();

    bool on_key_pressed(guint keyval, guint, Gdk::ModifierType state);
    void on_file_dialog_response(int response_id, Gtk::FileChooserDialog* dialog,
                                 bool saving);

    void step();
    void update_labels();
    void reset();
};

#endif