#ifndef ANIMATIONS_H_FILE
#define ANIMATIONS_H_FILE

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <SDL2/SDL.h>
#include <iostream>

class Animation {
private:
    SDL_Renderer* renderer;
    std::vector<SDL_Texture*> animation_frames;
    int current_frame;
public:
    Animation(SDL_Renderer* renderer, std::vector<SDL_Texture*> animation_frames);
    void RenderNextFrame(SDL_Rect* srcrect, SDL_Rect* dstrect, double angle, SDL_Point* center, SDL_RendererFlip flip);
    void Reset();
    ~Animation();
}; 

#endif // ANIMATIONS_H_FILE