#include "gamestate.h"

void PlayNowButtonCallback(void* any_thing) {
    std::cout << "WARNING: BLACK MAGIC MEMORY MANAGEMENT SHIT HAPPENS HERE" << std::endl;
    std::cout << "\tPlay now button on title screen ^^^^^^^^" << std::endl;
    Gamestate* catch_me = (Gamestate*)any_thing;
    if (catch_me == NULL) {
        std::cout << "FUCK" << std::endl;
    }
    catch_me->SetCurrentScene(GAMEPLAY_SCREEN);
}

void WorldButtonCallback(void* any_thing) {

}

Gamestate::Gamestate(SDL_Window* window, SDL_Renderer* renderer) {
	this->window = window;
    this->renderer = renderer;
	LoadGameTextures();
	LoadEnemyTextures();
	try {
		this->c = new Camera(renderer, this->item_texture_mapper);
	} catch (std::bad_alloc& ba) {
        std::cout << "Bad alloc caught: " << __FILE__ << ":" << __LINE__ << " " << ba.what() << std::endl;
    }
    LoadUITextures();
    LoadMiscTextures();
	LoadFonts();
    this->scene = 0;
	try {
    	this->m = new Map(2048, 64, 20);
	} catch (std::bad_alloc& ba) {
        std::cout << "Bad alloc caught: " << __FILE__ << ":" << __LINE__ << " " << ba.what() << std::endl;
    }
    try {
		this->ch = new Character(renderer, character_texture, inventory_slot_texture, item_texture_mapper, font);
	} catch (std::bad_alloc& ba) {
        std::cout << "Bad alloc caught: " << __FILE__ << ":" << __LINE__ << " " << ba.what() << std::endl;
    }
}

void Gamestate::LoadGameTextures() {
	item_texture_mapper.insert(std::pair<int, SDL_Texture*>(AIR, LoadTexture(renderer, "Textures/air.bmp")));
	item_texture_mapper.insert(std::pair<int, SDL_Texture*>(GRASS, LoadTexture(renderer, "Textures/grass.bmp")));
	item_texture_mapper.insert(std::pair<int, SDL_Texture*>(COBBLE, LoadTexture(renderer, "Textures/cobble.bmp")));
	item_texture_mapper.insert(std::pair<int, SDL_Texture*>(IRON, LoadTexture(renderer, "Textures/iron.bmp")));
	item_texture_mapper.insert(std::pair<int, SDL_Texture*>(EPICORE, LoadTexture(renderer, "Textures/epicore.bmp")));
	item_texture_mapper.insert(std::pair<int, SDL_Texture*>(DIRT_WALL, LoadTexture(renderer, "Textures/dirt_wall.bmp")));
	item_texture_mapper.insert(std::pair<int, SDL_Texture*>(LOG_WALL, LoadTexture(renderer, "Textures/log_wall.bmp")));
	item_texture_mapper.insert(std::pair<int, SDL_Texture*>(LEAF_WALL, LoadTexture(renderer, "Textures/leaf_wall.bmp")));
}

void Gamestate::LoadUITextures() {
    this->button_texture = LoadTexture(renderer, "UI-Textures/default-button.bmp");
	this->slider_arrow_texture = LoadTexture(renderer, "UI-Textures/slider-arrow-texture.bmp");
	this->inventory_slot_texture = LoadTexture(renderer, "UI-Textures/inventory-slot.bmp");
	this->title_screen_background_texture = LoadTexture(renderer, "UI-Textures/blue-background-gradient.bmp");
	this->game_logo_texture = LoadTexture(renderer, "UI-Textures/terraria-logo.bmp");
	this->slider_thumb_texture = LoadTexture(renderer, "UI-Textures/slider-thumb-texture.bmp");
}

void Gamestate::LoadMiscTextures() {
    this->background_texture = LoadTexture(renderer, "Textures/default-background.bmp");
	this->projectile_texture = LoadTexture(renderer, "Textures/projectile1.bmp");
    this->character_texture = LoadTexture(renderer, "Textures/character-standing.bmp");
}

