#include "projectile.h"

Projectile::Projectile(SDL_Rect projectile_world_pos, int max_range, int max_frames, SDL_Texture* texture, SDL_Renderer* renderer, double velocity_x, double velocity_y) {
    this->projectile_world_pos = projectile_world_pos;
    this->initial_projectile_world_pos = projectile_world_pos;

    this->max_range = max_range;
    this->max_frames = max_frames;

    this->texture = texture;
    this->renderer = renderer;

    this->velocity_x = velocity_x;
    this->velocity_y = velocity_y;
    this->cur_frames = 0;
}

void Projectile::Explode() {
    std::cout << "Aaaahhh! I'm being exploded!" << std::endl;
    this->projectile_world_pos = projectile_world_pos;
    this->initial_projectile_world_pos = projectile_world_pos;

    this->texture = NULL;

    this->velocity_x = 0;
    this->velocity_y = 0;
    
    this->alive = false;
}

void Projectile::Update(double dt) {
    // check if > max_range tile distance
    double distance = Distance(this->projectile_world_pos.x, this->projectile_world_pos.y, this->initial_projectile_world_pos.x, this->initial_projectile_world_pos.y);
    double distance_tiles = distance / TILE_WIDTH;  // @DEBUG: THERE MIGHT BE AN ERROR HERE IF THE TILES AREN'T SQUARES
    if (abs(distance) > this->max_range) {
        Explode();
    } else {
        // update the position
        this->projectile_world_pos.x += this->velocity_x;
        this->projectile_world_pos.y += this->velocity_y; 
    }
    if (this->cur_frames >= this->max_frames) {
        Explode();
    }
    this->cur_frames++;
}

SDL_Rect Projectile::GetPos() {
    return this->projectile_world_pos;
}

void Projectile::Render(SDL_Rect camera_pos) {
    SDL_Rect render_here = {this->projectile_world_pos.x - camera_pos.x,
                            this->projectile_world_pos.y - camera_pos.y,
                            this->projectile_world_pos.w, this->projectile_world_pos.h};
    if (this->texture == NULL) {
        std::cout << "PROJECTILE TEXTURE NULL! NOT SHOWING ANYTHING" << std::endl;
    }
    SDL_RenderCopy(this->renderer, this->texture, NULL, &render_here);
}

bool Projectile::GetState() {
    return this->alive;
}

void ProjectileSystem::AddProjectile(Projectile projectile) {
    this->projectiles.push_back(projectile);
}

void ProjectileSystem::UpdateAll(double dt, SDL_Rect camera_pos) {
    for (size_t i = 0; i < this->projectiles.size(); i++) {
        // check to see if its alive
        if (this->projectiles[i].GetState() == true) {
            // update the projectile
            this->projectiles[i].Update(dt);

            // render all the projectiles
            this->projectiles[i].Render(camera_pos);
        } else {
            // if the projectile is exploded, remove it from the list
            this->projectiles.erase(this->projectiles.begin() + i);
        }

        //printf("Projectile %d: (%d, %d)\n", i, this->projectiles[i].GetPos().x, this->projectiles[i].GetPos().y);
    }
}

std::vector<Projectile> ProjectileSystem::GetProjectiles() {
    return this->projectiles;
}

void ProjectileSystem::ExplodeProjectile(size_t num) {
    std::cout << "ProjectileSystem exploding this guy: " << num << std::endl;
    this->projectiles[num].Explode();
}