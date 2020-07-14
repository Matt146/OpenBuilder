#include "inventory.h"

Inventory::Inventory(SDL_Renderer* renderer, SDL_Texture* slot_texture, std::map<int, SDL_Texture*> textures, TTF_Font* font) {
    this->renderer = renderer;
    this->slot_texture = slot_texture;
    this->cur_hopbar_slot = 0;
    for (size_t x = 0; x < GUI_HOPBAR_SLOTS; x++) {
        SDL_Rect pos = {GUI_HOPBAR_PADDING + (x * GUI_HOPBAR_SLOT_WIDTH) + GUI_HOPBAR_PADDING, GUI_HOPBAR_PADDING, GUI_HOPBAR_SLOT_WIDTH, GUI_HOPBAR_SLOT_HEIGHT};
        Button new_inventory_button(this->renderer, this->slot_texture,
                                    NULL, pos, "", 0, InventoryButtonCallback, true, {0, 0, 0, 255});
        this->hopbar_buttons.push_back(new_inventory_button);
    }
    this->textures = textures;
    this->font = font;
    for (size_t x = 0; x < INVENTORY_MAX_SLOTS; x++) {
        Item i = {0, INVENTORY_EMPTY_SLOT_ID, true, 1, 1, NULL, NULL, 0, 1};
        this->items.push_back(i);
    }
    for (size_t x = 0; x < GUI_HOPBAR_SLOTS; x++) {
        SDL_Rect label_rect = {(GUI_HOPBAR_PADDING + (x * GUI_HOPBAR_SLOT_WIDTH) + GUI_HOPBAR_PADDING + 20) + (GUI_HOPBAR_SLOT_WIDTH - 90), (GUI_HOPBAR_PADDING + 20) + (GUI_HOPBAR_SLOT_HEIGHT - 90), GUI_HOPBAR_NUM_LABEL_WIDTH, GUI_HOPBAR_NUM_LABEL_HEIGHT};
        Label l(this->renderer, NULL, this->font, label_rect, std::to_string(this->items[x].num), 0, NULL, true, {255, 255, 255, 255});
        this->hopbar_num_label.push_back(l);
    }
}

/*********BUG (WAS) HERE:******************/
void Inventory::AddItem(Item& item) {
    // find all indexes with the same item.id
    std::vector<size_t> indexes_w_same_item;
    for (size_t i = 0; i < this->items.size(); i++) {
        if (this->items[i].id == item.id) {
            indexes_w_same_item.push_back(i);
        }
    }

    // find the next empty slot
    int next_empty_slot = -1;
    for (size_t i = 0; i < this->items.size(); i++) {
        if (this->items[i].id == INVENTORY_EMPTY_SLOT_ID) {
            next_empty_slot = i;
            break;
        }
    }
    
    // go through all the indexes with the same item.id
    // and see if at least one of them is empty.
    // if one is empty and has sufficient capacity,
    // add the item and return. if it isn't, keep moving forward
    for (size_t x = 0; x < indexes_w_same_item.size(); x++) {
        if (item.id == this->items[indexes_w_same_item[x]].id) {
            if (this->items[indexes_w_same_item[x]].num + item.num <= this->items[indexes_w_same_item[x]].max_num) {
                this->items[indexes_w_same_item[x]].num += item.num;
                return;
            }
        }
    }

    // if there is an empty slot, make a new stack
    if (next_empty_slot >= 0) {
        this->items[next_empty_slot] = item;
    }

    /*DEBUG:
    for (size_t i = 0; i < INVENTORY_MAX_SLOTS; i++) {
        if (this->items[i].id != AIR) {
            printf("\nInventory slot: %d\n", i);
            printf("Item ID: %c\n", this->items[i].id);
            printf("Item Num: %d\n", this->items[i].num);
            printf("Item Max Num: %d\n", this->items[i].max_num);
            printf("Item Texture: %x\n", this->textures[this->items[i].id]);
        }
    }
    */


    return;
}

void Inventory::RemoveItem(int item_id, int num) {
    for (size_t i = 0; i < this->items.size(); i++) {
        if (this->items[i].id == item_id) {
            // if the item is stackable
            if (this->items[i].stackable == true) {
                // check to see if the number is greater than one
                if (this->items[i].num > num) {
                    this->items[i].num -= num;
                } else {
                    this->items[i] = {0, INVENTORY_EMPTY_SLOT_ID, true, 1, 1, NULL, NULL, 0, 1};
                }
            } else {
                // if the item is not stackable
                this->items[i] = {0, INVENTORY_EMPTY_SLOT_ID, true, 1, 1, NULL, NULL, 0, 1};
            }
        }
    }
}

