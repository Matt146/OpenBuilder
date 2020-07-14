#ifndef CHARACTER_H_FILE
#define CHARACTER_H_FILE

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "utils.h"
#include <SDL2/SDL.h>
#include "projectile.h"
#include "map.h"
#include "inventory.h"

class Character {
private:
    // rendering and map stuff
    SDL_Rect player_world_pos;
    SDL_Texture* player_texture;

    // vectors
    double velocity_x;
    double velocity_y;
    double velocity_x_goal;
    double velocity_y_goal;

    // gameplay stuff
    int health;
    int energy;
    int strength;   // multiplier used for character attacks (applies to both melee and range)
    bool alive;

    // projectile stuff
    ProjectileSystem projectiles;

    // player rendering stuff
    SDL_Renderer* renderer;

    // collision stuff
    bool collision_right;
    bool collision_left;
    bool collision_top;
    bool collision_bottom;

    // mouse stuff
    bool left_mouse_down;
    bool right_mouse_down;

    // inventory stuff
    Inventory* player_inventory;

    // animation stuff
    Animation* walking_animation;
    bool facing_right;
public:
    //Constructor
    Character(SDL_Renderer* renderer, SDL_Texture* player_texture, SDL_Texture* inventory_slot_texture, std::map<int, SDL_Texture*> textures, TTF_Font* font);

    // Movement functions
    void MoveLeft();
    void MoveRight();
    void Jump();
    void Fall();
    void StopMoveLeft();
    void StopMoveRight();
    void StopJump();

    // Setters and getters
    SDL_Rect GetPos();
    void SetPos(SDL_Rect pos);
    std::pair<double, double> GetVelocity();
    void SetVelocity(std::pair<double, double> velocity);
    std::pair<double, double> GetVelocityGoal();
    void SetVelocityGoal(std::pair<double, double> velocity_goal);
    std::vector<Projectile> GetProjectiles();
    bool IsAlive();
    bool IsFacingLeft();

    // Gameplay functions
    void AddItemToPlayerInventory(Item i);

    // Rendering functions
    void Render();

    // Input handling
    void HandleCharacterInputs(SDL_Event ev);

    // Update/misc functions
    void Update(double dt, SDL_Rect camera_pos, Map& m);

    // Combat functions
    void AttackRange(SDL_Texture* projectile_texture, SDL_Point mouse_pos);
    void AttackMelee(SDL_Texture* texture);
    bool TakeDamageFromEntity(SDL_Rect entity_pos, double attack_range, int damage);  // true means that it was a successful attack, false means that it was unsuccessful
    void Die();

    // Get collision state
    std::tuple<bool, bool, bool, bool> GetCollisionStates();

    //Destructor
    ~Character();
};

#endif // CHARACTER_H_FILE