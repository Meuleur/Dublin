//
// Created by Jb Caron on 07/10/2024.
//

#ifndef MINIGOLF_ANIMATION_H
#define MINIGOLF_ANIMATION_H
#include "types.h"

void animate_ball(Ball *ball, Hole *hole, Terrain *terrain);
bool is_ball_in_bunker(const Ball *ball, const Terrain *terrain, double &bunker_friction);
double clamp(double value, double min, double max);
void random_animate_ball(Ball *ball, Hole *hole, Terrain *terrain);


#endif //MINIGOLF_ANIMATION_H
