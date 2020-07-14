#ifndef GUI_H_FILE
#define GUI_H_FILE

#include <SDL2/SDL.h>
#include <iostream>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <map>
#include "utils.h"

class InputHandler {
private:
public:
};

class Widget {
private:
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    SDL_Rect pos;
    std::string value;
    int state;
    void (*callback)(int);
    bool visible;
public:
    // Constructor
    Widget(SDL_Renderer* renderer, SDL_Rect pos, std::string value,
            int state, void (*callback)(int), bool visible);

    // setters
    void SetValue(std::string new_value);
    void SetPos(SDL_Rect pos);
    void SetCallback(void(*callback)(int));
    void SetTexture(SDL_Texture* texture);

    // update, render, and input handlers
    void Render();
    void Update(SDL_Event ev);
    std::string GetValue();
};

class Button : public Widget {
private:
public:
    Button();
};

class Label : public Widget {
private:
public:
};

class Testbox : public Widget {
private:
public:
};

// optional to make
class Slider : public Widget {
private:
public:
};

#endif // GUI_H_FILE