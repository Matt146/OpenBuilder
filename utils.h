#ifndef UTILS_H
#define UTILS_H

#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include <string>
#include <chrono>
#include <iostream>
#include <dirent.h>
#include <map>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <limits.h>
#include "animations.h"
#include "perlin.h"

// Texture definitions
#define CHARACTER_TEXTURE "character.bmp"
#define MAP_BACKGROUND_TEXTURE "map_background.bmp"

// Tile definitions
// BEFORE YOU CHANGE THIS, WAIT:
// THERE MIGHT BE AN ERROR HERE: void Projectile::Update(double dt)
// B/C THE FUNCTION ASSUMES THAT THE TILES ARE SQUARES
#define TILE_HEIGHT 64
#define TILE_WIDTH 64
#define ITEMDROP_HEIGHT 32
#define ITEMDROP_WIDTH 32

// item id enums
enum {
    AIR = 0,
    GRASS = 1,
    COBBLE = 2,
    IRON = 3,
    EPICORE = 4,
    DIRT_WALL = 5,
    LOG_WALL = 6,
    LEAF_WALL = 7,
};

// scene enums
enum {
    TITLE_SCREEN = 0,
    CHOOSE_WORLD_SCREEN = 1,
    GAMEPLAY_SCREEN = 2,
};

// title screen gui enums
enum {
    GUI_TITLESCREEN_PLAYNOW_BUTTON_INDEX = 0,
    GUI_TITLESCREEN_QUITNOW_BUTTON_INDEX = 1,
};

// enemy enums
enum {
    ZOMBIE = 1,
};

// enemy stat enums
enum {
    // zombie enums
    ZOMBIE_ATTACK_DAMAGE = 5,
    ZOMBIE_ATTACK_RANGE = (1 * TILE_WIDTH),
    ZOMBIE_FALL_TERMINAL_VELOCITY = 20,
    ZOMBIE_FALL_VELOCITY = 1,
    ZOMBIE_JUMP_HEIGHT = 10,
    ZOMBIE_HEALTH = 100,
    ZOMBIE_TYPE = 0,
    ZOMBIE_WALKING_SPEED = 5,
};

// Music definitions
#define DEFAULT_BACKGROUND_MUSIC "./Music/default-background.mp3"

// Perlin/Map definitions
#define ONED_PERLIN_STRIP_INDEX 22
#define MIN_HEIGHT_IN_TILES 1   // for the surface, ie: max_height_in_tiles. Then, we add MAP_UNDERGROUND_HEIGHT # of blocks to the randomly-generate terrain. Then, we add caves and other generations.
#define PERLIN_FREQUENCY 0.005
#define PERLIN_FREQUENCY_CAVE_MULTIPLIER 5
#define PERLIN_FREQUENCY_PATCH_MULTIPLIER 10
#define PERLIN_FREQUENCY_ORE_MULTIPLIER 5
#define PERLIN_PERSISTENCE 0.05
#define PERLIN_ROUGHNESS 2
#define PERLIN_OCTAVES 2
#define MAP_UNDERGROUND_HEIGHT 100
#define SURFACE_BLOCK_HEIGHT 15
#define TREE_CHANCE 10 // means that 1/TREE_CHANCE blocks will have a tree
#define TREE_NUM (floor((TREE_CHANCE / 2)))  // this is the number that rand() % TREE_CHANCE will spawn a tree
#define TREE_MAX_HEIGHT 10
#define TREE_MAX_WIDTH 3
#define TREE_MIN_HEIGHT 5

// Screen definitions
extern int WIDTH;   // default: 1080*2
extern int HEIGHT;   // default: 740*2
#define CAMERA_STARTING_X 0
#define CAMERA_STARTING_Y 0

// Character definitions
#define CHARACTER_LR_DISTANCE 10                // default: 10
#define CHARACTER_JUMP_HEIGHT 12                // default: 10
#define CHARACTER_FALL_VELOCITY 1.15              // default: 1
#define CHARACTER_FALL_TERMINAL_VELOCITY 20      // default: 3
#define CHARACTER_DT_MULTIPLIER 100             // default: 100
#define CHARACTER_FALL_DT_MULTIPLIER (CHARACTER_DT_MULTIPLIER / 2)
#define CHARACTER_MAX_HEALTH 100                //default: 100
//#define GRAVITY 10

// Math definitions
#define EPSILON std::numeric_limits<double>::epsilon()

// Debug constants
#define MAX_POS_ERRORS 25
#define MAX_VELOCITY_ERRORS 25
#define FRAMES_PER_CYCLE 120

// Projectile constants
#define PROJECTILE_MAX_TILE_DISTANCE 100 * TILE_WIDTH    // tiles
#define PROJECTILE_HEIGHT TILE_HEIGHT / 2
#define PROJECTILE_WIDTH TILE_WIDTH / 2
#define PROJECTILE_SLOPE_DIVISOR 20
#define PROJECTILE_MAX_FRAMES 800

