#ifndef PROJECTILE_H_FILE
#define PROJECTILE_H_FILE

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <SDL2/SDL.h>
#include "utils.h"

class Projectile {
private:
    // world position stuff
    SDL_Rect initial_projectile_world_pos;
    SDL_Rect projectile_world_pos;
    int max_range;  // the number of tiles the projectile can travel without exploding if it doesn't first collide with something or exceed max_frames
    int max_frames; // the number of frames the projectiel can travel without exploding if it doesn't exceed max_range or collide with something
    int cur_frames;

    // velocity stuff
    double velocity_x;
    double velocity_y;

    // rendering stuff
    SDL_Texture* texture;
    SDL_Renderer* renderer;

    // state
    bool alive; // true = not exploded, false = exploded
public:
    Projectile(SDL_Rect projectile_world_pos, int max_range, int max_frames, SDL_Texture* texture, SDL_Renderer* renderer, double velocity_x, double velocity_y);
    void Update(double dt); // used to update a projectile's position. should only be called once a frame
    void Explode(); // to be used if it hits a surface or whatever
    SDL_Rect GetPos();
    void Render(SDL_Rect camera_pos);   // used to render a projectile to the screen. should only be called once a frame
    bool GetState();
};

class ProjectileSystem {
private:
    std::vector<Projectile> projectiles;
public:
    void AddProjectile(Projectile projectile);
    void UpdateAll(double dt, SDL_Rect camera_pos);
    std::vector<Projectile> GetProjectiles();
    void ExplodeProjectile(size_t num);
};

#endif // PROJECTILE_H_FILE