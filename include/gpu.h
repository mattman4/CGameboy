#ifndef GPU_H_
#define GPU_H_

enum Colour {
    WHITE = 0xFFFFFFFF,
    LIGHT_GRAY = 0xC8C8C8FF,
    DARK_GRAY = 0x505050FF,
    BLACK = 0x000000FF
};

void setPixel(int, int, enum Colour);
void updateScreen(SDL_Texture *, SDL_Renderer *);
void resetGPU(SDL_Texture *, SDL_Renderer *);

#endif