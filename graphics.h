//
// Created by Jb Caron on 02/10/2024.
//
//graphics.h
#ifndef MINIGOLF_GRAPHICS_H
#define MINIGOLF_GRAPHICS_H
#include "types.h"



void draw_terrain();
void draw_hole(Hole *hole);
void draw_ball( Ball *ball);
void draw_bunkers(Terrain *terrain);
void draw_scene(Ball *ball, Hole *hole, Terrain *terrain);
void gd_rectangleFilled(double x1, double y1, double x2, double y2);
void draw_walls(Terrain *terrain);
void draw_rectangle(int x, int y, int width, int height);

#endif // MINIGOLF_GRAPHICS_H

