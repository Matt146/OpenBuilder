#include "map.h"


void DebugTiles(std::vector<std::vector<Tile>> tiles) {
	//printf("Works\n");
	for (size_t i = 0; i < tiles.size(); i++) {
        for (size_t j = 0; j < tiles[i].size(); j++) {
            printf("Tile: (%d, %d) %d\n", tiles[i][j].x, tiles[i][j].y, tiles[i][j].texture_id);
        }
    }
}

Map::Map(std::vector<std::vector<Tile>> foreground_tiles, std::vector<std::vector<Tile>> background_tiles_) {
    this->tiles_parsed = foreground_tiles;
    this->background_tiles = background_tiles_;
    BlockData air = {AIR, 0.000000000001, 2, 10000000, 0};
    this->block_data.insert(std::pair<int, BlockData>(AIR, air));
    BlockData grass = {GRASS, 0.02, 2, 0, 0, 0};
    this->block_data.insert(std::pair<int, BlockData>(GRASS, grass));
    BlockData cobble = {COBBLE, 0.02, 2, 1, 1, 0};
    this->block_data.insert(std::pair<int, BlockData>(COBBLE, cobble));
    BlockData iron = {IRON, 0.02, 2, 2, 1, 0};
    this->block_data.insert(std::pair<int, BlockData>(IRON, iron));
    BlockData epicore = {EPICORE, 0.02, 2, 3, 1, 0};
    this->block_data.insert(std::pair<int, BlockData>(EPICORE, epicore));
    BlockData dirt_wall = {DIRT_WALL, 0.02, 2, 0, 1, 1};
    this->block_data.insert(std::pair<int, BlockData>(DIRT_WALL, dirt_wall));
    BlockData log_wall = {LOG_WALL, 0.02, 2, 0, 0, 1};
    this->block_data.insert(std::pair<int, BlockData>(LOG_WALL, log_wall));
    BlockData leaf_wall = {LEAF_WALL, 0.02, 2, 0, 0, 1};
    this->block_data.insert(std::pair<int, BlockData>(LEAF_WALL, leaf_wall));
}

