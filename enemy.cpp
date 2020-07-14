#include "enemy.h"

void Enemy::WalkLeft() {
    pos_values.velocity_x_goal = -stat_values.walking_speed;
    facing_right = false;
}

void Enemy::WalkRight() {
    pos_values.velocity_x_goal = stat_values.walking_speed;
    facing_right = true;
}

void Enemy::Jump() {
    if (collision_bottom == true) {
        pos_values.velocity_y = -stat_values.jump_height;
        pos_values.velocity_y_goal = -stat_values.jump_height;
    }
}

void Enemy::Fall() {
    if (this->collision_bottom == false) {
        if (pos_values.velocity_y >= stat_values.fall_terminal_velocity) {
           pos_values.velocity_y = stat_values.fall_terminal_velocity;
           pos_values.velocity_y_goal = stat_values.fall_terminal_velocity;
        } else {
            pos_values.velocity_y += (stat_values.fall_velocity * 0.5);
            pos_values.velocity_y_goal += (stat_values.fall_velocity * 0.5);
        }
    }
}


void Enemy::WalkToPlayer(Character& ch) {
    // get character position
    SDL_Rect player_pos = ch.GetPos();

    // calculate difference and stuff
    double x_diff = player_pos.x - pos_values.pos.x;
    double y_diff = player_pos.y - pos_values.pos.y;
    double distance_between_enemy_and_player = Distance(player_pos.x, player_pos.y, pos_values.pos.x, pos_values.pos.y);
    
    // change velocity for X
    if (x_diff <= 0 && distance_between_enemy_and_player >= stat_values.attack_range) {
        WalkLeft();
    } if (x_diff <= 0 && distance_between_enemy_and_player <= stat_values.attack_range) {
        pos_values.velocity_x = 0;
        pos_values.velocity_x_goal = 0;
    }
    if (x_diff >= 0 && distance_between_enemy_and_player >= stat_values.attack_range) {
        WalkRight();
    } if (x_diff >= 0 && distance_between_enemy_and_player <= stat_values.attack_range) {
        pos_values.velocity_x = 0;
        pos_values.velocity_x_goal = 0;
    }
}


void Enemy::AttackPlayer(Character& ch) {
    int cur_time_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>
        (std::chrono::high_resolution_clock::now().time_since_epoch()).count();
    if (cur_time_milliseconds - stat_values.time_of_last_attack_milliseconds >= stat_values.attack_cooldown_milliseconds) {
        //std::cout << cur_time_milliseconds - stat_values.time_of_last_attack_milliseconds << std::endl;
        //std::cout << stat_values.attack_cooldown_milliseconds << std::endl;
        ch.TakeDamageFromEntity(pos_values.pos, stat_values.attack_range, stat_values.attack_damage);
        stat_values.time_of_last_attack_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>
        (std::chrono::high_resolution_clock::now().time_since_epoch()).count();
        return;
    }
}

void Enemy::Die() {
    stat_values.alive = false;
}

bool Enemy::IsAlive() {
    return stat_values.alive;
}

SDL_Rect Enemy::GetPos() const {
    return pos_values.pos;
}

// @DEBUG @BUG might be here
bool Enemy::TakeDamageFromPlayer(Character& ch, double attack_range, int damage) {
    // calculate the distance between the attacking entity and 
    // the character
    SDL_Rect player_world_pos = ch.GetPos();
    double distance = Distance(player_world_pos.x, player_world_pos.y, 
                            pos_values.pos.x, pos_values.pos.y);
    
    // actually take damage
    if (distance <= attack_range) {
        stat_values.health -= damage;
        if (stat_values.health <= 0) {
            Die();
        }
        return true;
    } else {
        return true;
    }
}

