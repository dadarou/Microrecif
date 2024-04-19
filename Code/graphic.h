#ifndef GRAPHIC_H
#define GRAPHIC_H

enum Color
{
    BLANC,
    GRIS,
    NOIR,
    ROUGE,
    VERT,
    BLEU,
};

void set_color(Color color);
void background();
void dessin_carre(double x, double y, double cote);
void dessin_cercle(double x, double y, double rayon);
void dessin_line(double x1, double y1, double x2, double y2);

#endif