Map::Map(int max_width_in_tiles, int max_height_in_tiles, int max_hill_height) {
    // clamp max_hill_height
    if (max_hill_height > max_height_in_tiles) {
        max_hill_height = max_height_in_tiles;
    }

    // Initialize block data
    // BUG ALERT: WE SAY THAT AIR IS A FOREGROUND BLOCK
    // BUT WE TREAT IT AS BOTH
    BlockData air = {AIR, 0.000000000001, 2, 10000000, 0};
    this->block_data.insert(std::pair<int, BlockData>(AIR, air));
    BlockData grass = {GRASS, 0.02, 2, 0, 0, 0};
    this->block_data.insert(std::pair<int, BlockData>(GRASS, grass));
    BlockData cobble = {COBBLE, 0.02, 2, 1, 1, 0};
    this->block_data.insert(std::pair<int, BlockData>(COBBLE, cobble));
    BlockData iron = {IRON, 0.02, 2, 2, 1, 0};
    this->block_data.insert(std::pair<int, BlockData>(IRON, iron));
    BlockData epicore = {EPICORE, 0.02, 2, 3, 1, 0};
    this->block_data.insert(std::pair<int, BlockData>(EPICORE, epicore));
    BlockData dirt_wall = {DIRT_WALL, 0.02, 2, 0, 1, 1};
    this->block_data.insert(std::pair<int, BlockData>(DIRT_WALL, dirt_wall));
    BlockData log_wall = {LOG_WALL, 0.02, 2, 0, 0, 1};
    this->block_data.insert(std::pair<int, BlockData>(LOG_WALL, log_wall));
    BlockData leaf_wall = {LEAF_WALL, 0.02, 2, 0, 0, 1};
    this->block_data.insert(std::pair<int, BlockData>(LEAF_WALL, leaf_wall));

    // generate heightmap (DOCS: https://github.com/Auburns/FastNoise/wiki)
    std::vector<size_t> height_map;
    FastNoise myNoise; // Create a FastNoise object
    myNoise.SetNoiseType(FastNoise::Simplex); // Set the desired noise type
    int seed = rand() % INT_MAX - 1;
    myNoise.SetSeed(seed);
    myNoise.SetFrequency(PERLIN_FREQUENCY);
    myNoise.SetInterp(FastNoise::Linear);
    std::cout << "[%] Seed: " << seed << std::endl;
    for (int x = 0; x < max_width_in_tiles; x++) {
        int height_map_point = abs(myNoise.GetNoise(x, ONED_PERLIN_STRIP_INDEX)) * max_hill_height;
        if (height_map_point > max_hill_height) {
            height_map_point = max_hill_height;
        } else if (height_map_point < MIN_HEIGHT_IN_TILES) {
            height_map_point = MIN_HEIGHT_IN_TILES;
        }
        height_map.push_back(height_map_point);
    }

    // debug heightmap
    /*
    for (size_t z = 0; z < max_width_in_tiles; z++) {
        std::cout << height_map[z] << std::endl;
    }
    */

    // convert heightmap to map
    std::vector<std::vector<Tile>> tiles_processed;
    std::vector<std::vector<Tile>> tiles_background_processed;
    std::vector<Tile> tiles_column;
    std::vector<Tile> tiles_background_column;
    Tile t;
    Tile t_background;
    for (int i = 0; i < max_height_in_tiles; i++) {
        for (int j = 0; j < max_width_in_tiles; j++) {
            if (i < (max_height_in_tiles - height_map[j])) {
                t = {AIR, j * TILE_WIDTH, i * TILE_HEIGHT};
                t_background = {AIR, j * TILE_WIDTH, i * TILE_HEIGHT};
            } else {
                t = {GRASS, j * TILE_WIDTH, i * TILE_HEIGHT};
                t_background = {DIRT_WALL, j * TILE_WIDTH, i * TILE_HEIGHT};
            }
            tiles_column.push_back(t);
            tiles_background_column.push_back(t_background);
        }
        tiles_processed.push_back(tiles_column);
        tiles_column.clear();
        tiles_background_processed.push_back(tiles_background_column);
        tiles_background_column.clear();
    }
    this->width = max_width_in_tiles;

    // add biomes

    // add the underground
    for (int i = max_height_in_tiles; i < max_height_in_tiles + MAP_UNDERGROUND_HEIGHT; i++) {
        for (int j = 0; j < max_width_in_tiles; j++) {
            t = {GRASS, j * TILE_WIDTH, i * TILE_HEIGHT};
            t_background = {DIRT_WALL, j * TILE_WIDTH, i * TILE_HEIGHT};
            tiles_column.push_back(t);
            tiles_background_column.push_back(t_background);
        }
        tiles_processed.push_back(tiles_column);
        tiles_column.clear();
        tiles_background_processed.push_back(tiles_background_column);
        tiles_background_column.clear();
    }

    this->height = max_height_in_tiles + MAP_UNDERGROUND_HEIGHT;

    // add trees
    for (int i = 0; i < this->height; i++) {
        for (int j = 0; j < this->width; j++) {
            // if it is a surface block
            if (tiles_processed[abs(i-1)][j].texture_id == AIR && tiles_processed[i][j].texture_id != AIR) {
                int tree_chance = rand() % TREE_CHANCE;
                int tree_height = rand() % TREE_MAX_HEIGHT;
                if (tree_height < TREE_MIN_HEIGHT) {
                    tree_height = TREE_MIN_HEIGHT;
                }
                // if we get the right conditions for a tree
                if (tree_chance == TREE_NUM) {
                    // add the logs
                    //std::cout << "TREE TIME" << std::endl;
                    for (int x = 0; x < tree_height; x++) {
                        tiles_background_processed[abs(i-x)][j].texture_id = LOG_WALL;
                    }
                    // add the leaves
                    for (int x = 0; x < 3; x++) {
                        for (int y = 0; y < TREE_MAX_WIDTH-x; y++) {
                            if (i-tree_height-x < this->height && j-y < this->width && j+y < this->width) {
                                tiles_background_processed[abs(i-tree_height-x)][abs(j-y)].texture_id = LEAF_WALL;
                                tiles_background_processed[abs(i-tree_height-x)][abs(j+y)].texture_id = LEAF_WALL;
                            }
                        }
                    }
                }
            }
        }
    }

    // before we add caves, we need to find all surface blocks
    // so we don't accidentally turn those to air
    // also, in this loop we make patches of dirt and stone for the underground
    std::vector<std::vector<std::pair<bool, Tile>>> surface_tiles;
    std::vector<std::pair<bool, Tile>> surface_tiles_column;
    for (int i = 0; i < this->height; i++) {
        for (int j = 0; j < this->width; j++) {
            if (tiles_processed[abs(i-SURFACE_BLOCK_HEIGHT)][j].texture_id == AIR && tiles_processed[i][j].texture_id != AIR) {
                std::pair<bool, Tile> surface_tile_ind = std::pair<bool, Tile>(true, tiles_processed[i][j]);
                surface_tiles_column.push_back(surface_tile_ind);
            } else {
                std::pair<bool, Tile> surface_tile_ind = std::pair<bool, Tile>(false, tiles_processed[i][j]);
                surface_tiles_column.push_back(surface_tile_ind);
            }
        }
        surface_tiles.push_back(surface_tiles_column);
        surface_tiles_column.clear();
    }

    // add caves & patches
    FastNoise caveNoise; // Create a FastNoise object
    caveNoise.SetNoiseType(FastNoise::Simplex); // Set the desired noise type
    caveNoise.SetSeed(seed);
    caveNoise.SetFrequency(PERLIN_FREQUENCY * PERLIN_FREQUENCY_CAVE_MULTIPLIER);
    caveNoise.SetInterp(FastNoise::Linear);
    FastNoise patchNoise; // Create a FastNoise object
    patchNoise.SetNoiseType(FastNoise::Simplex); // Set the desired noise type
    patchNoise.SetSeed(seed - 10000);
    patchNoise.SetFrequency(PERLIN_FREQUENCY * PERLIN_FREQUENCY_PATCH_MULTIPLIER);
    patchNoise.SetInterp(FastNoise::Linear);
    for (int i = 0; i < this->height; i++) {
        for (int j = 0; j < this->width; j++) {
            double noise = abs(caveNoise.GetNoise(i, abs(j-1)));
            double patch_noise = abs(patchNoise.GetNoise(i, abs(j-1)));
            // add caves and patches
            if (surface_tiles[i][j].first == false) {
                if (patch_noise > 0.1 && patch_noise < 0.8 && tiles_processed[i][j].texture_id != AIR) {
                    tiles_processed[i][j].texture_id = COBBLE;
                }
                if (noise > 0.2 && noise < 0.5) {
                    tiles_processed[i][j].texture_id = AIR;
                }
            }
        }
    }

    // add water

    // add ores
    FastNoise oreNoise; // Create a FastNoise object
    oreNoise.SetNoiseType(FastNoise::Simplex); // Set the desired noise type
    oreNoise.SetSeed(seed - 100000);
    oreNoise.SetFrequency(PERLIN_FREQUENCY * PERLIN_FREQUENCY_ORE_MULTIPLIER);
    oreNoise.SetInterp(FastNoise::Linear);
    for (int i = 0; i < this->height; i++) {
        for (int j = 0; j < this->width; j++) {
            double ore_noise = abs(oreNoise.GetNoise(i, j));
            // add caves and patches
            if (surface_tiles[i][j].first == false && tiles_processed[i][j].texture_id != AIR) {
                if (ore_noise > 0.2 && ore_noise < 0.25) {
                    tiles_processed[i][j].texture_id = IRON;
                }
                if (ore_noise > 0.3 && ore_noise < 0.31) {
                    tiles_processed[i][j].texture_id = EPICORE;
                }
            }
        }
    }

    // add background blocks

    // set the tiles processed to the map tiles
    this->tiles_parsed = tiles_processed;
    this->background_tiles = tiles_background_processed;
    //DEBUG: DebugTiles(tiles_processed);
}

