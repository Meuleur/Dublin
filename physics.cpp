// physics.cpp
#include "physics.h"
#include <cmath>
#include "types.h"
#include <iostream> // Pour std::cout

void update_ball_position(Ball *ball, double friction, double deltaTime) {
    // Mettre à jour la position
    ball->position.x += ball->velocity.x * deltaTime;
    ball->position.y += ball->velocity.y * deltaTime;

    // Appliquer la friction
    ball->velocity.x *= (1 - friction);
    ball->velocity.y *= (1 - friction);

    // Si la vitesse est très faible, l'arrêter
    if (std::abs(ball->velocity.x) < 0.01) ball->velocity.x = 0;
    if (std::abs(ball->velocity.y) < 0.01) ball->velocity.y = 0;

    // Ajouter des messages de débogage
    std::cout << "update_ball_position: New Position = ("
              << ball->position.x << ", "
              << ball->position.y << "), New Velocity = ("
              << ball->velocity.x << ", "
              << ball->velocity.y << ")" << std::endl;
}
