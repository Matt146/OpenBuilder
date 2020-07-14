#ifndef CAMERA_H_FILE
#define CAMERA_H_FILE

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include <map>
#include "map.h"
#include "character.h"

// Responsible for rendering the map

// @TODO THERE MIGHT BE AN ERROR WITH STORING THE TEXTURES AS CHARS, AS I MAY
// HAVE FORGOTTEN TO REFACTOR OTHER PARTS FROM CHAR TO INT

class Camera {
private:
    // renderer
    SDL_Renderer* renderer;

    // all have their own ID's defined in utils.h
    std::map<int, SDL_Texture*> textures;
    
    // the world position of the top left of the screen, which is the origin of the screen coordinate system
    SDL_Rect world_pos_tl;   // this is the camera_pos

    // velocity stuff
    double velocity_x;
    double velocity_y;
    double velocity_x_goal;
    double velocity_y_goal;

    // collision stuff
    bool collision_left;
    bool collision_right;
    bool collision_top;
    bool collision_bottom;
public:
    // Constructors
    Camera(SDL_Renderer* renderer, std::map<int, SDL_Texture*> textures);

    // Movement Systems
    // Character handles this through SetVelocity, SetVelocityGoal, and SetPos

    // Rendering
    void Render(std::vector<std::vector<Tile>>& tiles_to_render, std::vector<std::vector<Tile>>& background_tiles_to_render, 
                std::vector<ItemDrop>& item_drops, 
                SDL_Texture* background_texture, std::pair<int, int> mouse_pos,
                std::vector<Projectile> projectiles);

    // Getters and setters
    SDL_Rect GetPos();
    void SetPos(SDL_Rect pos);
    std::pair<double, double> GetVelocity();
    void SetVelocity(std::pair<double, double> velocity);
    std::pair<double, double> GetVelocityGoal();
    void SetVelocityGoal(std::pair<double, double> velocity_goal);
    ~Camera();
};

#endif // CAMERA_H_FILE