std::pair<bool, Tile> Map::FindCollision(SDL_Rect entity_pos) {
    std::pair<bool, Tile> return_val;
    for (size_t i = 0; i < this->tiles_parsed.size(); i++) {
        for (size_t j = 0; j < this->tiles_parsed[i].size(); j++) {
            // Making a rect from a tile
            SDL_Rect tile_to_rect = {this->tiles_parsed[i][j].x, this->tiles_parsed[i][j].y, TILE_WIDTH, TILE_HEIGHT};

            // check if the texture ID is not an air tile
            if (this->tiles_parsed[i][j].texture_id != AIR) {
                // Use SDL functions to check for a collision
                if (SDL_HasIntersection(&entity_pos, &tile_to_rect) == SDL_TRUE) {
                    return_val.first = true;
                    return_val.second = this->tiles_parsed[i][j];

                    // If there is an intersection, return true and the tile that is being intersected
                    return return_val;
                } 

            }  
        }
    }
    return_val.first = false;
    return_val.second = {0, 0, 0};
    return return_val;
}

std::vector<std::pair<bool, Tile>> Map::FindAllCollisions(SDL_Rect entity_pos) {
    std::vector<std::pair<bool, Tile>> return_val;
    for (size_t i = 0; i < this->tiles_parsed.size(); i++) {
        for (size_t j = 0; j < this->tiles_parsed[i].size(); j++) {
            // Making a rect from a tile
            SDL_Rect tile_to_rect = {this->tiles_parsed[i][j].x, this->tiles_parsed[i][j].y, TILE_WIDTH, TILE_HEIGHT};
            std::pair<bool, Tile> temp;
            // check if the texture ID is not an air tile
            if (this->tiles_parsed[i][j].texture_id != AIR) {
                // Use SDL functions to check for a collision
                if (SDL_HasIntersection(&entity_pos, &tile_to_rect) == SDL_TRUE) {
                    temp.first = true;
                    temp.second = this->tiles_parsed[i][j];
                    return_val.push_back(temp);
                } 
            }  
        }
    }
    return return_val;
}

