/*These are all in gamestate.h
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
*/
#include "gamestate.h"

// @TODO: MAKE FALLING AFFECT VELOCITY VECTORS

void test_callback(void* any) {
	printf("hi\n");
}

void CheckForVelocityOrPositionErrors(Camera& c, Character& ch) {
	// Check for position and velocity errors
	static int velocity_errors;
	static int pos_errors;
	if (CompareDoubles(c.GetVelocityGoal().first, ch.GetVelocityGoal().first) == false || CompareDoubles(c.GetVelocityGoal().second, ch.GetVelocityGoal().second) == false) {
		if (velocity_errors >= MAX_POS_ERRORS) {
			printf("\n\n[Error] Too many velocity errors! Camera velocity and character velocity do not equal!");
			exit(-1);
		} else {
			velocity_errors += 1;
		}
	} else if (ch.GetPos().x != c.GetPos().x + (WIDTH / 2) - TILE_WIDTH || ch.GetPos().y != c.GetPos().y + (HEIGHT / 2) - TILE_HEIGHT) {
		if (pos_errors >= MAX_POS_ERRORS) {
			printf("\n\n[Error] Too many position errors! Camera position and character position do not correspond!");
			exit(-1);
		} else {
			pos_errors += 1;
		}
	}
}

bool is_vsync_enabled() {
	FILE* fp = fopen("vsync.txt", "r");
	if (fp == NULL) {
		return false;
	}
	fclose(fp);
	return true;
}

int main() {
	// Seed the RNG with the current unix time
	srand(time(NULL));

	// Initialize SDL
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();

	// Create the window to render to
	SDL_DisplayMode dm;
	SDL_GetCurrentDisplayMode(0, &dm);
	WIDTH = dm.w;
	HEIGHT = dm.h;
	SDL_Window* window = SDL_CreateWindow("Draw",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			WIDTH,
			HEIGHT,
			SDL_WINDOW_FULLSCREEN);

	// Create the renderer
	bool vsync = is_vsync_enabled();
	SDL_Renderer* renderer = NULL;
	if (vsync == true) {
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	} else {
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	}

	// Set up music

	// Set up delta T stuff
	double previous_time = 0;
	double current_time = GetCurrentTime();
	double delta_t = 0;

	// Set up gamestate
	Gamestate gamestate(window, renderer);
	gamestate.LoadTitleScreenWidgets();
	gamestate.LoadChooseWorldWidgets();
	gamestate.SetCurrentScene(TITLE_SCREEN);
	gamestate.LoadNewMap();
	gamestate.SaveMap("NewWorld");
	//gamestate.LoadMap("NewWorld");
	std::cout << "toggle" << std::endl;
	
	//std::vector<double> times;

	// Game loop
	SDL_Event ev;
	bool running = true;
	while (running) {
		// start calculating delta_t
		previous_time = current_time;
		current_time = GetCurrentTime();

		// Get current scnee
		int scene = gamestate.GetCurrentScene();

		// Do actual work here
		switch (scene) {
			case TITLE_SCREEN:	// NOT WORKING YET
				// handle title screen
				gamestate.HandleTitleScreenInputs(ev, running);
				gamestate.HandleTitleScreenUpdatesAndRendering(delta_t);
				break;
			case CHOOSE_WORLD_SCREEN:
				gamestate.HandleChooseWorldScreenInputs(ev, running);
				gamestate.HandleChooseWorldUpdatesAndRendering(delta_t);
				break;
			case GAMEPLAY_SCREEN:
				// handle gameplay screen
				gamestate.HandleGameplayInputs(ev, running);
				gamestate.HandleGameplayUpdatesAndRendering(delta_t);
				break;
		}

		// debug here
		//PrintDebug(c, ch, delta_t);

		// calculate delta t
		//std::cout << 1/delta_t << std::endl;
		//times.push_back(delta_t);

		delta_t = current_time - previous_time;
		if (delta_t > 0.15) {
			delta_t = 0.15;
		}
	}

	//double sum = 0;
	//for (size_t i = 0; i < times.size(); i++) {
	//	sum += times[i];
	//}
	//std::cout << "Average FPS: " << 1 / (sum / (double)times.size()) << std::endl;

	// Clean up
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	return 0;
}
