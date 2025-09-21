#define SDL_MAIN_USE_CALLBACKS 1

#define APP_NAME "CGameboy"
#define VERSION "0.0.1"
#define WIDTH 160
#define HEIGHT 144

#include <stdio.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "cart.h"

// https://examples.libsdl.org/SDL3/renderer/01-clear/

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

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
	SDL_Log("Goodbye!");
}