// @TODO: ERROR HERE PROBABLY
void Map::EditBlock(SDL_Rect pos, int new_texture_id, bool drop_item, int block_type) {
    // edit a foreground block
    if (block_type == 0) {
        // Change the block
        int old_texture_id;
        for (size_t j = 0; j < this->tiles_parsed.size(); j++) {
            for (size_t i = 0; i < this->tiles_parsed[j].size(); i++) {
                if (this->tiles_parsed[j][i].x == pos.x && this->tiles_parsed[j][i].y == pos.y) {
                    old_texture_id = this->tiles_parsed[j][i].texture_id;
                    this->tiles_parsed[j][i].texture_id = new_texture_id;
                    this->tiles_parsed[j][i].brokenness = 0.0;
                }
            }
        }

        // Add an ItemDrop
        Item item = {old_texture_id, old_texture_id, true, 64, 1, NULL, NULL};
        SDL_Rect new_pos = {pos.x, pos.y, ITEMDROP_WIDTH, ITEMDROP_HEIGHT};
        ItemDrop item_drop = {item, new_pos};
        this->item_drops.push_back(item_drop);
    // edit a background block
    } else if (block_type == 1) {
        // Change the block
        int old_texture_id;
        for (size_t j = 0; j < this->background_tiles.size(); j++) {
            for (size_t i = 0; i < this->background_tiles[j].size(); i++) {
                if (this->background_tiles[j][i].x == pos.x && this->background_tiles[j][i].y == pos.y) {
                    old_texture_id = this->background_tiles[j][i].texture_id;
                    this->background_tiles[j][i].texture_id = new_texture_id;
                    this->background_tiles[j][i].brokenness = 0.0;
                }
            }
        }

        // Add an ItemDrop
        Item item = {old_texture_id, old_texture_id, true, 64, 1, NULL, NULL};
        SDL_Rect new_pos = {pos.x, pos.y, ITEMDROP_WIDTH, ITEMDROP_HEIGHT};
        ItemDrop item_drop = {item, new_pos};
        this->item_drops.push_back(item_drop);
    }
}

