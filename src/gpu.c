#include <string.h>
#include <SDL3/SDL_render.h>
#include "gpu.h"
#include "constants.h"

Uint32 pixels[HEIGHT][WIDTH] = { BLACK };

void setPixel(int x, int y, enum Colour colour) {
    pixels[y][x] = colour;
}

void updateScreen(SDL_Texture *texture, SDL_Renderer *renderer) {
	Uint32 *pixelsFlattened;
	int pitch;

	if(SDL_LockTexture(texture, NULL, (void**) &pixelsFlattened, &pitch)) {
		for(int y = 0; y < HEIGHT; y++) {
			for(int x = 0; x < WIDTH; x++) {
				int idx = y * (pitch/4) + x;
				pixelsFlattened[idx] = pixels[y][x];
			}
		}

		SDL_UnlockTexture(texture);
	}

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	SDL_RenderTexture(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);
}

void resetGPU(SDL_Texture *texture, SDL_Renderer *renderer) {
    memset(pixels, BLACK, sizeof(pixels));
    updateScreen(texture, renderer);
}