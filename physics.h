// physics.h
#ifndef MINIGOLF_PHYSICS_H
#define MINIGOLF_PHYSICS_H

#include "types.h"

void update_ball_position(Ball *ball, double friction, double deltaTime);

#endif // MINIGOLF_PHYSICS_H