// @TODO = make tool_power for hand (ie: AIR BLOCK) 0
void Map::BreakBlock(SDL_Point mouse_world_pos, int tool_power, int tool_type) {
    // convert mouse_world_pos to the tile it is intersecting
    // Render the foreground tiles in the scene
    int tile_i = 0;
    int tile_j = 0;
    for (int i = 0; i < this->tiles_parsed.size(); i++) {
        for (int j = 0; j < this->tiles_parsed[i].size(); j++) {
            // check if the texture ID is not an air tile
            SDL_Rect tile_to_rect = {this->tiles_parsed[i][j].x, this->tiles_parsed[i][j].y, TILE_WIDTH, TILE_HEIGHT};
            SDL_Point entity_pos = {mouse_world_pos.x, mouse_world_pos.y};
            // Use SDL functions to check for a collision
            if (SDL_PointInRect(&entity_pos, &tile_to_rect) == SDL_TRUE) {
                tile_i = i;
                tile_j = j;
                break;
            }
        }
    }

    if (tile_i < 0) {
        tile_i = 0;
    }
    if (tile_j < 0) {
        tile_j = 0;
    }

    // check if the background is covered or not
    // if it is uncovered, break the background.
    // if it is covered, break the tile
    Tile* tile_to_edit = NULL;
    if (this->tiles_parsed[tile_i][tile_j].texture_id == AIR && this->background_tiles[tile_i][tile_j].texture_id != AIR) {
        //std::cout << "BREAKING BACKGROUND" << std::endl;
        tile_to_edit = &(this->background_tiles[tile_i][tile_j]);
    } else if (this->tiles_parsed[tile_i][tile_j].texture_id != AIR) {
        tile_to_edit = &(this->tiles_parsed[tile_i][tile_j]);
    }

    if (tile_to_edit != NULL) {
        // get the blockdata for the block we are supposed to edit
        BlockData tile_blockdata;
        if (tile_to_edit != NULL) {
            tile_blockdata = this->block_data[tile_to_edit->texture_id];
        }

        // go to that and add the appropriate brokenness
        double brokenness_to_add = tile_blockdata.hit_break;
        if (tool_power < tile_blockdata.min_tool_power) {
            brokenness_to_add = 0.0;
        } else if (tool_power > tile_blockdata.min_tool_power) {
            double brokenness_to_add = (tile_blockdata.hit_break * tile_blockdata.hit_break_scale_factor * (tool_power - tile_blockdata.min_tool_power + 1));
        }

        // add the brokenness
        // if the brokenness > 1, the block is considered broken and you must use
        // the EditBlock function and replace the block with air and leave a tile drop
        tile_to_edit->brokenness += brokenness_to_add;
        if (tile_to_edit->brokenness > 1) {
            this->EditBlock({tile_to_edit->x, tile_to_edit->y, TILE_WIDTH, TILE_HEIGHT},
                            AIR,
                            true, tile_blockdata.block_type);
        }
        // DEBUG:
        printf("Block Position: (%d, %d)\n", tile_to_edit->x, tile_to_edit->y);
        printf("Block ID: %d\n", tile_to_edit->texture_id);
        printf("Block Brokenness: %f\n", tile_to_edit->brokenness);
    } else {
        std::cout << "Segfault averted" << std::endl;
    }
}

void Map::PlaceBlock(SDL_Point mouse_world_pos, Item& block) {
    int tile_i = 0;
    int tile_j = 0;
    for (int i = 0; i < this->tiles_parsed.size(); i++) {
        for (int j = 0; j < this->tiles_parsed[i].size(); j++) {
            // check if the texture ID is not an air tile
            SDL_Rect tile_to_rect = {this->tiles_parsed[i][j].x, this->tiles_parsed[i][j].y, TILE_WIDTH, TILE_HEIGHT};
            SDL_Point entity_pos = {mouse_world_pos.x, mouse_world_pos.y};
            // Use SDL functions to check for a collision
            if (SDL_PointInRect(&entity_pos, &tile_to_rect) == SDL_TRUE) {
                tile_i = i;
                tile_j = j;
                break;
            }
        }
    }

    // check if the block is foreground or background
    int block_type = block_data[block.id].block_type;
    if (block.num >= 1) {
        if (block.id != INVENTORY_EMPTY_SLOT_ID) {
            if (block_type == 0) {
                // foreground
                if (this->tiles_parsed[tile_i][tile_j].texture_id == AIR) {
                    EditBlock({this->tiles_parsed[tile_i][tile_j].x, this->tiles_parsed[tile_i][tile_j].y, TILE_WIDTH, TILE_HEIGHT},
                                block.id, false, block_type);
                    block.num -= 1;
                }
            } else if (block_type == 1) {
                // background
                if (this->background_tiles[tile_i][tile_j].texture_id == AIR) {
                    EditBlock({this->background_tiles[tile_i][tile_j].x, this->background_tiles[tile_i][tile_j].y, TILE_WIDTH, TILE_HEIGHT},
                                block.id, false, block_type);
                    block.num -= 1;
                }
            }
        }
    }
}

