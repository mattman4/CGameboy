#define SDL_MAIN_USE_CALLBACKS 1

#include "constants.h"
#include <stdio.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "cart.h" // for loadrom
#include "gpu.h"

void colourShowcase();

// https://examples.libsdl.org/SDL3/renderer/01-clear/

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static SDL_Texture *texture = NULL;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv) {
	SDL_SetAppMetadata(APP_NAME, VERSION, "com.mattman.gb_emu");

	if (!SDL_Init(SDL_INIT_VIDEO)) {
		SDL_Log("Couldn't initialise SDL: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	if (!SDL_CreateWindowAndRenderer(APP_NAME, WIDTH, HEIGHT, 0, &window, &renderer)) {
		SDL_Log("Couldn't create SDL window/renderer: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	if(!(texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT))) {
		SDL_Log("Couldn't create SDL texture: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}
	
	if(!SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST)) {
		SDL_Log("Couldn't set SDL texture scale mode: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	SDL_Log("%s %s", APP_NAME, VERSION);
	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {

	if (event->type == SDL_EVENT_QUIT) {
		return SDL_APP_SUCCESS;
	}

	if(event->type == SDL_EVENT_KEY_DOWN)
	{
		if(event->key.key == SDLK_L && event->key.mod & SDL_KMOD_CTRL) {
			loadrom(window, texture, renderer);
		}

		if(event->key.key == SDLK_K && event->key.mod & SDL_KMOD_CTRL) {
			colourShowcase();
		}
	}

	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* appstate) {
	return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void* appstate, SDL_AppResult result) {
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	SDL_Log("Goodbye!");
}

void colourShowcase() {
	for(int j = 0; j < HEIGHT; j++) {
		enum Colour colour = BLACK;

		if(j < (HEIGHT/4)) {
			colour = WHITE;
		} else if(j < (HEIGHT/4)*2) {
			colour = LIGHT_GRAY;
		} else if(j < (HEIGHT/4)*3) {
			colour = DARK_GRAY;
		}
		
		for(int i = 0; i < WIDTH; i++) {
			setPixel(i, j, colour);
		}
	}
	updateScreen(texture, renderer);
}