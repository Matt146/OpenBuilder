#include "gui.h"

/*******************************
 * Widget Functions
*******************************/
Widget::Widget(SDL_Renderer* renderer, SDL_Texture* texture, TTF_Font* font, SDL_Rect pos, std::string value,
            int state, void (*callback)(void*), bool visible, SDL_Color text_color) {
    this->renderer = renderer;
    this->pos = pos;
    this->value = value;
    this->state = state;
    this->callback = callback;
    this->visible = visible;
    this->texture = texture;
    this->font = font;
    this->text_color = text_color;
}

void Widget::SetValue(std::string new_value) {
    this->value = new_value;
}

void Widget::SetPos(SDL_Rect pos) {
    this->pos = pos;
}

void Widget::SetState(int state) {
    this->state = state;
}

void Widget::SetCallback(void(*callback)(void*)) {
    this->callback = callback;
}

void Widget::SetTexture(SDL_Texture* texture) {
    this->texture = texture;
}

void Widget::SetFont(TTF_Font* font) {
    this->font = font;
}

std::string Widget::GetValue() {
    return this->value;
}

/****************************
 * Button Functions
****************************/
void Button::Update(SDL_Event ev, void* any_value) {
    clicked = false;
    if (this->state == 0) {
        int mouse_pos_x;
        int mouse_pos_y;
        SDL_GetMouseState(&mouse_pos_x, &mouse_pos_y);
        SDL_Point mouse_pos = {mouse_pos_x, mouse_pos_y};
        if (SDL_PointInRect(&mouse_pos, &this->pos) == SDL_TRUE) {
            if (ev.type == SDL_MOUSEBUTTONUP) {
                // if there is an intersection, highlight the button
                // play the animation
                SDL_SetRenderDrawColor(renderer, 255, 223, 13, 80);
                SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
                SDL_RenderFillRect(renderer, &this->pos);

                // set clicked to true
                clicked = true;

                // do the callback
                this->callback(any_value);
            }
        }
    } 
}

void Button::SetPadding(int padding_x_, int padding_y_) {
    padding_x = padding_x_;
    padding_y = padding_y_;
}

void Button::SetClickedTexture(SDL_Texture* clicked_texture_) {
    clicked_texture = clicked_texture_;
}

void Button::Render() {
    if (this->visible == true) {
        // render the texture
        if (clicked == false) {
            SDL_RenderCopy(this->renderer, this->texture, NULL, &this->pos);
        } else if (clicked == true && clicked_texture != NULL) {
            SDL_RenderCopy(this->renderer, clicked_texture, NULL, &this->pos);
        } else {
            SDL_RenderCopy(this->renderer, this->texture, NULL, &this->pos);
        }

        // render the text in the "value"
        /* https://stackoverflow.com/questions/22886500/how-to-render-text-in-sdl2
        int text_width;
        int text_height;
        SDL_Surface *surface;
        SDL_Color textColor = {255, 255, 255, 0};

        surface = TTF_RenderText_Solid(font, text, textColor);
        *texture = SDL_CreateTextureFromSurface(renderer, surface);
        text_width = surface->w;
        text_height = surface->h;
        SDL_FreeSurface(surface);
        rect->x = x;
        rect->y = y;
        rect->w = text_width;
        rect->h = text_height;
        */
       if (this->font != NULL) {
            SDL_Surface* surface = TTF_RenderText_Solid(this->font, this->value.c_str(), this->text_color);
            SDL_Texture* font_texture = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_FreeSurface(surface);
            SDL_Rect font_pos = {pos.x + padding_x, 
                            pos.y + padding_y, 
                            (pos.x + pos.w - padding_x) - (pos.x + padding_x), 
                            (pos.y + pos.h - padding_y) - (pos.y + padding_y)};
            SDL_RenderCopy(renderer, font_texture, NULL, &font_pos);
            SDL_DestroyTexture(font_texture);
       }
    }
}

SDL_Rect* Button::GetPosReference() {
    return &this->pos;
}

/****************************
 * Label Functions
****************************/

