// types.h
#ifndef MINIGOLF_TYPES_H
#define MINIGOLF_TYPES_H
#define MAX_WALLS 4

typedef unsigned int u_int;

typedef struct {
    double x;
    double y;
} Vector2D;

typedef struct {
    Vector2D position;
    Vector2D velocity; // Ajoutez 'velocity' si ce n'est pas déjà fait
    double radius;
} Ball;

typedef struct {
    Vector2D position;
    double width;
    double height;
    double friction_coefficient;
} Bunker;


typedef struct {
    Vector2D position;
    double width;
    double height;
    double friction_coefficient;


}Rocks;

typedef struct {
    Vector2D position;
    double radius;
} Hole;


typedef struct {
    double x1, y1; // Coordonnées du premier point du mur
    double x2, y2; // Coordonnées du second point du mur
} Wall;

typedef struct {
    double width;
    double height;
    double friction_coefficient;
    Bunker *bunkers;
    int bunker_count;
    Wall walls[MAX_WALLS];
    int wall_count;
} Terrain;

#endif // MINIGOLF_TYPES_H