void Gamestate::LoadEnemyTextures() {
	this->enemy_texture_mapper.insert(std::pair<int, SDL_Texture*>(ZOMBIE, LoadTexture(renderer, "Textures/zombie.bmp")));
}


void Gamestate::LoadFonts() {
    font = TTF_OpenFont("Fonts/OpenSans-Bold.ttf", 24);
	text_color_default = {255, 255, 255, 255};
}

void Gamestate::LoadNewMap() {
	// create a new map
	try {
		this->m = new Map(1024, 64, 20);
	} catch (std::bad_alloc& ba) {
        std::cout << "Bad alloc caught: " << __FILE__ << ":" << __LINE__ << " " << ba.what() << std::endl;
    }
	this->m->TestItemDrops();

	// spawn some enemies
	for (size_t i = 0; i < 1; i++) {
		EnemyPositionValues pos_values_;
		pos_values_.pos = {200, 100, TILE_WIDTH, TILE_HEIGHT};
		pos_values_.velocity_x = 0;
		pos_values_.velocity_y = 0;
		pos_values_.velocity_x_goal = 0;
		pos_values_.velocity_y_goal = 0;
		EnemyRenderValues render_values_;
		render_values_.attack_animation = NULL;
		render_values_.walking_animation = NULL;
		render_values_.renderer = renderer;
		render_values_.default_texture = enemy_texture_mapper[ZOMBIE];
		EnemyStatValues stat_values_;
		stat_values_.alive = true;
		stat_values_.attack_damage = ZOMBIE_ATTACK_DAMAGE;
		stat_values_.attack_range = ZOMBIE_ATTACK_RANGE;
		stat_values_.enemy_id = ZOMBIE;
		stat_values_.fall_terminal_velocity = ZOMBIE_FALL_TERMINAL_VELOCITY;
		stat_values_.fall_velocity = ZOMBIE_FALL_VELOCITY;
		stat_values_.health = ZOMBIE_HEALTH;
		stat_values_.jump_height = ZOMBIE_JUMP_HEIGHT;
		stat_values_.type = ZOMBIE_TYPE;
		stat_values_.walking_speed = ZOMBIE_WALKING_SPEED;
		stat_values_.attack_cooldown_milliseconds = 1000;
		stat_values_.time_of_last_attack_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>
        (std::chrono::high_resolution_clock::now().time_since_epoch()).count();
		Enemy enemy(pos_values_, stat_values_, render_values_);
		enemies.push_back(enemy);
	}
}

void Gamestate::SaveMap(std::string world_name) {
	WorldSerializer ws(WORLD_FOLDER_PATH + world_name + "_");
	ws.SerializeWorldData(*this->m);
}

void Gamestate::LoadMap(std::string world_name) {
	WorldSerializer ws(WORLD_FOLDER_PATH + world_name + "_");
	WorldData parsed_world_data = ws.ParseWorldData();
	delete this->m;	// @TODO @DEBUG @SEGFAUTL PROBABLY HERE
	try {
		this->m = new Map(parsed_world_data.tiles, parsed_world_data.background_tiles);
	} catch (std::bad_alloc& ba) {
        std::cout << "Bad alloc caught: " << __FILE__ << ":" << __LINE__ << " " << ba.what() << std::endl;
    }
}

