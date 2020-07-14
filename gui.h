#ifndef GUI_H_FILE
#define GUI_H_FILE

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <map>
#include "utils.h"

class Widget {
protected:
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    TTF_Font* font;
    SDL_Rect pos;
    std::string value;
    int state;  // 0 = enabled; 1 = disabled;
    void (*callback)(void*);
    bool visible;
    SDL_Color text_color;
public:
    // Constructor
    Widget(SDL_Renderer* renderer, SDL_Texture* texture, TTF_Font* font, SDL_Rect pos, std::string value,
            int state, void (*callback)(void*), bool visible, SDL_Color text_color);

    // setters
    void SetValue(std::string new_value);
    void SetPos(SDL_Rect pos);
    void SetState(int state);
    void SetCallback(void(*callback)(void*));
    void SetTexture(SDL_Texture* texture);
    void SetFont(TTF_Font* font);

    // getter
    std::string GetValue();
};

class Button : public Widget {
private:
    int padding_x;
    int padding_y;
    SDL_Texture* clicked_texture;
    bool clicked;
public:
    Button(SDL_Renderer* renderer, SDL_Texture* texture, TTF_Font* font, SDL_Rect pos, std::string value,
            int state, void (*callback)(void*), bool visible, SDL_Color text_color) : Widget(renderer, texture, font, pos, value, state, callback, visible, text_color), padding_x(0), padding_y(0), clicked_texture(NULL), clicked(false) {};
    void Update(SDL_Event ev, void* any_value);
    void SetClickedTexture(SDL_Texture* clicked_texture_);   // you have to manually set it, otherwise, it will default to the other texture
    void SetPadding(int padding_x_, int padding_y_);                           // you have to manually set it, otherwise, it will default to 0
    void Render();
    SDL_Rect* GetPosReference();
};

class Label : public Widget {
private:
public:
    Label(SDL_Renderer* renderer, SDL_Texture* texture, TTF_Font* font, SDL_Rect pos, std::string value,
            int state, void (*callback)(void*), bool visible, SDL_Color text_color) : Widget(renderer, texture, font, pos, value, state, callback, visible, text_color) {};
    void Render();
};

class Textbox : public Widget {
private:
public:
    Textbox(SDL_Renderer* renderer, SDL_Texture* texture, TTF_Font* font, SDL_Rect pos, std::string value,
            int state, void (*callback)(void*), bool visible, SDL_Color text_color) : Widget(renderer, texture, font, pos, value, state, callback, visible, text_color) {};
    void Update(SDL_Event ev, void* any_value);
    void Render();
};

// optional to make
class VerticalSlider {
private:
    SDL_Renderer* renderer;
    SDL_Texture* arrow_texture;
    SDL_Texture* slider_icon;
    SDL_Rect pos;
    SDL_Rect slider_pos;
    SDL_Rect top_arrow_pos;
    SDL_Rect bottom_arrow_pos;
    int state;
    bool visible;
    double value;   // a value from 0 to 1, telling
    std::vector<SDL_Rect*> things_to_update;
    bool is_sliding = false;
    SDL_Point starting_mouse_coords;
public:
    // Important stuff
    VerticalSlider(SDL_Renderer* renderer_, SDL_Texture* arrow_texture_, SDL_Texture* slider_icon_, 
        SDL_Rect top_arrow_pos_, SDL_Rect bottom_arrow_pos_, SDL_Rect pos_, int state_, 
        bool visible_, std::vector<SDL_Rect*> things_to_update_)
        : renderer(renderer_), arrow_texture(arrow_texture_), slider_icon(slider_icon_), 
        top_arrow_pos(top_arrow_pos_), bottom_arrow_pos(bottom_arrow_pos_),
        pos(pos_), state(state_), visible(visible_), value(0.0),
        things_to_update(things_to_update_) {};
    void Update(SDL_Event ev, void* any_value);
    void Render();

    // Getters/Setters
    void SetPos(const SDL_Rect& new_pos);
    void SetState(const int& new_state);
    void SetVisible(const bool& new_visible);
    void AddThingToUpdate(SDL_Rect* new_thing_to_update);
    void SetThingsToUpdate(std::vector<SDL_Rect*> new_things_to_update);
    void SetValue(const double& new_value);
    void SetArrowTexture(SDL_Texture* arrow_texture);

    // Destructor for cleanup
    ~VerticalSlider();
};

#endif // GUI_H_FILE