#pragma once
#include <SDL2_gfxPrimitives.h>

struct G_redraw_t {
    bool ui;
    bool pallete;
    bool pointlist;
    bool pointcursor;
    bool instructions;
}; 

enum G_state_t {
    SELECT_POINT, EDIT_POINT, STATE_END
};

int redrawscreen(SDL_Renderer * renderer, SDL_Surface * surface);
