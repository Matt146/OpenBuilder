#ifndef GAMESTATE_H_FILE
#define GAMESTATE_H_FILE

#include <iostream>
#include <string>
#include <vector>
#include "projectile.h"

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

#include "utils.h"
#include "character.h"
#include "map.h"
#include "camera.h"
#include "perlin.h"
#include "gui.h"
#include "inventory.h"
#include "enemy.h"

class Gamestate {
private:
    // Gameplay stuff
    Map* m;
    Camera* c;
    Character* ch;

    // Texture stuff
    std::map<int, SDL_Texture*> item_texture_mapper;
    std::map<int, SDL_Texture*> enemy_texture_mapper;
    SDL_Texture* button_texture;
	SDL_Texture* inventory_slot_texture;
	SDL_Texture* character_texture;
	SDL_Texture* background_texture;
	SDL_Texture* projectile_texture;
    SDL_Texture* title_screen_background_texture;
    SDL_Texture* game_logo_texture;
    SDL_Texture* slider_arrow_texture;
    SDL_Texture* slider_thumb_texture;

    // Font/text stuff
    TTF_Font* font;
    SDL_Color text_color_default;

    // Scene management stuff
    int scene;      // the current scene number

    // SDL2 stuff
    SDL_Window* window;
    SDL_Renderer* renderer;

    // Framerate stuff
    double delta_t;

    // UI stuff
    std::vector<Button> title_screen_buttons;
    std::vector<Button> choose_world_screen_buttons;
    VerticalSlider* choose_world_slider;

    // Enemies
    std::vector<Enemy> enemies;
public:
    // Constructor
    Gamestate(SDL_Window* window, SDL_Renderer* renderer);

    // Initialization
    void LoadGameTextures();
    void LoadUITextures();
    void LoadMiscTextures();
    void LoadEnemyTextures();
    void LoadAnimations();
    void LoadFonts();
    void LoadNewMap();

    // Saving and loading stuff
    void SaveMap(std::string world_name);
    void LoadMap(std::string world_name);

    // Debug
    void PrintDebugLogs(double delta_t);

    // General scene management
    int GetCurrentScene();
    void SetCurrentScene(int scene);

    // Scene TITLE_SCENE:
    void LoadTitleScreenWidgets(); // only to be called once before the game loop. basically initializes all the UI elements
    void HandleTitleScreenInputs(SDL_Event& ev, bool& running); // to be called every frame of the game loop
    void HandleTitleScreenUpdatesAndRendering(double delta_t);  // to be called every frame of the game loop

    // Scene CHOOSE_WORLD_SCREEN:
    void LoadChooseWorldWidgets();
    void HandleChooseWorldScreenInputs(SDL_Event& ev, bool& running);
    void HandleChooseWorldUpdatesAndRendering(double delta_t);

    // Scene GAME_SCENE:
    void HandleGameplayInputs(SDL_Event& ev, bool& running);
    void HandleGameplayUpdatesAndRendering(double delta_t);

    // Cleanup
    ~Gamestate();

};

/*********************************************
 * UI Callback functions
*********************************************/
void PlayNowButtonCallback(void* any_thing);
void QuitNowButtonCallback(void* any_thing);
void WorldButtonCallback(void* any_thing);

#endif // GAMESTATE_H_FILE