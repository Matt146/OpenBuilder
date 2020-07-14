#ifndef MAP_H_FILE
#define MAP_H_FILE

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <map>
#include "utils.h"
#include <SDL2/SDL.h>
#include <algorithm>
#include "perlin.h"
#include <limits.h>
#include <memory>
#include "inventory.h"
#include <fstream>

typedef struct Tile {
    int texture_id;
    int x;
    int y;
    double brokenness; // starts at 0, goes up to 1 | THIS WAS THE MOFO ERROR THAT CAUSED THE RENDERING TO GO TO SHIT
} Tile;


// These are the characteristics for each blcok
typedef struct BlockData {
    int texture_id;
    double hit_break;   // how much you add to brokenness every single frame that you are holding your mouse button down
    double hit_break_scale_factor; // multiplier for hit_break when you use better tools than min_tool_power
    int min_tool_power; // the minimum amount of tool power you need to break a block
    int tool_type;      // the type of tool that you need to break a block (0=anything, 1=pickaxe, 2=axe)
    int block_type;      // 0 = foreground, 1 = background
} BlockData;

typedef struct ItemDrop {
    Item i;
    SDL_Rect pos;
} ItemDrop;

typedef struct WorldMetadata {
    std::string version;
    int width;
    int height;
} WorldMetadata;

typedef struct WorldData {
    std::string path_to_world_dir;    // the world directory with a slash at the end
    WorldMetadata metadata;
    std::vector<std::vector<Tile>> tiles;
    std::vector<std::vector<Tile>> background_tiles;
} WorldData;

class Map {
private:
    std::string unparsed_map_data;
    std::vector<std::vector<Tile>> tiles_parsed;        // foreground tiles
    std::vector<std::vector<Tile>> background_tiles;    // background tile
    std::map<int, BlockData> block_data;
    std::vector<ItemDrop> item_drops;
    int height; // in terms of tiles
    int width;  // in terms of tiles
public:
    Map(std::vector<std::vector<Tile>> foreground_tiles, std::vector<std::vector<Tile>> background_tiles_);
    Map(int max_width_in_tiles, int max_height_in_tiles, int max_hill_height);
    std::pair<bool, Tile> FindCollision(SDL_Rect entity_pos);
    std::vector<std::pair<bool, Tile>> FindAllCollisions(SDL_Rect entity_pos);
    std::vector<std::pair<bool, Tile>> FindAllCollisionsInRange(SDL_Rect entity_pos, SDL_Point starting_point, SDL_Point ending_point);
    //std::tuple<bool, Tile, std::string> FindCollisionEx(SDL_Rect entity_pos);
    void EditBlock(SDL_Rect pos, int new_texture_id, bool drop_item, int block_type);
    void BreakBlock(SDL_Point mouse_world_pos, int tool_power, int tool_type);
    void PlaceBlock(SDL_Point mouse_world_pos, Item& block);
    std::vector<std::vector<Tile>> GetTiles();
    std::vector<std::vector<Tile>> GetTilesInRange(SDL_Point starting_point, SDL_Point ending_point);
    std::vector<std::vector<Tile>> GetBackgroundTiles();
    std::vector<std::vector<Tile>> GetBackgroundTilesInRange(SDL_Point starting_point, SDL_Point ending_point);
    std::vector<ItemDrop>& GetItemDrops();
    std::pair<int, int> GetMapDimensions();
    void UpdateItemDrops();
    void RemoveItemDrop(int itr);   // the element of the item
    void TestItemDrops();
    ~Map();
};

class WorldSerializer {
private:
    WorldData world_data;
public:
    WorldSerializer(std::string path_to_world_dir)
        : world_data({path_to_world_dir, {VERSION, -1, -1}}) {};
    // serializatio functions
    
    // deserialization functions
    WorldData ParseWorldData();  // call this function to have everything done automatically for you
    // if you want lower-level control, call these functions in this order:
    WorldMetadata ParseWorldMetadata();
    std::vector<std::vector<Tile>> ParseTilemap(std::string tilemap_fname);  // this is used to parse a specified .map file

    // serialization functions
    void SerializeWorldData(Map& m); // call this function to have everything done automatically for you
    // if you want lower-level control, call these functions in this order:
    void SerializeTileMaps(Map& m); 
    void SerializeMetadata(Map& m); 
};


#endif // MAP_H_FILE