void Label::Render() {
    if (this->font != NULL) {
        /*
        std::cout << "1" << std::endl;
        printf("[+] %x\n", this->font);
        printf("[+] %s\n", this->value.c_str());
        printf("[+] %d %d %d %d\n", this->text_color.r, this->text_color.g, this->text_color.b, this->text_color.a);
        */
        if (this->font != (TTF_Font*)0x1) {
            SDL_Surface* surface = TTF_RenderText_Solid(this->font, this->value.c_str(), this->text_color); // BUG HERE. WE ACCIDETNALLY SET THE FONT TO ONE SOMEWHERE
            SDL_Texture* font_texture = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_FreeSurface(surface);
            SDL_RenderCopy(renderer, font_texture, NULL, &this->pos);
            SDL_DestroyTexture(font_texture);
        }
    }
}

/****************************
 * Textbox Functions
****************************/

void Textbox::Render() {
    
}

/**************************
 * Vertical Slider Functions
**************************/

void VerticalSlider::Update(SDL_Event ev, void* any_value) {
    // calcualte slider_pos height and width based on number of 
    SDL_Rect new_slider_pos = {this->slider_pos.x, this->slider_pos.y, 
                            0, 0};
    int slider_pos_width = this->pos.w;
    int slider_pos_height = (int)((double)(this->pos.h) / (double)(this->things_to_update.size()));
    if (slider_pos_height < GUI_VERTICAL_SLIDER_MIN_HEIGHT) {
        slider_pos_height = GUI_VERTICAL_SLIDER_MIN_HEIGHT;
    }
    new_slider_pos.w = slider_pos_width;
    new_slider_pos.h = slider_pos_height;
    this->slider_pos = new_slider_pos;


    // do drag and drop calculations
    SDL_Point mouse_pos = {0, 0};
    SDL_GetMouseState(&mouse_pos.x, &mouse_pos.y);
    if (SDL_PointInRect(&mouse_pos, &this->slider_pos)) {
        if (RightMouseDown(ev)) {
            if (this->is_sliding == true) {
                this->starting_mouse_coords = {0, 0};
                SDL_GetMouseState(&this->starting_mouse_coords.x, &this->starting_mouse_coords.y);
            } else {
                this->is_sliding = true;
            }
        } else {
            double distance = Distance(mouse_pos.x, mouse_pos.y,
                                    this->starting_mouse_coords.x, this->starting_mouse_coords.y);
            this->slider_pos.y += distance;
            is_sliding = false;
            for (int j = 0; j < this->things_to_update.size(); j++) {
                things_to_update[j]->y += distance;
            }
        }
    }
}

void VerticalSlider::Render() {
    // render the top arrow
    SDL_RenderCopy(this->renderer, this->arrow_texture, NULL, &this->top_arrow_pos);

    // render the bottom arrow
    SDL_RenderCopyEx(this->renderer, this->arrow_texture, NULL, &this->bottom_arrow_pos,
    0, NULL, SDL_FLIP_VERTICAL);

    // render the entire slider background thing
    SDL_SetRenderDrawColor(this->renderer, 69, 69, 69, 100);
    SDL_RenderFillRect(this->renderer, &this->pos);

    // render the slider now
    SDL_RenderCopy(this->renderer, this->slider_icon, NULL, &this->slider_pos);
}

void VerticalSlider::SetPos(const SDL_Rect& new_pos) {
    this->pos = new_pos;
}

void VerticalSlider::SetState(const int& new_state) {
    this->state = new_state;
}

void VerticalSlider::SetVisible(const bool& new_visible) {
    this->visible = new_visible;
}
void VerticalSlider::AddThingToUpdate(SDL_Rect* new_thing_to_update) {
    this->things_to_update.push_back(new_thing_to_update);
}

void VerticalSlider::SetThingsToUpdate(std::vector<SDL_Rect*> new_things_to_update) {
    this->things_to_update.clear();
    this->things_to_update = new_things_to_update;
}

void VerticalSlider::SetValue(const double& new_value) {
    this->value = new_value;
}

void VerticalSlider::SetArrowTexture(SDL_Texture* arrow_texture) {
    this->arrow_texture = arrow_texture;
}

VerticalSlider::~VerticalSlider() {
    SDL_DestroyTexture(this->arrow_texture);
    SDL_DestroyTexture(this->slider_icon);
}