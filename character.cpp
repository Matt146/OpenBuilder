#include "character.h"

Character::Character(SDL_Renderer* renderer, SDL_Texture* player_texture, SDL_Texture* inventory_slot_texture, std::map<int, SDL_Texture*> textures, TTF_Font* font) {
    //SDL_Rect player_world_pos = {CAMERA_STARTING_X + (WIDTH / 2) - TILE_WIDTH, CAMERA_STARTING_Y + (HEIGHT / 2) - TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT};
    this->player_world_pos = {CAMERA_STARTING_X + (WIDTH / 2) - TILE_WIDTH, CAMERA_STARTING_Y + (HEIGHT / 2) - TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT};

    this->renderer = renderer;
    this->player_texture = player_texture;
    this->health = CHARACTER_MAX_HEALTH;
    try {
        this->player_inventory = new Inventory(renderer, inventory_slot_texture, textures, font);
    } catch (std::bad_alloc& ba) {
        std::cout << "Bad alloc caught: " << __FILE__ << ":" << __LINE__ << " " << ba.what() << std::endl;
    }
    this->velocity_x = 0;
    this->velocity_y = 0;
    this->velocity_x_goal = 0;
    this->velocity_y_goal = 0;
    this->alive = true;

    // load the animations
    try {
        Animation* a = new Animation(this->renderer, LoadAnimationFrames(this->renderer, ANIMATION_CHARACTER_WALKING));
        this->walking_animation = a;
    } catch (std::bad_alloc& ba) {
        std::cout << "Bad alloc caught: " << __FILE__ << ":" << __LINE__ << " " << ba.what() << std::endl;
    }

    this->facing_right = true;
}

void Character::MoveLeft() {
    this->SetVelocityGoal(std::pair<double, double>(-CHARACTER_LR_DISTANCE, velocity_y));
    this->facing_right = false;
}

void Character::MoveRight() {
    this->SetVelocityGoal(std::pair<double, double>(CHARACTER_LR_DISTANCE, velocity_y));
    this->facing_right = true;
}

void Character::Jump() {
    /*
    velocity_x += dt*CHARACTER_DT_MULTIPLIER;
    velocity_y += dt*CHARACTER_DT_MULTIPLIER;
    SDL_Rect new_position = {player_world_pos.x + (velocity_x), player_world_pos.y + (velocity_y), player_world_pos.w, player_world_pos.h};
    this->player_world_pos = new_position;
    */
    if (this->collision_bottom == true) {
        this->SetVelocity(std::pair<double, double>(velocity_x, -CHARACTER_JUMP_HEIGHT));
        this->SetVelocityGoal(std::pair<double, double>(velocity_x, -CHARACTER_JUMP_HEIGHT));
    }
}

void Character::StopMoveLeft() {
    SetVelocityGoal(std::pair<double, double>(0, velocity_y));
    this->walking_animation->Reset();
}

void Character::StopMoveRight() {
    SetVelocityGoal(std::pair<double, double>(0, velocity_y));
    this->walking_animation->Reset();
}

void Character::StopJump() {
	SetVelocityGoal(std::pair<double, double>(velocity_x, 0));
}

void Character::Fall() {
    /* OLD FALL:
    SDL_Rect pre_pos = this->player_world_pos;
    SDL_Rect post_pos = {pre_pos.x, pre_pos.y + CHARACTER_FALL_DISTANCE, pre_pos.w, pre_pos.h};
    this->player_world_pos = post_pos;
    */
    if (this->collision_bottom == false) {
        if (this->velocity_y >= CHARACTER_FALL_TERMINAL_VELOCITY) {
           this->velocity_y = CHARACTER_FALL_TERMINAL_VELOCITY;
           this->velocity_y_goal = CHARACTER_FALL_TERMINAL_VELOCITY;
        } else {
            this->velocity_y += (CHARACTER_FALL_VELOCITY * 0.5);
            this->velocity_y_goal += (CHARACTER_FALL_VELOCITY * 0.5);
        }
    }
}

SDL_Rect Character::GetPos() {
    return this->player_world_pos;
}

std::pair<double, double> Character::GetVelocity() {
    return std::pair<double, double>(velocity_x, velocity_y);
}

void Character::SetVelocity(std::pair<double, double> velocity) {
    this->velocity_x = velocity.first;
    this->velocity_y = velocity.second;
}

std::pair<double, double> Character::GetVelocityGoal() {
    return std::pair<double, double>(velocity_x_goal, velocity_y_goal);
}

