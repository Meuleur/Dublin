// graphics.cpp
#include "graphics.h"
#include "GeoDraw.h"
#include "types.h"
#include "game.h"
#include "physics.h"

void draw_terrain() {
    gd_setCanvasColor(0.0, 0.8, 0.0); // Vert pour l'herbe
    gd_clear();
}

void draw_hole(Hole *hole) {
    gd_setFillColor(BLACK);
    gd_circleFilled(hole->position.x, hole->position.y, hole->radius);
}

void draw_bunkers(Terrain *terrain) {
    gd_setFillColor(210, 180, 140); // Couleur sable

    for (int i = 0; i < terrain->bunker_count; i++) {
        Bunker *bunker = &terrain->bunkers[i];

        double x = bunker->position.x;
        double y = bunker->position.y;
        double width = bunker->width;
        double height = bunker->height;
        double radius = (width < height ? width : height) * 0.2;

        if (radius > 20) radius = 20;

        // Dessiner le corps du bunker
        gd_quadFilled(
                x + radius, y,
                x + width - radius, y,
                x + width - radius, y + height,
                x + radius, y + height
        );

        // Dessiner les côtés
        gd_quadFilled(
                x, y + radius,
                x + radius, y + radius,
                x + radius, y + height - radius,
                x, y + height - radius
        );

        gd_quadFilled(
                x + width - radius, y + radius,
                x + width, y + radius,
                x + width, y + height - radius,
                x + width - radius, y + height - radius
        );

        // Dessiner les coins arrondis
        gd_circleFilled(x + radius, y + radius, radius);
        gd_circleFilled(x + width - radius, y + radius, radius);
        gd_circleFilled(x + width - radius, y + height - radius, radius);
        gd_circleFilled(x + radius, y + height - radius, radius);
    }
}

void draw_rocks(Terrain *terrain){




}

void gd_rectangleFilled(double x1, double y1, double x2, double y2) {
    for (double y = y1; y <= y2; y++) {
        gd_line(x1, y, x2, y);
    }
}
void draw_ball(Ball *ball) {
    gd_setFillColor(BLUE);
    std::string js_command = "ctx.beginPath();\n"
                             "ctx.fillStyle = 'rgb(255,255,255)';\n" // WHITE
                             "ctx.arc(" + gd_to_string(ball->position.x) + ", " + gd_to_string(ball->position.y) +
                             ", " + gd_to_string(static_cast<int>(ball->radius)) + ", 0, 2 * Math.PI);\n"
                                                                                   "ctx.fill();\n";
    std::cout << "Drawing ball: " << js_command << std::endl; // Ligne de débogage
    gd_circleFilled(ball->position.x, ball->position.y, ball->radius);
}

void draw_walls(Terrain *terrain) {
    // Définir la couleur et l'épaisseur du stylo pour les murs
    gd_setPenColor(BLACK);
    gd_setPenWidth(15);

    double x = 0;
    double y = 0;
    double width = terrain->width;
    double height = terrain->height;

    // Dessiner les quatre côtés du rectangle
    gd_line(x, y, x + width, y);                 // Ligne supérieure
    gd_line(x + width, y, x + width, y + height); // Ligne droite
    gd_line(x + width, y + height, x, y + height); // Ligne inférieure
    gd_line(x, y + height, x, y);                 // Ligne gauche
}

void draw_scene(Ball *ball, Hole *hole, Terrain *terrain) {
    draw_terrain();
    draw_bunkers(terrain);
    draw_hole(hole);

    draw_ball(ball);
    draw_walls(terrain);
    gd_save("MiniGolf.html");
}