void Gamestate::PrintDebugLogs(double delta_t) {
	/*
	printf("\n");
	printf("[+] Character Velocity: (%f, %f)\n", ch.GetVelocity().first, ch.GetVelocity().second);
	printf("[+] Character Velocity Goal: (%f, %f)\n", ch.GetVelocityGoal().first, ch.GetVelocityGoal().second);
	printf("[+] Camera Velocity: (%f, %f)\n", c.GetVelocity().first, c.GetVelocity().second);
	printf("[+] Camera Velocity Goal: (%f, %f)\n", c.GetVelocity().first, c.GetVelocity().second);
	printf("[*] Character position: (%d, %d)\n", ch.GetPos().x, ch.GetPos().y);
	printf("[*] Camera position: (%d, %d)\n", c.GetPos().x, c.GetPos().y);
	printf("[*] Adjusted Character Position: (%d, %d)\n", c.GetPos().x + (WIDTH / 2) - TILE_WIDTH, c.GetPos().y + (HEIGHT / 2) - TILE_HEIGHT);
	printf("[@] Total velocity errors: %d\n", velocity_errors);
	printf("[@] Total position errors: %d\n", pos_errors);
	printf("[&] Delta T: %f\n", delta_t);
	printf("[&] FPS: %f\n", 1/delta_t);
	*/
	//printf("[*] Character position: (%d, %d)\n", ch->GetPos().x, ch->GetPos().y);
}

int Gamestate::GetCurrentScene() {
    return this->scene;
}

void Gamestate::SetCurrentScene(int scene) {
    this->scene = scene;
}


/***********************************
 * TITLE_SCREEN functions
***********************************/
void Gamestate::LoadTitleScreenWidgets() {
	// load the play now button
	SDL_Color play_button_color_text = {255, 255, 255, 255};
	Button play_now_button(renderer, button_texture, font, {0, 0, 0, 0}, std::string("Play now!"), 0, PlayNowButtonCallback, true, play_button_color_text);
	title_screen_buttons.push_back(play_now_button);
}

void Gamestate::HandleTitleScreenInputs(SDL_Event& ev, bool& running) {
	while (SDL_PollEvent(&ev)) {
		switch (ev.type) {
			case SDL_QUIT:
				running = false;
				break;
		}
	}
	for (size_t i = 0; i < this->title_screen_buttons.size(); i++) {
		title_screen_buttons[i].Update(ev, this);
	}
}

void Gamestate::HandleTitleScreenUpdatesAndRendering(double delta_t) {
	// clear the screen first
	SDL_RenderClear(renderer);

	// render the background texture
	SDL_Rect title_screen_background_texture_rect = {0, 0, WIDTH, HEIGHT};
	SDL_RenderCopy(renderer, title_screen_background_texture, NULL, &title_screen_background_texture_rect);

	// render the logo in the top middle
	int w;
	int h;
	SDL_QueryTexture(game_logo_texture, NULL, NULL, &w, &h);
	int game_logo_width = w / GUI_GAME_LOGO_WIDTH_DIVISOR;
	int game_logo_height = h / GUI_GAME_LOGO_HEIGHT_DIVISOR;
	int game_logo_x = 0 + ((WIDTH - game_logo_width) / 2);
	int game_logo_y = 45;
	// HOW TO CENTER A RECTANGLE IN ANOTHER RECTANGLE
	//x2 = x1 + ((w1 - w2) / 2);
	//y2 = y1 + ((h1 - h2) / 2);
	//printf("\n(%d, %d)\n", game_logo_x, game_logo_y);
	//printf("(%d, %d)\n", game_logo_width, game_logo_height);
	SDL_Rect game_logo_rect = {game_logo_x, game_logo_y, game_logo_width, game_logo_height};
	SDL_RenderCopy(renderer, game_logo_texture, NULL, &game_logo_rect);

	// render play now button
	SDL_QueryTexture(button_texture, NULL, NULL, &w, &h);
	int play_button_width = w / GUI_PLAY_NOW_BUTTON_WIDTH_DIVISOR;
	int play_button_height = h / GUI_PLAY_NOW_BUTTON_HEIGHT_DIVISOR;
	int play_button_x = 0 + ((WIDTH - play_button_width) / 2);
	int play_button_y = game_logo_height + GUI_TITLE_SCREEN_LOGO_BUTTON_PADDING;
	SDL_Rect play_button_rect = {play_button_x, play_button_y, play_button_width, play_button_height};
	this->title_screen_buttons[GUI_TITLESCREEN_PLAYNOW_BUTTON_INDEX].SetPos(play_button_rect);
	this->title_screen_buttons[GUI_TITLESCREEN_PLAYNOW_BUTTON_INDEX].Render();

	// actually render the stuff
	SDL_RenderPresent(renderer);
}

