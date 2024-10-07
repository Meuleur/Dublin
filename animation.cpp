// animation.cpp
#include "animation.h"
#include "physics.h"
#include "graphics.h"
#include "game.h"
#include "GeoDraw.h"
#include "types.h"
#include <cmath>
#include <iostream>

using namespace std;

void animate_ball(Ball *ball, Hole *hole, Terrain *terrain) {
    double friction = terrain->friction_coefficient;
    double deltaTime = 0.1; // Temps entre chaque mise à jour (en secondes)
    const double VELOCITY_THRESHOLD = 15.0; // Pixels par seconde
    const double SECOND_HIT_SPEED = 100.0; // Vitesse pour le deuxième coup (pixels par seconde)

    // Variable pour suivre la vitesse précédente
    double previous_speed = std::sqrt(ball->velocity.x * ball->velocity.x + ball->velocity.y * ball->velocity.y);

    // Définir une vitesse initiale vers le trou
    double dx = hole->position.x - ball->position.x;
    double dy = hole->position.y - ball->position.y;
    double distance = std::sqrt(dx * dx + dy * dy);
    double speed = 100.0; // Pixels par seconde

    if (distance != 0) {
        ball->velocity.x = (dx / distance) * speed;
        ball->velocity.y = (dy / distance) * speed;
    }

    cout << "Initial Position: (" << ball->position.x << ", " << ball->position.y << ")" << endl;
    cout << "Initial Velocity: (" << ball->velocity.x << ", " << ball->velocity.y << ")" << endl;

    int max_frames = 200; // Limite à 200 frames pour le test
    for (int frame = 0; frame < max_frames; frame++) {
        // Vérifier si la balle est dans le trou
        dx = ball->position.x - hole->position.x;
        dy = ball->position.y - hole->position.y;
        distance = std::sqrt(dx * dx + dy * dy);

        if (distance <= hole->radius) {
            cout << "La balle est dans le trou !" << endl;
            break;
        }

        // Mettre à jour la position de la balle
        update_ball_position(ball, friction, deltaTime);

        // Calculer la vitesse actuelle
        double current_speed = std::sqrt(ball->velocity.x * ball->velocity.x + ball->velocity.y * ball->velocity.y);

        // Vérifier si la vitesse est en dessous du seuil et si elle était au-dessus dans la frame précédente
        if (distance > hole->radius && current_speed < VELOCITY_THRESHOLD && previous_speed >= VELOCITY_THRESHOLD) {
            // Calculer la direction vers le trou
            double accel_dx = hole->position.x - ball->position.x;
            double accel_dy = hole->position.y - ball->position.y;
            double accel_distance = std::sqrt(accel_dx * accel_dx + accel_dy * accel_dy);

            if (accel_distance != 0) {
                // Réinitialiser la vitesse vers le trou
                ball->velocity.x = (accel_dx / accel_distance) * SECOND_HIT_SPEED;
                ball->velocity.y = (accel_dy / accel_distance) * SECOND_HIT_SPEED;

                cout << "Frame " << frame << ": Coup appliqué vers le trou." << endl;
            }
        }

        // Mettre à jour la vitesse précédente
        previous_speed = current_speed;

        // Afficher la nouvelle position et la distance
        cout << "Frame " << frame << " Updated Position: ("
             << ball->position.x << ", "
             << ball->position.y << "), Distance to hole: "
             << distance << ", Current Speed: "
             << current_speed << endl;

        // Redessiner la scène avec la nouvelle position de la balle
        draw_terrain();   // Efface et dessine le terrain
        draw_bunkers(terrain);
        draw_hole(hole);
        draw_walls(terrain);
        draw_ball(ball);   // Dessine la balle à la nouvelle position

        // Ajouter une pause pour l'animation
        gd_pause(static_cast<unsigned int>(deltaTime * 1000)); // Convertir en millisecondes
    }
}

void animate_ball_simple(Ball *ball, Hole *hole, Terrain *terrain) {
    double friction = terrain->friction_coefficient;
    double deltaTime = 0.1; // Temps entre chaque mise à jour (en secondes)

    // Définir une vitesse initiale uniquement sur l'axe X
    ball->velocity.x = 50; // Pixels par seconde
    ball->velocity.y = 0;

    cout << "Initial Position: (" << ball->position.x << ", " << ball->position.y << ")" << endl;
    cout << "Initial Velocity: (" << ball->velocity.x << ", " << ball->velocity.y << ")" << endl;

    int max_frames = 10; // Limite à 10 frames pour le test
    for (int frame = 0; frame < max_frames; frame++) {
        // Mettre à jour la position de la balle
        update_ball_position(ball, friction, deltaTime);

        // Afficher la nouvelle position
        cout << "Frame " << frame << " Updated Position: (" << ball->position.x << ", " << ball->position.y << ")" << endl;

        // Redessiner la scène avec la nouvelle position de la balle
        draw_terrain();   // Efface et dessine le terrain
        draw_bunkers(terrain);
        draw_hole(hole);
        draw_walls(terrain);
        draw_ball(ball);   // Dessine la balle à la nouvelle position

        // Ajouter une pause pour l'animation
        gd_pause(static_cast<unsigned int>(deltaTime * 1000)); // Convertir en millisecondes
    }
}