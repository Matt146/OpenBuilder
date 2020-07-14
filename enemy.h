#ifndef ENEMY_H_FILE
#define ENEMY_H_FILE

#include <SDL2/SDL.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <chrono>
#include "enemy.h"
#include "animations.h"
#include "inventory.h"
#include "character.h"

typedef struct EnemyPositionValues {
    SDL_Rect pos;
    double velocity_x;
    double velocity_y;
    double velocity_x_goal;
    double velocity_y_goal;
} EnemyPosValues;

typedef struct EnemyStatValues {
    int health;
    int type;            // 0 = normal enemy; collision detection applies here
    int enemy_id;
    int attack_damage;
    double attack_range; // in terms of pixels
    int walking_speed;
    int jump_height;
    int fall_velocity;
    int fall_terminal_velocity;
    bool alive;
    int attack_cooldown_milliseconds;
    int time_of_last_attack_milliseconds;
} EnemyStatValues;

typedef struct EnemyRenderValues {
    SDL_Renderer* renderer;
    SDL_Texture* default_texture;
    Animation* walking_animation;
    Animation* attack_animation;
} EnemyRenderValues;

// @DEBUG @BUG = we can still take damage even though
// we might be considered dead (for both the enemy and the player)

class Enemy {
private:
    EnemyPositionValues pos_values;
    EnemyStatValues stat_values;
    EnemyRenderValues render_values;

    // collision detection stuff
    bool collision_top;
    bool collision_bottom;
    bool collision_left;
    bool collision_right;

    // which way the enemy is facing
    bool facing_right;
public:
    // Constructor
    explicit Enemy(EnemyPositionValues pos_values_, EnemyStatValues stat_values_,
        EnemyRenderValues render_values_)
        : pos_values(pos_values_), stat_values(stat_values_), render_values(render_values_) {};

    // Movement functions
    void WalkToPlayer(Character& ch);
    void WalkLeft();
    void WalkRight();
    void Jump();
    void Fall();    // only falls if type is not aerial

    // Combat functions
    void AttackPlayer(Character& ch);
    bool TakeDamageFromPlayer(Character& ch, double attack_range, int damage);
    void Die();

    // Updating/rendering functions
    void Update(Character& ch, Map& m, SDL_Rect camera_pos, double dt);
    void Render(SDL_Rect camera_pos);

    // Getters/setters
    SDL_Rect GetPos() const;
    bool IsAlive();

    // Destructor
    ~Enemy();
};

#endif // ENEMY_H_FILE