/************************************
 * CHOOSE_WORLD_SCREEN functions
*************************************/
void Gamestate::LoadChooseWorldWidgets() {
	// this is the plane we make in HandleChooseWorldUpdatesAndRendering(double delta_t)
	SDL_Rect plane = {GUI_CHOOSE_WORLD_PLANE_X_PUSH_IN, GUI_CHOOSE_WORLD_PLANE_Y_PUSH_IN, 
					(WIDTH - GUI_CHOOSE_WORLD_PLANE_X_PUSH_IN) -  GUI_CHOOSE_WORLD_PLANE_X_PUSH_IN, 
					(HEIGHT - GUI_CHOOSE_WORLD_PLANE_Y_PUSH_IN) - GUI_CHOOSE_WORLD_PLANE_Y_PUSH_IN};

	// get a list of all the worlds
	std::vector<std::string> world_names = LoadWorldNames();

	// the font color
	SDL_Color font_color = {0, 0, 0, 255};

	// make the buttons for the for the world
	std::vector<std::string>::iterator it;
	int cur_y = GUI_CHOOSE_WORLD_PLANE_Y_PUSH_IN;
	int cur_num = 0;
	for (it = world_names.begin(); it != world_names.end(); ++it) {
		SDL_Rect button_rect = {
			plane.x,
			cur_y,
			plane.w,
			(plane.h / 4)
		};
		if (cur_num <= 3) {
			Button b = Button(renderer, button_texture,
							font, button_rect, *it, 0, WorldButtonCallback, true,
							font_color);
			b.SetPadding(300, 0);
			choose_world_screen_buttons.push_back(b);
		} else {
			Button b = Button(renderer, button_texture,
							font, button_rect, *it, 1, WorldButtonCallback, false,
							font_color);
			b.SetPadding(300, 0);
			choose_world_screen_buttons.push_back(b);
		}
		cur_y += ((int)((double)(plane.h) / (double)(4)));
		cur_num += 1;
	}

	SDL_Rect top_arrow_pos = {plane.x + plane.w + 1, 
							plane.y + 1,
							GUI_CHOOSE_WORLD_ARROW_WIDTH,
							GUI_CHOOSE_WORLD_ARROW_HEIGHT};
	SDL_Rect pos = {plane.x + plane.w + 1,
					plane.y + 1 + GUI_CHOOSE_WORLD_ARROW_HEIGHT,
					GUI_CHOOSE_WORLD_ARROW_WIDTH,
					plane.h - (GUI_CHOOSE_WORLD_ARROW_HEIGHT * 2)};
	SDL_Rect bottom_arrow_pos = {plane.x + plane.w + 1,
								plane.y + 1 + plane.h - GUI_CHOOSE_WORLD_ARROW_HEIGHT,
								GUI_CHOOSE_WORLD_ARROW_WIDTH,
								GUI_CHOOSE_WORLD_ARROW_HEIGHT};
	std::vector<SDL_Rect*> things_to_update_for_scrollbar;
	for (int i = 0; i < this->choose_world_screen_buttons.size(); i++) {
		things_to_update_for_scrollbar.push_back(this->choose_world_screen_buttons[i].GetPosReference());
	}
	try {
		this->choose_world_slider = new VerticalSlider(this->renderer, this->slider_arrow_texture, this->slider_thumb_texture, 
			top_arrow_pos, bottom_arrow_pos, pos, 0, 
			true, things_to_update_for_scrollbar);
	} catch (std::bad_alloc& ba) {
        std::cout << "Bad alloc caught: " << __FILE__ << ":" << __LINE__ << " " << ba.what() << std::endl;
    }
}

void Gamestate::HandleChooseWorldScreenInputs(SDL_Event& ev, bool& running) {
	while (SDL_PollEvent(&ev)) {
		switch (ev.type) {
			case SDL_QUIT:
				running = false;
			case SDL_KEYDOWN:
				if (ev.key.keysym.sym == SDLK_ESCAPE) {
					running = false;
				}
		}
		std::vector<Button>::iterator it;
		for (it = choose_world_screen_buttons.begin(); it != choose_world_screen_buttons.end(); ++it) {
			it->Update(ev, this);
		}
		this->choose_world_slider->Update(ev, this);
	}
}

