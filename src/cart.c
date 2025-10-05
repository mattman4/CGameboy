#include <SDL3/SDL_dialog.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_iostream.h>
#include "cart.h"
#include "memory.h" // for rom

const SDL_DialogFileFilter filters[] = {
    {"GB Files", "gb"}
};

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
}

void loadrom(SDL_Window *window) {
    SDL_Log("Opening file prompt");
    SDL_ShowOpenFileDialog(callback, NULL, window, filters, SDL_arraysize(filters), NULL, false);
}

