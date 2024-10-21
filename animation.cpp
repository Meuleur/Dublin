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
    double base_friction = terrain->friction_coefficient;
    double deltaTime = 0.1; // Temps entre chaque mise à jour (en secondes)
    const double VELOCITY_THRESHOLD = 1; // Pixels par seconde
    const double SECOND_HIT_SPEED = 100.0; // Vitesse pour le deuxième coup (pixels par seconde)

    // Variable pour suivre la vitesse précédente
    double previous_speed = std::sqrt(ball->velocity.x * ball->velocity.x + ball->velocity.y * ball->velocity.y);

    // Définir une vitesse initiale vers le trou
    double dx = hole->position.x - ball->position.x;
    double dy = hole->position.y - ball->position.y;
    double distance = std::sqrt(dx * dx + dy * dy);
    srand(time(NULL));
    double speed = 100; // Pixels par seconde

    if (distance != 0) {
        ball->velocity.x = (dx / distance) * speed ;
        ball->velocity.y = (dy / distance) * speed;
    }

    cout << "Initial Position: (" << ball->position.x << ", " << ball->position.y << ")" << endl;
    cout << "Initial Velocity: (" << ball->velocity.x << ", " << ball->velocity.y << ")" << endl;

    int max_frames = 200; // Limite à 200 frames pour le test
    for (int frame = 0; frame < max_frames; frame++) {

        dx = ball->position.x - hole->position.x;
        dy = ball->position.y - hole->position.y;
        distance = std::sqrt(dx * dx + dy * dy);

        if (distance <= hole->radius) {
            cout << "La balle est dans le trou !" << endl;


            break;
        }

        double bunker_friction = 0.0;
        bool in_bunker = is_ball_in_bunker(ball, terrain, bunker_friction);

        double current_friction = base_friction;
        if (in_bunker) {
            current_friction = bunker_friction;
            cout << "Frame " << frame << ": La balle est dans un bunker. Friction ajustée à " << current_friction
                 << endl;
        }

        // Mettre à jour la position de la balle avec la friction actuelle
        update_ball_position(ball, current_friction, deltaTime);

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
        draw_terrain();         // Efface et dessine le terrain
        draw_bunkers(terrain);  // Dessine les bunkers
        draw_hole(hole);
        draw_walls(terrain);
        draw_ball(ball);         // Dessine la balle à la nouvelle position

        // Ajouter une pause pour l'animation
        gd_pause(static_cast<unsigned int>(deltaTime * 1000)); // Convertir en millisecondes
    }
}

double clamp(double value, double min, double max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

// Fonction pour vérifier si la balle est dans un bunker
bool is_ball_in_bunker(const Ball *ball, const Terrain *terrain, double &bunker_friction) {
    for (int i = 0; i < terrain->bunker_count; ++i) {
        const Bunker *bunker = &terrain->bunkers[i];

        // Calculer le point le plus proche de la balle sur le rectangle du bunker
        double closest_x = clamp(ball->position.x, bunker->position.x, bunker->position.x + bunker->width);
        double closest_y = clamp(ball->position.y, bunker->position.y, bunker->position.y + bunker->height);

        // Calculer la distance entre la balle et ce point
        double distance_x = ball->position.x - closest_x;
        double distance_y = ball->position.y - closest_y;
        double distance_sq = (distance_x * distance_x) + (distance_y * distance_y);


        if (distance_sq <= (ball->radius * ball->radius)) {

            bunker_friction = terrain->friction_coefficient + bunker->friction_coefficient;
            return true;
        }
    }
    return false;
}


void random_animate_ball(Ball *ball, Hole *hole, Terrain *terrain) {
    double base_friction = terrain->friction_coefficient;
    double deltaTime = 0.1; // Temps entre chaque mise à jour (en secondes)
    const double VELOCITY_THRESHOLD = 1; // Pixels par seconde
    const double MAX_RANDOM_SPEED = 150.0; // Vitesse maximale aléatoire (pixels par seconde)
    const double MIN_RANDOM_SPEED = 50.0;  // Vitesse minimale aléatoire (pixels par seconde)

    // Initialiser le générateur de nombres aléatoires
    srand(time(NULL));

    // Fonction pour générer une nouvelle direction et vélocité aléatoires
    auto generate_random_velocity = [&]() {
        double random_angle = (rand() % 360) * (M_PI / 180); // Angle aléatoire en radians
        double random_speed = MIN_RANDOM_SPEED + static_cast<double>(rand()) / RAND_MAX * (MAX_RANDOM_SPEED - MIN_RANDOM_SPEED); // Vélocité aléatoire entre MIN_RANDOM_SPEED et MAX_RANDOM_SPEED
        ball->velocity.x = cos(random_angle) * random_speed;
        ball->velocity.y = sin(random_angle) * random_speed;
    };

    // Initialiser la première direction et vélocité aléatoires
    generate_random_velocity();

    // Afficher la position initiale
    cout << "Random Ball Initial Position: (" << ball->position.x << ", " << ball->position.y << ")" << endl;
    cout << "Random Ball Initial Velocity: (" << ball->velocity.x << ", " << ball->velocity.y << ")" << endl;

    int max_frames = 200; // Limite à 200 frames pour le test
    for (int frame = 0; frame < max_frames; frame++) {
        // Calculer la distance actuelle de la balle au trou
        double dx = ball->position.x - hole->position.x;
        double dy = ball->position.y - hole->position.y;
        double distance = std::sqrt(dx * dx + dy * dy);

        // Vérifier si la balle est dans le trou
        if (distance <= hole->radius) {
            cout << "Random Ball is in the hole!" << endl;
            break;
        }

        // Calculer la vitesse actuelle de la balle
        double current_speed = std::sqrt(ball->velocity.x * ball->velocity.x + ball->velocity.y * ball->velocity.y);

        // Si la vitesse est inférieure au seuil, générer une nouvelle direction et vélocité aléatoires
        if (current_speed < VELOCITY_THRESHOLD) {
            generate_random_velocity();
            cout << "Frame " << frame << ": Nouvelle direction et vélocité aléatoires appliquées." << endl;
        }

        // Gérer la collision avec les murs
        handle_wall_collision(ball, terrain);

        // Mettre à jour la position de la balle en fonction de sa vitesse et de la friction
        update_ball_position(ball, base_friction, deltaTime);

        // Afficher la position mise à jour
        cout << "Frame " << frame << " Updated Position: ("
             << ball->position.x << ", "
             << ball->position.y << "), Distance to hole: "
             << distance << ", Current Speed: "
             << current_speed << endl;

        // Redessiner la scène avec la nouvelle position de la balle
        draw_terrain();         // Efface et dessine le terrain
        draw_bunkers(terrain);  // Dessine les bunkers
        draw_hole(hole);
        draw_walls(terrain);
        draw_ball(ball);         // Dessine la balle à la nouvelle position

        // Ajouter une pause pour l'animation
        gd_pause(static_cast<unsigned int>(deltaTime * 1000)); // Convertir en millisecondes
    }
}