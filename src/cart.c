#include <SDL3/SDL_dialog.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_iostream.h>
#include <SDL3/SDL_render.h>
#include "cart.h" 
#include "gpu.h"
#include "constants.h"
#include "memory.h" // for rom

static SDL_Renderer *renderer = NULL;
static SDL_Texture *texture = NULL;

const SDL_DialogFileFilter filters[] = {
    {"GB Files", "gb"}
};

// maybe not the best way to do it but it works :)
void loadLogo(int offsetX, int offsetY) {
    int i = 0;

    // first half
    for (unsigned short addr = 0x104; addr <= 0x11B; addr += 2) {
        unsigned short two_bytes = (rom[addr] << 8) + (rom[addr+1]);
        
        int bit = 15;
        for (int row = 0; row < 4; row++) {
            for(int col = 0; col < 4; col++) {
                if((two_bytes >> bit) & 1) setPixel(i*4 + col + offsetX, row + offsetY, WHITE);
                bit--;
            }
        }
        i++;
    }

    i = 0;
    offsetY += 4;

    // second half
    for (unsigned short addr = 0x11C; addr <= 0x133; addr += 2) {
        unsigned short two_bytes = (rom[addr] << 8) + (rom[addr+1]);
        
        int bit = 15;
        for (int row = 0; row < 4; row++) {
            for(int col = 0; col < 4; col++) {
                if((two_bytes >> bit) & 1) setPixel(i*4 + col + offsetX, row + offsetY, WHITE);
                bit--;
            }
        }
        i++;
    }

    updateScreen(texture, renderer);
}

void SDLCALL callback(void *userdata, const char* const *filelist, int filter) {
    if(!filelist) {
        SDL_Log("Error opening file: %s", SDL_GetError());
        return;
    }

    if(!*filelist) {
        SDL_Log("Error opening file: no file selected");
        return;
    }

    SDL_Log("File selected: %s", *filelist);

    size_t datasize = 0;
    void *data = SDL_LoadFile(*filelist, &datasize);

    if(!data) {
        SDL_Log("Error reading file: %s", SDL_GetError());
        return;
    }

    if(datasize != 0x8000) {
        SDL_Log("Error reading file: expected 32k size");
        return;
    }

    memcpy(rom, data, 0x8000);

    // Read cartridge header (0x1000 - 0x014F)
    loadLogo(56, 68);
}

void loadrom(SDL_Window *window, SDL_Texture *t, SDL_Renderer *r) {
    renderer = r;
    texture = t;
    
    SDL_Log("Opening file prompt");
    SDL_ShowOpenFileDialog(callback, NULL, window, filters, SDL_arraysize(filters), NULL, false);
}