std::vector<std::vector<Tile>> Map::GetTiles() {
    return this->tiles_parsed;
}

std::vector<std::vector<Tile>> Map::GetBackgroundTiles() {
    return this->background_tiles;
}

// @TODO - WARNING: UNTESTED:
std::vector<std::pair<bool, Tile>> Map::FindAllCollisionsInRange(SDL_Rect entity_pos, 
                                        SDL_Point starting_point, SDL_Point ending_point) {
    std::vector<std::vector<Tile>> tiles_to_check = GetTilesInRange(starting_point, ending_point);
    std::vector<std::pair<bool, Tile>> return_val;
    for (size_t i = 0; i < tiles_to_check.size(); i++) {
        for (size_t j = 0; j < tiles_to_check[i].size(); j++) {
            // Making a rect from a tile
            SDL_Rect tile_to_rect = {tiles_to_check[i][j].x, tiles_to_check[i][j].y, TILE_WIDTH, TILE_HEIGHT};
            std::pair<bool, Tile> temp;
            // check if the texture ID is not an air tile
            if (tiles_to_check[i][j].texture_id != AIR) {
                // Use SDL functions to check for a collision
                if (SDL_HasIntersection(&entity_pos, &tile_to_rect) == SDL_TRUE) {
                    temp.first = true;
                    temp.second = tiles_to_check[i][j];
                    return_val.push_back(temp);
                } 
            }  
        }
    }
    return return_val;
}

std::vector<std::vector<Tile>> Map::GetTilesInRange(SDL_Point starting_point, SDL_Point ending_point) {
    int starting_tile_x = floor(starting_point.x / TILE_WIDTH);
    int starting_tile_y = floor(starting_point.y / TILE_HEIGHT);
    int ending_tile_x = ceil(ending_point.x / TILE_WIDTH);
    int ending_tile_y = ceil(ending_point.y / TILE_HEIGHT);
    //starting_tile_x = clamp(starting_tile_x, 0, this->width);
    //starting_tile_y = clamp(starting_tile_y, 0, this->height);
    //ending_tile_x = clamp(ending_tile_x, 0, this->width);
    //ending_tile_y = clamp(ending_tile_y, 0, this->height);
    if (starting_tile_x < 0) {
        starting_tile_x = 0;
    }
    if (starting_tile_x > this->width) {
        starting_tile_x = this->width-1;
    }

    if (starting_tile_y < 0) {
        starting_tile_y = 0;
    }
    if (starting_tile_y > this->height) {
        starting_tile_y = this->height-1;
    }

    if (ending_tile_x < 0) {
        ending_tile_x = 0;
    }
    if (ending_tile_x > this->width) {
        ending_tile_x = this->width-1;
    }

    if (ending_tile_y < 0) {
        ending_tile_y = 0;
    }
    if (ending_tile_y > this->height) {
        ending_tile_y = this->height-1;
    }

    //printf("\n");
    //printf("(%d, %d)\n", this->width, this->height);
    //printf("(%d, %d); (%d, %d)\n", starting_tile_x, starting_tile_y, 
                                    //ending_tile_x, ending_tile_y);
    std::vector<std::vector<Tile>> return_val;
    //std::cout << std::to_string(x) << std::endl;
    std::vector<Tile> temp_val;
    for (int i = starting_tile_x; i < ending_tile_x; i++) {
        for (int j = starting_tile_y; j < ending_tile_y; j++) {
            temp_val.push_back(this->tiles_parsed[j][i]);
        }
        return_val.push_back(temp_val);
        temp_val.clear();
    }
    return return_val;
}

std::pair<int, int> Map::GetMapDimensions() {
    std::pair<int, int> map_dimensions(this->width, this->height);
    return map_dimensions;
}