// Animation constants
#define ANIMATION_DIRECTORY "Animations"
#define ANIMATION_CHARACTER_WALKING "character-walking"

// Framerate constants
#define MAX_FRAMERATE 60

// GUI constants
#define GUI_VERTICAL_SLIDER_MIN_HEIGHT 50
#define GUI_HOPBAR_PADDING 20
#define GUI_HOPBAR_SLOTS 10 // how many hopbar slots there are
#define GUI_HOPBAR_SLOT_WIDTH ((WIDTH / 2) / GUI_HOPBAR_SLOTS) // the width of each slot
#define GUI_HOPBAR_TO_HEALHBAR_PADDING 100
#define GUI_HOPBAR_SLOT_HEIGHT GUI_HOPBAR_SLOT_WIDTH    // the height of each slots
#define GUI_HEALTHBAR_MAX_WIDTH ((((WIDTH / 2)) - GUI_HOPBAR_PADDING - 100))
#define GUI_HEALTHBAR_HEIGHT (GUI_HOPBAR_SLOT_HEIGHT/2)
#define GUI_HOPBAR_NUM_LABEL_WIDTH (GUI_HOPBAR_SLOT_WIDTH / 4)
#define GUI_HOPBAR_NUM_LABEL_HEIGHT (GUI_HOPBAR_SLOT_HEIGHT / 4)

// GUI title screen constants
#define GUI_GAME_LOGO_WIDTH_DIVISOR 0.5
#define GUI_GAME_LOGO_HEIGHT_DIVISOR 0.5
#define GUI_PLAY_NOW_BUTTON_WIDTH_DIVISOR 1.2
#define GUI_PLAY_NOW_BUTTON_HEIGHT_DIVISOR 3
#define GUI_TITLE_SCREEN_LOGO_BUTTON_PADDING 250
#define GUI_TITLE_SCREEN_BUTTON_BUTTON_PADDING 50
#define GUI_QUIT_GAME_BUTTON_WIDTH_DIVISOR 1.2
#define GUI_QUIT_GAME_BUTTON_HEIGHT_DIVISOR 3

// GUI choose world screen constants
#define GUI_CHOOSE_WORLD_GAME_LOGO_WIDTH_DIVISOR 1
#define GUI_CHOOSE_WORLD_GAME_LOGO_HEIGHT_DIVISOR 1
#define GUI_CHOOSE_WORLD_PLANE_X_PUSH_IN 350
#define GUI_CHOOSE_WORLD_PLANE_Y_PUSH_IN 350
#define GUI_CHOOSE_WORLD_ARROW_WIDTH 50
#define GUI_CHOOSE_WORLD_ARROW_HEIGHT 50

// Item drop constant
#define ITEMDROP_GRAVITY 10

// Inventory constants
#define INVENTORY_EMPTY_SLOT_ID AIR
#define INVENTORY_MAX_SLOTS 40

// Misc constants
#define VERSION "0.0.1 - ALPHA"

// Map constants
#define MAP_FILE_PATH "./Maps/"
#define WORLD_FOLDER_PATH "./Worlds/"
#define WORLD_TILES_FNAME "tiles.map"
#define WORLD_BACKGROUND_TILES_FNAME "background_tiles.map"
#define WORLD_METADATA_FNAME "metadata.txt"
enum {
    WORLD_METADATA_VERSION_LINE = 0,
    WORLD_METADATA_WIDTH_LINE = 1,
    WORLD_METADATA_HEIGHT_LINE = 2,
};

SDL_Texture* LoadTexture(SDL_Renderer* renderer, std::string path);
std::vector<std::string> split_string(const std::string& str,
                                      const std::string& delimiter);
template<typename T>
size_t RemoveDuplicatesKeepOrder(std::vector<T>& vec);
std::string ReadFile(std::string fname);
float Distance(double x1, double y1, double x2, double y2);
double GetCurrentTime(); // Returns the current time in seconds
double Approach(double current, double goal, double dt); // dt is delta time
bool CompareDoubles(double A, double B);
int clamp(int n, int lower, int upper);
template<typename T>
std::vector<T> slice(std::vector<T> const &v, int m, int n)
{
    auto first = v.cbegin() + m;
    auto last = v.cbegin() + n + 1;

    std::vector<T> vec(first, last);
    return vec;
}
Animation LoadAnimations(SDL_Renderer* renderer, std::string animation_name);
std::vector<SDL_Texture*> LoadAnimationFrames(SDL_Renderer* renderer, std::string animation_name);
std::vector<std::string> LoadWorldNames();
float SampleLayeredNoise(float value, int seed);
bool LeftMouseDown(SDL_Event ev);   // return true if left mouse button is held down -- needs to be called every frame
bool RightMouseDown(SDL_Event ev);  // returns true if right mouse button is held down -- needs to be called every frame
void ReduceFraction (int &numerator, int &denominator);

#endif // UTILS_H