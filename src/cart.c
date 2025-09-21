#include <SDL3/SDL_dialog.h>
#include <SDL3/SDL_log.h>
#include "cart.h"

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

    SDL_Log("File opened: %s", *filelist);
}

void loadrom(SDL_Window *window) {
    SDL_Log("Opening file prompt");
    SDL_ShowOpenFileDialog(callback, NULL, window, filters, SDL_arraysize(filters), NULL, false);
}