void Character::SetVelocityGoal(std::pair<double, double> velocity_goal) {
    this->velocity_x_goal = velocity_goal.first;
    this->velocity_y_goal = velocity_goal.second;
}

std::vector<Projectile> Character::GetProjectiles() {
    return this->projectiles.GetProjectiles();
}

void Character::Render() {
    // Draw the health bar background that's black
    // We will then draw a red bar over that in order to make
    // it look like there is a border around the actual bar
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_Rect healthbar_background_rect = {GUI_HOPBAR_SLOT_WIDTH * GUI_HOPBAR_SLOTS + GUI_HOPBAR_TO_HEALHBAR_PADDING, GUI_HOPBAR_PADDING, GUI_HEALTHBAR_MAX_WIDTH + 10, GUI_HEALTHBAR_HEIGHT + 10};
    SDL_RenderFillRect(renderer, &healthbar_background_rect);

    // Draw the green part of the health bar
    SDL_SetRenderDrawColor(renderer, 4, 232, 0, 255);
    SDL_Rect healthbar_rect = {GUI_HOPBAR_SLOT_WIDTH * GUI_HOPBAR_SLOTS + GUI_HOPBAR_TO_HEALHBAR_PADDING + 10 , GUI_HOPBAR_PADDING + 10, ((double)health / (double)CHARACTER_MAX_HEALTH) * (double)GUI_HEALTHBAR_MAX_WIDTH, (GUI_HEALTHBAR_HEIGHT) - 10};
    SDL_RenderFillRect(renderer, &healthbar_rect);

    // Draw the hopbar
    this->player_inventory->RenderHopbar();

    // Render the character (always in center of screen)
    SDL_Rect player_dstrect = {(WIDTH / 2) - TILE_WIDTH, (HEIGHT / 2) - TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT};
    if (velocity_x == 0 && velocity_y == 0) {
        SDL_RenderCopy(this->renderer, this->player_texture, NULL, &player_dstrect);
    } else if (velocity_x > 0) {
        this->walking_animation->RenderNextFrame(NULL, &player_dstrect, 0, NULL, SDL_FLIP_NONE);
    } else if (velocity_x < 0) {
        this->walking_animation->RenderNextFrame(NULL, &player_dstrect, 0, NULL, SDL_FLIP_HORIZONTAL);
    } else {
        // if all else fails
        if (this->facing_right == true) {
            SDL_RenderCopyEx(this->renderer, this->player_texture, NULL, &player_dstrect, 0.0, NULL, SDL_FLIP_HORIZONTAL);
        } else {
            SDL_RenderCopy(this->renderer, this->player_texture, NULL, &player_dstrect);
        }
    }
}

