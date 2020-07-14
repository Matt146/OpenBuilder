#include "animations.h"

Animation::Animation(SDL_Renderer* renderer, std::vector<SDL_Texture*> animation_frames) {
    this->renderer = renderer;
    this->animation_frames = animation_frames;
    this->current_frame = 0;
}

void Animation::RenderNextFrame(SDL_Rect* srcrect, SDL_Rect* dstrect, double angle, 
                                SDL_Point* center, SDL_RendererFlip flip) {
    SDL_RenderCopyEx(this->renderer, this->animation_frames[this->current_frame],
                    srcrect, dstrect, angle, center, flip);
    if (this->current_frame < animation_frames.size()-1) {
        this->current_frame += 1;
    } else {
        Reset();
    }
}

void Animation::Reset() {
    this->current_frame = 0;
}

Animation::~Animation() {
    for (size_t i = 0; i < this->animation_frames.size(); i++) {
        SDL_DestroyTexture(this->animation_frames[i]);
    }
}