void Gamestate::HandleChooseWorldUpdatesAndRendering(double delta_t) {
	// first clear the entire screen
	SDL_RenderClear(renderer);

	// render the background
	SDL_Rect choose_world_background = {0, 0, WIDTH, HEIGHT};
	SDL_RenderCopy(renderer, title_screen_background_texture, NULL, &choose_world_background);

	// load the game logo in the top left corner of the map
	int game_logo_w;
	int game_logo_h;
	SDL_QueryTexture(game_logo_texture, NULL, NULL, &game_logo_w, &game_logo_h);
	SDL_Rect game_logo_dstrect = {0, 0, game_logo_w / GUI_CHOOSE_WORLD_GAME_LOGO_WIDTH_DIVISOR,
								game_logo_h / GUI_CHOOSE_WORLD_GAME_LOGO_HEIGHT_DIVISOR};
	SDL_RenderCopy(renderer, game_logo_texture, NULL, &game_logo_dstrect);

	// make the plane where you display all the worlds
	SDL_Rect plane = {GUI_CHOOSE_WORLD_PLANE_X_PUSH_IN, GUI_CHOOSE_WORLD_PLANE_Y_PUSH_IN, 
					(WIDTH - GUI_CHOOSE_WORLD_PLANE_X_PUSH_IN) -  GUI_CHOOSE_WORLD_PLANE_X_PUSH_IN, 
					(HEIGHT - GUI_CHOOSE_WORLD_PLANE_Y_PUSH_IN) - GUI_CHOOSE_WORLD_PLANE_Y_PUSH_IN};
	SDL_SetRenderDrawColor(renderer, 69, 69, 69, 100);
	SDL_RenderFillRect(renderer, &plane);

	// render the buttons for each world
	std::vector<Button>::iterator it;
	for (it = choose_world_screen_buttons.begin(); it != choose_world_screen_buttons.end(); ++it) {
		it->Render();
	}

	// render the slider
	this->choose_world_slider->Render();

	// now remember to render the entire screen
	SDL_RenderPresent(renderer);
}

/***********************************
 * GAMEPLAY_SCREEN functions
***********************************/
void Gamestate::HandleGameplayUpdatesAndRendering(double delta_t) {
	PrintDebugLogs(delta_t);
	this->delta_t = delta_t;
	// Get character collision states
	std::tuple<bool, bool, bool, bool> character_collision_states = ch->GetCollisionStates();
	
	//Fall 
	bool bottom = std::get<1>(character_collision_states);
	if (bottom == false){
		ch->Fall();
	}
	
	// Set camera position to the corresponding character position, so
	// we dont' have to perform calculations on camera velocity
	SDL_Rect camera_new_pos {ch->GetPos().x - (WIDTH / 2) + TILE_WIDTH, ch->GetPos().y - (HEIGHT / 2) + TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT};
	c->SetPos(camera_new_pos);
	c->SetVelocity(ch->GetVelocity());
	c->SetVelocityGoal(ch->GetVelocityGoal());

	// Check for velocity or position errors: CheckForVelocityOrPositionErrors(c, ch);

	// Get mouse position
	int mouse_x = 0;
	int mouse_y = 0;
	SDL_GetMouseState(&mouse_x, &mouse_y);
	std::pair<int, int> mouse_pos;
	mouse_pos.first = mouse_x;
	mouse_pos.second = mouse_y;

	// Render Map.... CHARACTER RENDER IS IN CHARACTER UPDATE FUNCTION
	//m->UpdateItemDrops();
	//std::vector<ItemDrop>& map_item_drops = m->GetItemDrops();

	// Update stuff
	SDL_Rect camera_pos = c->GetPos();
	this->m->UpdateItemDrops();
	ch->Update(delta_t, camera_pos, *this->m);
	// update enemies if in range
	if (enemies.size() > 0) {
		for (size_t i = 0; i < enemies.size(); i++) {
			enemies[i].Update(*ch, *m, camera_pos, delta_t);
		}
	}

	// Render map
	SDL_RenderClear(renderer);
	SDL_Point tiles_starting_point = {c->GetPos().x - 100, c->GetPos().y - 100};
	SDL_Point tiles_ending_point = {c->GetPos().x + WIDTH + 100, c->GetPos().y + HEIGHT + 100};
	//DISABLE FRUSTRUM CULLING: std::vector<std::vector<Tile>> tiles = m->GetTiles();
	std::vector<std::vector<Tile>> tiles = this->m->GetTilesInRange(tiles_starting_point, tiles_ending_point);
	std::vector<std::vector<Tile>> background_tiles = m->GetBackgroundTilesInRange(tiles_starting_point, tiles_ending_point);
	c->Render(tiles, background_tiles, this->m->GetItemDrops(), background_texture, mouse_pos, ch->GetProjectiles());	// Render the scene and character with the camera class
	if (enemies.size() > 0) {
		for (size_t i = 0; i < enemies.size(); i++) {
			enemies[i].Render(camera_pos);
		}
	}

	//Render GUI and character
	//TEST: test_button.Render();
	ch->Render();

	// Render to screen
	SDL_RenderPresent(renderer);
}

