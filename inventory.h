#ifndef INVENTORY_H_FILE
#define INVENTORY_H_FILE

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <stdint.h>
#include <algorithm>
#include "animations.h"
#include "utils.h"
#include "gui.h"

typedef struct item {
    int type;
    int id;
    bool stackable;
    int max_num;
    int num;
    Animation* use_animation;
    Animation* other_animation;
    int tool_type;
    int tool_power;
} Item;

/**************************************************
 * BUG ALERT: THE HANDELING OF THE CALLBACKS USES
 * SOME SPOOKY BLACK MAGIC MEMORY MANAGEMENT SHIT
 * WITH VOID*.
 ***************************************************/

class Inventory {
private:
    SDL_Renderer* renderer;
    std::vector<Item> items;
    SDL_Texture* slot_texture;
    std::map<int, SDL_Texture*> textures;
    std::vector<Button> hopbar_buttons;
    int cur_hopbar_slot;    // 1 - 9
    std::vector<Label> hopbar_num_label;
    TTF_Font* font;
public:
    Inventory(SDL_Renderer* renderer, SDL_Texture* slot_texture, std::map<int, SDL_Texture*> textures, TTF_Font* font);
    void AddItem(Item& item);
    void RemoveItem(int item_id, int num);
    void RemoveCurrentItem(int num);    // remove the item in the current hopbar slot
    std::vector<Item> GetItems();
    Item& GetCurrentItem();
    void AddToCurrentItem(int num);
    void RenderHopbar();
    void UpdateHopbar(SDL_Event ev);
    void SetCurHopbarSlot(int slot);
    int GetCurHopbarSlot();
};

void InventoryButtonCallback(void* any_thing);

typedef struct InventoryHopbarCallbackParam {
    Inventory* obj;
    int hopbar_slot;
} hopbar_callback_param_t;

#endif // INVENTORY_H_FILE