void Character::Update(double dt, SDL_Rect camera_pos, Map& m) {
    //printf("(%d, %d)\n", this->player_world_pos.x, player_world_pos.y);
    // Find any and all collisions with the map
    SDL_Point starting_pos = {player_world_pos.x - (TILE_WIDTH * 2), player_world_pos.y - (TILE_HEIGHT * 2)};
    SDL_Point ending_pos = {player_world_pos.x + (TILE_WIDTH * 2), player_world_pos.y + (TILE_HEIGHT * 2)};
    std::vector<std::pair<bool, Tile>> collisions = m.FindAllCollisionsInRange(player_world_pos, starting_pos, ending_pos);

    // handle collisions
    this->collision_bottom = false;
    this->collision_left = false;
    this->collision_right = false;
    this->collision_top = false;
    double character_midpoint_x = ((this->player_world_pos.x + this->player_world_pos.x + TILE_WIDTH) / 2);
    double character_midpoint_y = ((this->player_world_pos.y + this->player_world_pos.y + TILE_HEIGHT) / 2);
    SDL_Rect bottom_collision_rect = {};
    SDL_Rect left_collision_rect = {};
    SDL_Rect right_collision_rect = {};
    SDL_Rect top_collision_rect = {};
    for (size_t i = 0; i < collisions.size(); i++) {
        //std::cout << "COLLISION" << std::endl;

        double tile_midpoint_x = (collisions[i].second.x + collisions[i].second.x + TILE_WIDTH) / 2;
        double tile_midpoint_y = (collisions[i].second.y + collisions[i].second.y + TILE_HEIGHT) / 2;

        double wy = ((TILE_WIDTH + TILE_WIDTH) * (character_midpoint_y - tile_midpoint_y));
        double hx = ((TILE_HEIGHT + TILE_HEIGHT) * (character_midpoint_x - tile_midpoint_x));

        if (wy > hx) {
            if (wy > -hx) {
                /* top */
                this->collision_top = true;
                top_collision_rect = {collisions[i].second.x, collisions[i].second.y,
                                        TILE_WIDTH, TILE_HEIGHT};
                //std::cout << "top" << std::endl;
            } else {
                /* left */
                this->collision_left = true;
                left_collision_rect = {collisions[i].second.x, collisions[i].second.y,
                                        TILE_WIDTH, TILE_HEIGHT};
                //std::cout << "left" << std::endl;
            }
        } else {
            if (wy > -hx) {
                /* right */
                this->collision_right = true;
                right_collision_rect = {collisions[i].second.x, collisions[i].second.y,
                                        TILE_WIDTH, TILE_HEIGHT};
                //std::cout << "right" << std::endl;
            }
            else {
                /* bottom */
                this->collision_bottom = true;
                bottom_collision_rect = {collisions[i].second.x, collisions[i].second.y,
                                        TILE_WIDTH, TILE_HEIGHT};
                //std::cout << "bottom" << std::endl;
            }
        }
    }

    // handle projectiles
    std::vector<Projectile> all_projectiles = this->projectiles.GetProjectiles();
    for (size_t i = 0; i < all_projectiles.size(); i++) {
        int projectile_pos_x = all_projectiles[i].GetPos().x;
        int projectile_pos_y = all_projectiles[i].GetPos().y;
        // DEBUG: 
        printf("[+] Projectile pos: (%d, %d)\n", projectile_pos_x, projectile_pos_y);
        int projectile_top_left_x = floor((projectile_pos_x - (2 * TILE_WIDTH)));
        int projectile_top_left_y = floor((projectile_pos_y - (2 * TILE_HEIGHT)));
        int projectile_bottom_right_x = ceil((projectile_pos_x + (3 * TILE_WIDTH)));
        int projectile_bottom_right_y = ceil((projectile_pos_y + (3 * TILE_HEIGHT)));
        SDL_Point starting_point = {projectile_top_left_x, projectile_top_left_y};
        SDL_Point ending_point = {projectile_bottom_right_x, projectile_bottom_right_y};
        std::vector<std::pair<bool, Tile>> projectile_tile_collision = m.FindAllCollisionsInRange(
            {projectile_pos_x, projectile_pos_y, PROJECTILE_WIDTH, PROJECTILE_HEIGHT},
            starting_point, ending_point);
        if (projectile_tile_collision.size() > 0) {
            if (projectile_tile_collision[0].first == true) {
                all_projectiles[i].Explode();
                this->projectiles.ExplodeProjectile(i);
            }
        }
    }

    // ramp up velocity
    velocity_x = Approach(velocity_x, velocity_x_goal, dt*CHARACTER_DT_MULTIPLIER);
    velocity_y = Approach(velocity_y, velocity_y_goal, dt*CHARACTER_DT_MULTIPLIER);

    if (collision_right && velocity_x < 0) {
        velocity_x = 0;
        velocity_x_goal = 0;
    }
    if (collision_left && velocity_x > 0) {
        velocity_x = 0;
        velocity_x_goal = 0;
    }
    if (collision_top && velocity_y < 0) {
        velocity_y = 0;
        velocity_y_goal = 0;
    } if (collision_bottom && velocity_y > 0) {
        velocity_y = 0;
        velocity_y_goal = 0;
    }

    if (collision_bottom == true) {
        player_world_pos.y = bottom_collision_rect.y - TILE_HEIGHT + 1;
    }
    if (collision_left == true) {
        player_world_pos.x = left_collision_rect.x - TILE_WIDTH + 1;
    }
    if (collision_right == true) {
        player_world_pos.x = right_collision_rect.x + TILE_WIDTH - 1;
    }
    if (collision_top == true) {
        player_world_pos.y = top_collision_rect.y + TILE_HEIGHT - 1;
    }

    // update position
    player_world_pos.x += velocity_x;
    player_world_pos.y += velocity_y;

    // deal with itemdrops
    std::vector<ItemDrop>& item_drops = m.GetItemDrops();
    for (int x = 0; x < item_drops.size(); x++) {
        SDL_Rect item_drop_to_rect = {item_drops[x].pos.x, item_drops[x].pos.y, ITEMDROP_WIDTH, ITEMDROP_HEIGHT};
        SDL_Rect player_world_pos_copy = this->player_world_pos;
        if (SDL_HasIntersection(&item_drop_to_rect, &player_world_pos_copy)) {
            std::vector<ItemDrop>::iterator it = item_drops.begin();
            this->player_inventory->AddItem(item_drops[x].i);
            m.RemoveItemDrop(x);
        }
    }

    // handle projectiles
    this->projectiles.UpdateAll(dt, camera_pos);

    // handle block editing
    if (this->left_mouse_down) {
        int x, y;
        SDL_GetMouseState(&x, &y);
        SDL_Point mouse_pos = {x, y};
        //printf("Mouse Screen Position: (%d, %d)\n", x, y);
        SDL_Point mouse_world_pos = {camera_pos.x + mouse_pos.x, camera_pos.y + mouse_pos.y};
        //printf("Mouse World Position: (%d, %d)\n", mouse_world_pos.x, mouse_world_pos.y);
        if (this->player_inventory != NULL) {
            m.BreakBlock(mouse_world_pos, player_inventory->GetCurrentItem().tool_power, player_inventory->GetCurrentItem().tool_type);
        }
    }

    if (this->right_mouse_down) {
        int x, y;
        SDL_GetMouseState(&x, &y);
        SDL_Point mouse_pos = {x, y};
        SDL_Point mouse_world_pos = {camera_pos.x + mouse_pos.x, camera_pos.y + mouse_pos.y};
        int i_prev_count = this->player_inventory->GetCurrentItem().num;
        m.PlaceBlock(mouse_world_pos, this->player_inventory->GetCurrentItem());
        if (i_prev_count > this->player_inventory->GetCurrentItem().num) {
            this->player_inventory->AddToCurrentItem(1);
            this->player_inventory->RemoveCurrentItem(1);
        }
    }
}