void Enemy::Update(Character& ch, Map& m, SDL_Rect camera_pos, double dt) {
    // calculate necessary velocities to the player
    if (pos_values.pos.x - camera_pos.x >= 0 && pos_values.pos.x - camera_pos.x <= WIDTH) {
        if (pos_values.pos.y - camera_pos.y >= 0 && pos_values.pos.y - camera_pos.y <= HEIGHT) {
        this->WalkToPlayer(ch);
        } else {
            pos_values.velocity_x = 0;
            pos_values.velocity_x_goal = 0;
        }
    } else {
        pos_values.velocity_x = 0;
        pos_values.velocity_x_goal = 0;
    }
    if (stat_values.type == 0) {
        // handle collision detection
        SDL_Point starting_point = {pos_values.pos.x - (TILE_WIDTH * 2), pos_values.pos.y - (TILE_HEIGHT * 2)};
        SDL_Point ending_point = {pos_values.pos.x + (TILE_WIDTH * 2), pos_values.pos.y + (TILE_HEIGHT * 2)};
        std::vector<std::pair<bool, Tile>> collisions = m.FindAllCollisionsInRange(pos_values.pos, starting_point, ending_point);

        // handle collisions
        collision_bottom = false;
        collision_left = false;
        collision_right = false;
        collision_top = false;
        double character_midpoint_x = ((pos_values.pos.x + pos_values.pos.x + pos_values.pos.w) / 2);
        double character_midpoint_y = ((pos_values.pos.y + pos_values.pos.y + pos_values.pos.h) / 2);
        SDL_Rect bottom_collision_rect = {};
        for (size_t i = 0; i < collisions.size(); i++) {
            //std::cout << "COLLISION" << std::endl;

            double tile_midpoint_x = (collisions[i].second.x + collisions[i].second.x + TILE_WIDTH) / 2;
            double tile_midpoint_y = (collisions[i].second.y + collisions[i].second.y + TILE_HEIGHT) / 2;

            double wy = ((TILE_WIDTH + TILE_WIDTH) * (character_midpoint_y - tile_midpoint_y));
            double hx = ((TILE_HEIGHT + TILE_HEIGHT) * (character_midpoint_x - tile_midpoint_x));

            if (wy > hx) {
                if (wy > -hx) {
                    /* top */
                    collision_top = true;
                    //std::cout << "top" << std::endl;
                } else {
                    /* left */
                    collision_left = true;
                    //std::cout << "left" << std::endl;
                }
            } else {
                if (wy > -hx) {
                    /* right */
                    collision_right = true;
                    //std::cout << "right" << std::endl;
                }
                else {
                    /* bottom */
                    collision_bottom = true;
                    bottom_collision_rect = {collisions[i].second.x, collisions[i].second.y,
                                            TILE_WIDTH, TILE_HEIGHT};
                    //std::cout << "bottom" << std::endl;
                }
            }
        }

        // ramp up velocity
        pos_values.velocity_x = Approach(pos_values.velocity_x, pos_values.velocity_x_goal, dt*CHARACTER_DT_MULTIPLIER);
        pos_values.velocity_y = Approach(pos_values.velocity_y, pos_values.velocity_y_goal, dt*CHARACTER_DT_MULTIPLIER);

        if (collision_right && pos_values.velocity_x < 0) {
            pos_values.velocity_x = 0;
            pos_values.velocity_x_goal = 0;
            this->Jump();
        }
        if (collision_left && pos_values.velocity_x > 0) {
            pos_values.velocity_x = 0;
            pos_values.velocity_x_goal = 0;
            this->Jump();
        }
        if (collision_top && pos_values.velocity_y < 0) {
            pos_values.velocity_y = 0;
            pos_values.velocity_y_goal = 0;
        } if (collision_bottom && pos_values.velocity_y > 0) {
            pos_values.velocity_y = 0;
            pos_values.velocity_y_goal = 0;
        }

        if (collision_bottom == true) {
            pos_values.pos.y = bottom_collision_rect.y - TILE_HEIGHT + 1;
        }

        if (collision_bottom == false) {
            Fall();
        }
    }

    // update position
    pos_values.pos.x += pos_values.velocity_x;
    pos_values.pos.y += pos_values.velocity_y;

    this->AttackPlayer(ch);
    //this->TakeDamageFromPlayer(ch, 120, 10);
}

void Enemy::Render(SDL_Rect camera_pos) {
    if (pos_values.pos.x - camera_pos.x >= 0 && pos_values.pos.x - camera_pos.x <= WIDTH) {
        if (pos_values.pos.y - camera_pos.y >= 0 && pos_values.pos.y - camera_pos.y <= HEIGHT) {
            if (pos_values.velocity_x > 0) {
                SDL_Rect enemy_dstrect = {pos_values.pos.x - camera_pos.x, pos_values.pos.y - camera_pos.y, pos_values.pos.w, pos_values.pos.h};
                SDL_RenderCopy(render_values.renderer, render_values.default_texture, NULL, &enemy_dstrect);
                //printf("Zombie screen position: (%d, %d, %d, %d) --> 0x%x\n", pos_values.pos.x - camera_pos.x, pos_values.pos.y - camera_pos.y, pos_values.pos.w, pos_values.pos.h, render_values.default_texture);
            } else if (pos_values.velocity_x < 0) {
                SDL_Rect enemy_dstrect = {pos_values.pos.x - camera_pos.x, pos_values.pos.y - camera_pos.y, pos_values.pos.w, pos_values.pos.h};
                SDL_RenderCopyEx(render_values.renderer, render_values.default_texture, NULL, &enemy_dstrect, 0.0, NULL, SDL_FLIP_HORIZONTAL);
            } else if (facing_right == true) {
                SDL_Rect enemy_dstrect = {pos_values.pos.x - camera_pos.x, pos_values.pos.y - camera_pos.y, pos_values.pos.w, pos_values.pos.h};
                SDL_RenderCopy(render_values.renderer, render_values.default_texture, NULL, &enemy_dstrect);
            } else if (facing_right == false) {
                SDL_Rect enemy_dstrect = {pos_values.pos.x - camera_pos.x, pos_values.pos.y - camera_pos.y, pos_values.pos.w, pos_values.pos.h};
                SDL_RenderCopyEx(render_values.renderer, render_values.default_texture, NULL, &enemy_dstrect, 0.0, NULL, SDL_FLIP_HORIZONTAL);
            } else {
                // if all else fails
                SDL_Rect enemy_dstrect = {pos_values.pos.x - camera_pos.x, pos_values.pos.y - camera_pos.y, pos_values.pos.w, pos_values.pos.h};
                SDL_RenderCopy(render_values.renderer, render_values.default_texture, NULL, &enemy_dstrect);
            }
        }
    }
}

// @TODO do later
Enemy::~Enemy() {

}