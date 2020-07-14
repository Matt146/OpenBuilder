#include "camera.h"

Camera::Camera(SDL_Renderer* renderer, std::map<int, SDL_Texture*> textures) {
    this->renderer = renderer;
    SDL_Rect starting_camera_pos = {CAMERA_STARTING_X, CAMERA_STARTING_Y, WIDTH, HEIGHT};
    this->world_pos_tl = starting_camera_pos;
    this->textures = textures;
}

// @TODO: RENDER ONLY THE TILES THAT ARE ON SCREEN
void Camera::Render(std::vector<std::vector<Tile>>& tiles_to_render,
                    std::vector<std::vector<Tile>>& background_tiles_to_render,
                    std::vector<ItemDrop>& item_drops,
                    SDL_Texture* background_texture, std::pair<int, int> mouse_pos,
                    std::vector<Projectile> projectiles) {
    // Render the background
    SDL_Rect srcrect = {0, 0, WIDTH, HEIGHT};
    SDL_Rect dstrect = {0, 0, WIDTH, HEIGHT};
    SDL_RenderCopy(this->renderer, background_texture, &srcrect, &dstrect);

   // Render the background tiles
    for (size_t i = 0; i < background_tiles_to_render.size(); i++) {
        for (size_t j = 0; j < background_tiles_to_render[i].size(); j++) {
            //printf("\nBackground tile: (%d, %d) --> %d\n", background_tiles_to_render[i][j].x, background_tiles_to_render[i][j].y, background_tiles_to_render[i][j].texture_id);
            //printf("Foreground tile: (%d, %d) --> %d\n", tiles_to_render[i][j].x, tiles_to_render[i][j].y, tiles_to_render[i][j].texture_id);
            if (background_tiles_to_render[i][j].texture_id != AIR) {
                if (tiles_to_render[i][j].texture_id == AIR) {
                    // Draw the actual tile
                    SDL_Rect dstrect = {background_tiles_to_render[i][j].x - this->world_pos_tl.x, background_tiles_to_render[i][j].y - this->world_pos_tl.y, TILE_WIDTH, TILE_HEIGHT};
                    SDL_RenderCopy(this->renderer, this->textures[background_tiles_to_render[i][j].texture_id], NULL, &dstrect);
                    
                    // Draw the correct breaking texture
                    if (background_tiles_to_render[i][j].brokenness > 0.0) {
                        // @TODO
                        int width = TILE_WIDTH * background_tiles_to_render[i][j].brokenness;
                        int height = TILE_HEIGHT * background_tiles_to_render[i][j].brokenness;
                        SDL_Rect broken_dstrect = {dstrect.x + ((dstrect.w - width) / 2),
                                                dstrect.y + ((dstrect.h - height) / 2),
                                                width,
                                                height,
                                                };
                        SDL_SetRenderDrawColor(renderer, 280, 280, 280, 165);
                        SDL_RenderFillRect(renderer, &broken_dstrect);
                    }
                }
            }       
        }
    }

    // Render the foreground tiles in the scene
    for (size_t i = 0; i < tiles_to_render.size(); i++) {
        for (size_t j = 0; j < tiles_to_render[i].size(); j++) {
            if (tiles_to_render[i][j].texture_id != AIR) {
                SDL_Rect dstrect = {tiles_to_render[i][j].x - this->world_pos_tl.x, tiles_to_render[i][j].y - this->world_pos_tl.y, TILE_WIDTH, TILE_HEIGHT};
                // Draw the actual tile
                SDL_RenderCopy(this->renderer, this->textures[tiles_to_render[i][j].texture_id], NULL, &dstrect);

                // Draw the correct breaking texture
                    if (tiles_to_render[i][j].brokenness > 0.0) {
                        // @TODO
                        int width = TILE_WIDTH * tiles_to_render[i][j].brokenness;
                        int height = TILE_HEIGHT * tiles_to_render[i][j].brokenness;
                        SDL_Rect broken_dstrect = {dstrect.x + ((dstrect.w - width) / 2),
                                                dstrect.y + ((dstrect.h - height) / 2),
                                                width,
                                                height,
                                                };
                        SDL_SetRenderDrawColor(renderer, 280, 280, 280, 165);
                        SDL_RenderFillRect(renderer, &broken_dstrect);
                    }
                // highlight block if mouse pos is on it
                // Making a rect from a tile
                SDL_Rect tile_to_rect = {tiles_to_render[i][j].x - this->world_pos_tl.x, tiles_to_render[i][j].y - this->world_pos_tl.y, TILE_WIDTH, TILE_HEIGHT};
                SDL_Point entity_pos = {mouse_pos.first, mouse_pos.second};
                // check if the texture ID is not an air tile
                if (tiles_to_render[i][j].texture_id != AIR) {
                    // Use SDL functions to check for a collision
                    if (SDL_PointInRect(&entity_pos, &tile_to_rect) == SDL_TRUE) {
                        // if there is an intersection, highlight the block
                        SDL_SetRenderDrawColor(renderer, 255, 223, 13, 80);
                        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
                        SDL_RenderFillRect(renderer, &tile_to_rect);
                    } 

                }
            }
        }
    }
    
    // Render item drops
    for (size_t x = 0; x < item_drops.size(); x++) {
        SDL_Rect item_drop_to_rect = {item_drops[x].pos.x, item_drops[x].pos.y, ITEMDROP_WIDTH, ITEMDROP_HEIGHT};
        SDL_Rect dstrect = {item_drop_to_rect.x - this->world_pos_tl.x, item_drop_to_rect.y - this->world_pos_tl.y, ITEMDROP_WIDTH, ITEMDROP_HEIGHT};
        int item_drop_id = item_drops[x].i.id;
        SDL_RenderCopy(this->renderer, this->textures[item_drop_id], NULL, &dstrect);
    }

    // draw a line from the character a hundred pixels out that follows the mouse
    SDL_SetRenderDrawColor(renderer, 12, 38, 235, 255);
    int character_midpoint_x = (((WIDTH / 2) - TILE_WIDTH) + ((WIDTH / 2))) / 2;
    int character_midpoint_y = (((HEIGHT / 2) - TILE_HEIGHT) + ((HEIGHT / 2))) / 2;
    SDL_RenderDrawLine(renderer, character_midpoint_x, character_midpoint_y,
                    mouse_pos.first, mouse_pos.second);

    // render projectiles
    for (size_t i = 0; i < projectiles.size(); i++) {
        projectiles[i].Render(this->world_pos_tl);
    }
}

SDL_Rect Camera::GetPos() {
    return this->world_pos_tl;
}

std::pair<double, double> Camera::GetVelocity() {
    return std::pair<double, double>(velocity_x, velocity_y);
}

void Camera::SetVelocity(std::pair<double, double> velocity) {
    velocity_x = velocity.first;
    velocity_y = velocity.second;
}

std::pair<double, double> Camera::GetVelocityGoal() {
    return std::pair<double, double>(velocity_x_goal, velocity_y_goal);
}

void Camera::SetVelocityGoal(std::pair<double, double> velocity_goal) {
    velocity_x_goal = velocity_goal.first;
    velocity_y_goal = velocity_goal.second;
}

void Camera::SetPos(SDL_Rect pos) {
    this->world_pos_tl = pos;
}

Camera::~Camera() {
    for (size_t i = 0; i < this->textures.size(); i++) {
        SDL_DestroyTexture(this->textures[i]);
    }
}
