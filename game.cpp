// game.c
#include <stdlib.h>
#include <time.h>
#include "types.h"
#include <cmath>
#include "GeoDraw.h"

void initialize_bunkers(Terrain *terrain) {
    int bunker_count=3 + rand()%8;
    terrain->bunker_count = bunker_count;
    terrain->bunkers = (Bunker *)malloc(sizeof(Bunker) * bunker_count);

    if (terrain->bunkers == NULL) {
        std::cerr << "Erreur d'allocation mémoire pour les bunkers." << std::endl;
        exit(EXIT_FAILURE);
    }

    int min_size = 30; // Taille minimale des bunkers
    int max_size = 200; // Taille maximale des bunkers

    srand(time(NULL)); // Initialiser le générateur aléatoire

    for (int i = 0; i < bunker_count; i++) {
        Bunker *bunker = &terrain->bunkers[i];

        // Attribuer des tailles aléatoires
        bunker->width = min_size + rand() % (max_size - min_size + 1);
        bunker->height = min_size + rand() % (max_size - min_size + 1);

        // Attribuer un coefficient de friction aléatoire entre 0.3 et 0.7
        bunker->friction_coefficient = 0.5 ;

        double terrain_width = terrain->width;
        double terrain_height = terrain->height;

        // Générer des positions aléatoires en s'assurant que le bunker est entièrement sur le terrain
        // Éviter de placer les bunkers trop près du trou ou du point de départ
        bool position_valide = false;
        while (!position_valide) {
            bunker->position.x = rand() % (int)(terrain_width - bunker->width);
            bunker->position.y = rand() % (int)(terrain_height - bunker->height);

            // Vérifier la distance par rapport au trou et à la balle pour éviter les placements gênants
            double dx = bunker->position.x - terrain->width / 2;
            double dy = bunker->position.y - terrain->height / 2;
            double distance = std::sqrt(dx * dx + dy * dy);

            if (distance > 10.0) { // Ajuster selon besoin
                position_valide = true;
            }
        }
    }
}

void initialize_hole(Hole *hole, Ball *ball, double terrain_width, double terrain_height) {

    hole->radius = 10;

    do {
        hole->position.x = hole->radius + rand() % (int)(600 - 2 * hole->radius);
        hole->position.y = hole->radius + rand() % (int)(600 - 2 * hole->radius);
    } while (fabs(hole->position.x - ball->position.x) < 100 && fabs(hole->position.y - ball->position.y) < 100);
}

void initialize_game(Ball *ball, Hole *hole, Terrain *terrain) {
    // Initialiser le terrain
    terrain->width = 600;
    terrain->height = 600;
    terrain->friction_coefficient = 0.1; // Coefficient de friction de base

    // Initialiser la balle
    ball->position.x = ball->radius + rand() % (int)(terrain->width - 2 * ball->radius);
    ball->position.y = ball->radius + rand() % (int)(terrain->height - 2 * ball->radius);
    ball->velocity.x = 0;
    ball->velocity.y = 0;
    ball->radius = 10;

    // Initialiser le trou
    initialize_hole(hole, ball, terrain->width, terrain->height);

    // Initialiser les bunkers
    initialize_bunkers(terrain);

    // Configurer le canvas
    gd_resetCanvasSize(terrain->width, terrain->height);
}
void initialize_canvas(Terrain *terrain) {
    gd_resetCanvasSize(terrain->width, terrain->height);
}
void initialize_walls(Terrain *terrain, double width, double height) {
    // Mur supérieur
    terrain->walls[0].x1 = 0;
    terrain->walls[0].y1 = 0;
    terrain->walls[0].x2 = width;
    terrain->walls[0].y2 = 0;

    // Mur droit
    terrain->walls[1].x1 = width;
    terrain->walls[1].y1 = 0;
    terrain->walls[1].x2 = width;
    terrain->walls[1].y2 = height;

    // Mur inférieur
    terrain->walls[2].x1 = width;
    terrain->walls[2].y1 = height;
    terrain->walls[2].x2 = 0;
    terrain->walls[2].y2 = height;

    // Mur gauche
    terrain->walls[3].x1 = 0;
    terrain->walls[3].y1 = height;
    terrain->walls[3].x2 = 0;
    terrain->walls[3].y2 = 0;

    terrain->wall_count = 4;
}