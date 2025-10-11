#define SDL_MAIN_USE_CALLBACKS 1

#include "constants.h"
#include <stdio.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "cart.h" // for loadrom

void updatePixels(void);

// https://examples.libsdl.org/SDL3/renderer/01-clear/

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Texture *texture = NULL;

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

	updatePixels();

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
			loadrom(window);
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

void updatePixels() {
	Uint32 *pixels;
	int pitch;

	if(SDL_LockTexture(texture, NULL, (void**) &pixels, &pitch)) {
		for(int y = 0; y < HEIGHT; y++) {
			for(int x = 0; x < WIDTH; x++) {
				int idx = y * (pitch/4) + x;
				pixels[idx] = idx & 1 ? 0xFF0000FF : 0x00FF00FF;
			}
		}

		SDL_UnlockTexture(texture);
	}

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	SDL_RenderTexture(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);
}