std::vector<std::vector<Tile>> Map::GetBackgroundTilesInRange(SDL_Point starting_point, SDL_Point ending_point) {
    int starting_tile_x = floor(starting_point.x / TILE_WIDTH);
    int starting_tile_y = floor(starting_point.y / TILE_HEIGHT);
    int ending_tile_x = ceil(ending_point.x / TILE_WIDTH);
    int ending_tile_y = ceil(ending_point.y / TILE_HEIGHT);
    //starting_tile_x = clamp(starting_tile_x, 0, this->width);
    //starting_tile_y = clamp(starting_tile_y, 0, this->height);
    //ending_tile_x = clamp(ending_tile_x, 0, this->width);
    //ending_tile_y = clamp(ending_tile_y, 0, this->height);
    if (starting_tile_x < 0) {
        starting_tile_x = 0;
    }
    if (starting_tile_x > this->width) {
        starting_tile_x = this->width-1;
    }

    if (starting_tile_y < 0) {
        starting_tile_y = 0;
    }
    if (starting_tile_y > this->height) {
        starting_tile_y = this->height-1;
    }

    if (ending_tile_x < 0) {
        ending_tile_x = 0;
    }
    if (ending_tile_x > this->width) {
        ending_tile_x = this->width-1;
    }

    if (ending_tile_y < 0) {
        ending_tile_y = 0;
    }
    if (ending_tile_y > this->height) {
        ending_tile_y = this->height-1;
    }

    //printf("\n");
    //printf("(%d, %d)\n", this->width, this->height);
    //printf("(%d, %d); (%d, %d)\n", starting_tile_x, starting_tile_y, 
                                    //ending_tile_x, ending_tile_y);
    std::vector<std::vector<Tile>> return_val;
    //std::cout << std::to_string(x) << std::endl;
    std::vector<Tile> temp_val;
    for (int i = starting_tile_x; i < ending_tile_x; i++) {
        for (int j = starting_tile_y; j < ending_tile_y; j++) {
            temp_val.push_back(this->background_tiles[j][i]);
        }
        return_val.push_back(temp_val);
        temp_val.clear();
    }
    return return_val;
}

std::vector<ItemDrop>& Map::GetItemDrops() {
    return this->item_drops;
}

void Map::UpdateItemDrops() {
    for (size_t x = 0; x < item_drops.size(); x++) {
        SDL_Point starting_point = {item_drops[x].pos.x - 100, item_drops[x].pos.y - 100};
        SDL_Point ending_point = {item_drops[x].pos.x + 100, item_drops[x].pos.y + 100};
        std::vector<std::pair<bool, Tile>> collisions = FindAllCollisionsInRange(item_drops[x].pos, starting_point, ending_point);
        if (collisions.size() > 0) { 
            if (collisions[0].first == true) {
            }
        } else {
            item_drops[x].pos.y += ITEMDROP_GRAVITY;
        }
    }
}

void Map::RemoveItemDrop(int itr) {
    item_drops.erase(this->item_drops.begin() + itr);
}

void Map::TestItemDrops() {
    for (size_t i = 0; i < 500; i++) {
        Item item = {0, (int)GRASS, true, 999, 1, NULL, NULL};
        SDL_Rect item_drop_pos = {5 * TILE_WIDTH, 10 * TILE_HEIGHT, ITEMDROP_WIDTH, ITEMDROP_HEIGHT};
        ItemDrop ite = {item, item_drop_pos};
        this->item_drops.push_back(ite);
        Item item1 = {0, (int)DIRT_WALL, true, 999, 1, NULL, NULL};
        SDL_Rect item_drop_pos1 = {5 * TILE_WIDTH, 10 * TILE_HEIGHT, ITEMDROP_WIDTH, ITEMDROP_HEIGHT};
        ItemDrop ite1 = {item1, item_drop_pos1};
        this->item_drops.push_back(ite1);
    }
}

/********************************************************
 * World deserialization/serialization functions
********************************************************/
WorldData WorldSerializer::ParseWorldData() {
    ParseWorldMetadata();
    std::vector<std::vector<Tile>> tiles = ParseTilemap(WORLD_TILES_FNAME);
    std::vector<std::vector<Tile>> background_tiles = ParseTilemap(WORLD_BACKGROUND_TILES_FNAME);
    this->world_data.tiles = tiles;
    this->world_data.background_tiles = background_tiles;
    return this->world_data;
}

