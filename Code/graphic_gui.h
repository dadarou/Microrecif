// graphic_gui.h : Entête de graphic.cc destinée à être incluse uniquement par gui.cc
// Auteurs : Daniel Roulin
// Version 3

#ifndef GRAPHIC_GUI_H
#define GRAPHIC_GUI_H

#include <gtkmm/drawingarea.h>
#include "graphic.h"

void graphic_set_context(const Cairo::RefPtr<Cairo::Context>& cr);

#endif
