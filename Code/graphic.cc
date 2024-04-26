// graphic.cc : Bibliothèque permettant d'afficher des formes géométriques simples 
// Auteurs : Daniel Roulin (100%)
// Version 2

#include "graphic.h"
#include "graphic_gui.h"

constexpr double LINE_WIDTH = 1;
static const Cairo::RefPtr<Cairo::Context>* ptcr(nullptr);

void graphic_set_context(const Cairo::RefPtr<Cairo::Context>& cr)
{
	ptcr = &cr;
}

void set_color(Color color)
{
	switch (color)
	{
	case BLANC:
		(*ptcr)->set_source_rgb(1., 1., 1.);
		break;
	
	case GRIS:
		(*ptcr)->set_source_rgb(0.5, 0.5, 0.5);
		break;
	
	case NOIR:
		(*ptcr)->set_source_rgb(1., 1., 1.);
		break;
	
	case ROUGE:
		(*ptcr)->set_source_rgb(1., 0., 0.);
		break;
	
	case VERT:
		(*ptcr)->set_source_rgb(0., 1., 0.);
		break;
	
	case BLEU:
		(*ptcr)->set_source_rgb(0., 0., 1.);
		break;
	}
}

void background()
{
    (*ptcr)->paint();
}

void dessin_carre(double x, double y, double cote)
{
	(*ptcr)->set_line_width(LINE_WIDTH);
	(*ptcr)->rectangle(x, y, cote, cote);
    (*ptcr)->stroke();
}

void dessin_cercle(double x, double y, double rayon)
{
	(*ptcr)->set_line_width(LINE_WIDTH);
  	(*ptcr)->arc(x, y, rayon, 0.0, 2.0 * M_PI);
  	(*ptcr)->stroke();
}

void dessin_line(double x1, double y1, double x2, double y2)
{
	(*ptcr)->set_line_width(LINE_WIDTH);
	(*ptcr)->move_to(x1, y1);
    (*ptcr)->line_to(x2, y2);
    (*ptcr)->stroke();
}