WorldMetadata WorldSerializer::ParseWorldMetadata() {
    std::string raw_metadata = ReadFile(world_data.path_to_world_dir + WORLD_METADATA_FNAME);
    std::vector<std::string> raw_metadata_split = split_string(raw_metadata, "\n");
    std::string version = "";
    int world_width = 0;
    int world_height = 0;
    for (int i = 0; i < raw_metadata_split.size(); i++) {
        if (i == WORLD_METADATA_VERSION_LINE) {
            version = raw_metadata_split[i];
        } else if (i == WORLD_METADATA_WIDTH_LINE) {
            world_width = atoi(raw_metadata_split[i].c_str());
        } else if (i == WORLD_METADATA_HEIGHT_LINE) {
            world_height = atoi(raw_metadata_split[i].c_str());
        }
    }

    WorldMetadata parsed_metadata = {version, world_width, world_height};
    world_data.metadata = parsed_metadata;
    return parsed_metadata;
}

std::vector<std::vector<Tile>> WorldSerializer::ParseTilemap(std::string tilemap_file) {
    // get a vector of the texture id's
    std::string raw_foreground_tiles_data = ReadFile(world_data.path_to_world_dir + tilemap_file);
    std::vector<std::string> split_texture_ids_raw = split_string(raw_foreground_tiles_data, "\n");
    std::vector<int> split_texture_ids;
    for (int i = 0; i < split_texture_ids_raw.size(); i++) {
        split_texture_ids.push_back(atoi(split_texture_ids_raw[i].c_str()));
    }

    // now just convert texture id's to tiles
    std::vector<std::vector<Tile>> tiles;
    std::vector<Tile> tiles_column;
    int cur_x = 0;
    int cur_y = 0;
    for (int i = 0; i < world_data.metadata.height; i++) {
        for (int j = 0; j < world_data.metadata.width; j++) {
            Tile t_;
            t_.texture_id = split_texture_ids[j + world_data.metadata.width*i];
            t_.x = cur_x;
            t_.y = cur_y;
            t_.brokenness = 0.0;
            tiles_column.push_back(t_);
            //printf("%d: (%d, %d) (%d, %d)--> %d\n", j + world_data.metadata.width*i, i, j, cur_x, cur_y, split_texture_ids[i*j]);
            cur_x += TILE_WIDTH;
        }
        tiles.push_back(tiles_column);
        tiles_column.clear();
        cur_y += TILE_HEIGHT;
        cur_x = 0;
    }

    // return tiles
    return tiles;
}

void WorldSerializer::SerializeWorldData(Map& m) {
    SerializeTileMaps(m);
    SerializeMetadata(m);
}

void WorldSerializer::SerializeTileMaps(Map& m) {
    std::vector<std::vector<Tile>> tiles = m.GetTiles();
    std::vector<std::vector<Tile>> background_tiles = m.GetBackgroundTiles();
    world_data.tiles = tiles;
    world_data.background_tiles = background_tiles;

    // first, we serialize the foreground tiles and write them to the file
    std::ofstream foreground_tilemap_file;
    foreground_tilemap_file.open(world_data.path_to_world_dir + WORLD_TILES_FNAME);
    std::cout << tiles.size() << std::endl;
    std::cout << tiles[0].size() << std::endl;
    for (size_t i = 0; i < tiles.size(); i++) {
        for (size_t j = 0; j < tiles[i].size(); j++) {
            foreground_tilemap_file << std::to_string(tiles[i][j].texture_id);
            foreground_tilemap_file << "\n";
        }
    }

    // cleanup
    foreground_tilemap_file.close();

    // next, we serialize the background tiles and write them to the file
    std::ofstream background_tilemap_file;
    background_tilemap_file.open(world_data.path_to_world_dir + WORLD_BACKGROUND_TILES_FNAME);
    for (size_t y = 0; y < background_tiles.size(); y++) {
        for (size_t x = 0; x < background_tiles[y].size(); x++) {
            background_tilemap_file << std::to_string(background_tiles[y][x].texture_id);
            background_tilemap_file << "\n";
        }
    }

    // cleanup
    background_tilemap_file.close();
}

void WorldSerializer::SerializeMetadata(Map& m) {
    // write to the file
    std::ofstream metadata_file;
    metadata_file.open(world_data.path_to_world_dir + WORLD_METADATA_FNAME);
    metadata_file << world_data.metadata.version << "\n";
    metadata_file << m.GetMapDimensions().first << "\n";
    metadata_file << m.GetMapDimensions().second << "\n";

    // cleanup
    metadata_file.close();
}

Map::~Map() {

}