void Gamestate::HandleGameplayInputs(SDL_Event& ev, bool& running) {
	while(SDL_PollEvent(&ev)) {
		switch (ev.type) {
			case SDL_QUIT:
				running = false;
				break;
			case SDL_KEYDOWN:
				//printf("[-] '%c' key pressed!", ev.key.keysym->sym);
				if (ev.key.keysym.sym == 27) {
					running = false;
				} else if (ev.key.keysym.sym == SDLK_a) {
					ch->MoveLeft();
				} else if (ev.key.keysym.sym == SDLK_d) {
					ch->MoveRight();
				} else if (ev.key.keysym.sym == SDLK_SPACE || ev.key.keysym.sym == SDLK_w) {
					ch->Jump();
				}
				break;
			case SDL_KEYUP:
				//printf("[-] '%c' key released!", ev.key.keysym->sym);
				if (ev.key.keysym.sym == SDLK_a) {
					ch->StopMoveLeft();
				} else if (ev.key.keysym.sym == SDLK_d) { 
					ch->StopMoveRight();
				} else if (ev.key.keysym.sym == SDLK_SPACE || ev.key.keysym.sym == SDLK_w) {
					ch->StopJump();
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (ev.button.button == SDL_BUTTON_LEFT) {
					printf("Left button pressed!\n");
					SDL_Point mouse_pos;
					SDL_GetMouseState(&mouse_pos.x, &mouse_pos.y);
					ch->AttackRange(this->projectile_texture, mouse_pos);
				} else if (ev.button.button == SDL_BUTTON_RIGHT) {
					printf("Right button pressed!\n");
				}
				break;
			default:
				break;
		}
		ch->HandleCharacterInputs(ev);	// also handles gui rendering for characters
	}
}

Gamestate::~Gamestate() {
	// cleanup map, camera, anch character objects
	delete m;
	delete c;
	delete ch;

	// cleanup misc textures
	SDL_DestroyTexture(button_texture);
	SDL_DestroyTexture(inventory_slot_texture);
	SDL_DestroyTexture(character_texture);
	SDL_DestroyTexture(background_texture);
	SDL_DestroyTexture(projectile_texture);
	SDL_DestroyTexture(title_screen_background_texture);
	SDL_DestroyTexture(game_logo_texture);

	// cleanup item textures
	std::map<int, SDL_Texture*>::iterator it = item_texture_mapper.begin();
	for (it; it != item_texture_mapper.end(); it++) {
		SDL_DestroyTexture(it->second);
	}

	// cleanup vertical slider
	delete this->choose_world_slider;
}