void Inventory::RemoveCurrentItem(int num) {
    if (this->items[this->cur_hopbar_slot].stackable == true) {
        // check to see if the number is greater than one
        if (this->items[this->cur_hopbar_slot].num > num) {
            this->items[this->cur_hopbar_slot].num -= num;
        } else {
            this->items[this->cur_hopbar_slot] = {0, INVENTORY_EMPTY_SLOT_ID, true, 1, 1, NULL, NULL, 0, 1};
        }
    } else {
        // if the item is not stackable
        this->items[this->cur_hopbar_slot] = {0, INVENTORY_EMPTY_SLOT_ID, true, 1, 1, NULL, NULL, 0, 1};
    }
}

std::vector<Item> Inventory::GetItems() {
    return this->items;
}

Item& Inventory::GetCurrentItem() {
    if (this->cur_hopbar_slot > GUI_HOPBAR_SLOTS - 1) {
        this->cur_hopbar_slot = GUI_HOPBAR_SLOTS - 1;
        std::cout << "Clamped this->cur_hopbar_slot for GetCurrentItem(); (upper)" << std::endl;
    }
    if (this->cur_hopbar_slot < 0) {
        this->cur_hopbar_slot = 0;
        std::cout << "Clamped this->cur_hopbar_slot for GetCurrentItem(); (lower)" << std::endl;
    }
        return this->items[this->cur_hopbar_slot];
}

void Inventory::AddToCurrentItem(int num) {
    if (this->items[this->cur_hopbar_slot].num + num < this->items[this->cur_hopbar_slot].max_num) {
        this->items[this->cur_hopbar_slot].num += num;
    }
}

void Inventory::RenderHopbar() {
    for (size_t i = 0; i < this->hopbar_buttons.size(); i++) {
        if (i == cur_hopbar_slot) {
            SDL_SetRenderDrawColor(renderer, 255, 223, 13, 150);
            SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
            SDL_Rect highlight_pos = {GUI_HOPBAR_PADDING + (i * GUI_HOPBAR_SLOT_WIDTH) + GUI_HOPBAR_PADDING - 2, GUI_HOPBAR_PADDING -2 , GUI_HOPBAR_SLOT_WIDTH + 2, GUI_HOPBAR_SLOT_HEIGHT + 2};
            SDL_RenderFillRect(renderer, &highlight_pos);
        }
        hopbar_buttons[i].Render();

        if (i < this->items.size()) {
            // if there is something in this slot of the hopbar, draw its texture
            if (this->items[i].id != AIR) {
                //DEBUG: std::cout << this->items[i].id << std::endl;
                // render the icon of the item
                SDL_Rect item_rect = {GUI_HOPBAR_PADDING + (i * GUI_HOPBAR_SLOT_WIDTH) + GUI_HOPBAR_PADDING + 20, GUI_HOPBAR_PADDING + 20 , GUI_HOPBAR_SLOT_WIDTH -40, GUI_HOPBAR_SLOT_HEIGHT - 40};
                SDL_RenderCopy(renderer, this->textures[this->items[i].id], NULL, &item_rect);

                // now render the text that shows the number of that item on the bottom right corner of the hopbar slot
                SDL_Rect label_rect = {(GUI_HOPBAR_PADDING + (i * GUI_HOPBAR_SLOT_WIDTH) + GUI_HOPBAR_PADDING + 20) + (GUI_HOPBAR_SLOT_WIDTH - 80), (GUI_HOPBAR_PADDING + 20) + (GUI_HOPBAR_SLOT_HEIGHT - 80), GUI_HOPBAR_NUM_LABEL_WIDTH, GUI_HOPBAR_NUM_LABEL_HEIGHT};
                this->hopbar_num_label[i].SetValue(std::to_string(this->items[i].num));
                this->hopbar_num_label[i].Render();
            }
        }
    }
}

void Inventory::UpdateHopbar(SDL_Event ev) {
    for (size_t i = 0; i < this->hopbar_buttons.size(); i++) {
        hopbar_callback_param_t pass_me = {this, i};
        this->hopbar_buttons[i].Update(ev, (void*)&pass_me);
        if (i+1 == ev.key.keysym.sym-48) {
            this->cur_hopbar_slot = i;
        } else if (ev.key.keysym.sym-48 == 0) {
            this->cur_hopbar_slot = 9;
        }
    }
}

void Inventory::SetCurHopbarSlot(int slot) {
    this->cur_hopbar_slot = slot;
}

int Inventory::GetCurHopbarSlot() {
    return this->cur_hopbar_slot;
}

void InventoryButtonCallback(void* any_thing) {
    std::cout << "WARNING: BLACK MAGIC MEMORY MANAGEMENT SHIT HAPPENS HERE" << std::endl;
    hopbar_callback_param_t* catch_me = (struct InventoryHopbarCallbackParam*)any_thing;
    if (catch_me == NULL) {
        std::cout << "FUCK" << std::endl;
    }
    catch_me->obj->SetCurHopbarSlot(catch_me->hopbar_slot);
}