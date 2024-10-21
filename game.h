// game.h
#ifndef GAME_H
#define GAME_H

#include "types.h"

void initialize_game(Ball *ball, Hole *hole, Terrain *terrain);
void initialize_hole(Hole *hole, Ball *ball, double terrain_width, double terrain_height);
void initialize_bunkers(Terrain *terrain);
void initialize_walls(Terrain *terrain, double width, double height) ;
void initialize_canvas(Terrain *terrain);

#endif // GAME_H