void Character::SetPos(SDL_Rect pos) {
    this->player_world_pos = pos;
}

void Character::HandleCharacterInputs(SDL_Event ev) {
    this->left_mouse_down = LeftMouseDown(ev);
    this->right_mouse_down = RightMouseDown(ev);
    this->player_inventory->UpdateHopbar(ev);
    if (ev.type == SDL_MOUSEWHEEL) {
        if(ev.wheel.y > 0) {
             // scroll up
             this->player_inventory->GetCurHopbarSlot();
        }
        else if(ev.wheel.y < 0) {
             // scroll down
        } if(ev.wheel.x > 0) {
             // scroll right
        }
        else if(ev.wheel.x < 0) {
             //scroll left
        }
    }
}

void Character::AttackRange(SDL_Texture* projectile_texture, SDL_Point mouse_pos) {
    std::cout << "attacking range" << std::endl;
    int character_midpoint_x = ((double)(((WIDTH / 2) - TILE_WIDTH) + ((WIDTH / 2)))) / ((double)2);
    int character_midpoint_y = ((double)(((HEIGHT / 2) - TILE_HEIGHT) + ((HEIGHT / 2)))) / 2.0;
    int projectile_velocity_y = (double)(mouse_pos.y - character_midpoint_y) / (double)PROJECTILE_SLOPE_DIVISOR;
    int projectile_velocity_x = (double)(mouse_pos.x - character_midpoint_x) / (double)PROJECTILE_SLOPE_DIVISOR;
    SDL_Rect projectile_pos = {this->player_world_pos.x, this->player_world_pos.y, PROJECTILE_WIDTH, PROJECTILE_HEIGHT};
    Projectile p(projectile_pos, PROJECTILE_MAX_TILE_DISTANCE, PROJECTILE_MAX_FRAMES, projectile_texture, this->renderer, projectile_velocity_x, projectile_velocity_y);
    if (projectile_texture == NULL) {
        std::cout << "Fuck! It's NULL! YOU CAN'T SEE PROJECTILE" << std::endl;
    }
    this->projectiles.AddProjectile(p);
}

bool Character::IsAlive() {
    return alive;
}

void Character::Die() {
    alive = false;
}

bool Character::TakeDamageFromEntity(SDL_Rect entity_pos, double attack_range, int damage) {
    // calculate the distance between the attacking entity and 
    // the character
    double distance = Distance(player_world_pos.x, player_world_pos.y, 
                            entity_pos.x, entity_pos.y);
    if (distance <= attack_range) {
        health -= damage;
        if (health <= 0) {
            Die();
        }
        return true;
    } else {
        return true;
    }
}

std::tuple<bool, bool, bool, bool> Character::GetCollisionStates() {
    std::tuple<bool, bool, bool, bool> collision_states = std::make_tuple(this->collision_top,
                                                                        this->collision_bottom,
                                                                        this->collision_left,
                                                                        this->collision_right);
    return collision_states;
}

Character::~Character() {
    delete walking_animation;
    delete player_inventory;
}