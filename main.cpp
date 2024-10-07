//main

#include "types.h"
#include "GeoDraw.h"
#include "graphics.h"
#include "game.h"
#include "physics.h"
#include "animation.h"
#include <iostream>

using namespace GeoDraw;
int main() {
    Ball ball;
    Hole hole;
    Terrain terrain;

    initialize_game(&ball, &hole, &terrain);

    // Configurer le canvas
    gd_resetCanvasSize(terrain.width, terrain.height);

    // Dessiner la scène initiale
    draw_scene(&ball, &hole, &terrain);

    // Démarrer l'animation
    animate_ball(&ball, &hole, &terrain);

    // Sauvegarder le fichier HTML avec l'animation
    gd_save("MiniGolf_Animation.html");

    // Libérer la mémoire allouée pour les bunkers
    free(terrain.bunkers);


    return 0;
}