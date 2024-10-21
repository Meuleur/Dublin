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
    Ball ball1;
    Ball ball2;
    Hole hole1;
    Hole hole2;
    Terrain terrain;

    // Initialiser le jeu avec deux balles et deux trous
    initialize_game(&ball1, &hole1, &terrain);
    initialize_game(&ball2, &hole2, &terrain);

    // Configurer le canvas pour l'ensemble du terrain
    gd_resetCanvasSize(terrain.width, terrain.height);

    // Dessiner la scène initiale avec les deux balles
    draw_scene(&ball1, &hole1, &terrain);
    draw_scene(&ball2, &hole2, &terrain);

    // Boucle d'animation principale
    int max_frames = 200;
    for (int frame = 0; frame < max_frames; frame++) {
        // Effacer la scène (si nécessaire)
        gd_clear();

        // Redessiner le terrain, les bunkers, et les murs
        draw_terrain();
        draw_bunkers(&terrain);
        draw_walls(&terrain);

        // Animer la première balle (utilisation de animate_ball)
        animate_ball(&ball1, &hole1, &terrain);

        // Animer la deuxième balle (utilisation de random_animate_ball)
        random_animate_ball(&ball2, &hole2, &terrain);

        // Redessiner les deux balles et les trous
        draw_hole(&hole1);
        draw_ball(&ball1);
        draw_hole(&hole2);
        draw_ball(&ball2);

        // Ajouter une pause pour rendre l'animation visible
        gd_pause(100);  // Ajuster le temps en millisecondes
    }
// Sauvegarder le fichier HTML avec l'animation complète
    gd_save("MiniGolf_Animation.html");

    // Libérer la mémoire allouée pour les bunkers
    free(terrain.bunkers);

    return 0;
}