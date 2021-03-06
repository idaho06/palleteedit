#include <stdio.h>
#include <SDL2_gfxPrimitives.h>

#include "redrawscreen.h"
#include "actions.h"
#include "pallete.h"
#include "globals.h"


/*************
 * Functions *
 *************/



// *window and *renderer pointers has to be declared outside this function
int initscreen(SDL_Window **window, SDL_Renderer **renderer) {
 
    if (SDL_Init(SDL_INIT_VIDEO))
    {
       printf ("SDL_Init Error: %s", SDL_GetError());
       // This returns should be exceptions
       return 1;
    }
 
    *window = SDL_CreateWindow("Pallete Edit", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if (*window == NULL)
    {
       printf ("SDL_CreateWindow Error: %s", SDL_GetError());
       SDL_Quit();
       return 2;
    }
 
    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_SOFTWARE );
    if (renderer == NULL)
    {
       SDL_DestroyWindow(*window);
       printf ("SDL_CreateRenderer Error: %s", SDL_GetError());
       SDL_Quit();
       return 3;
    }
    return 0;
}

/********
 * main *
 ********/

int main(int argc, char* argv[])
{
    // Globals init
    G_state = SELECT_POINT;
    G_redraw.ui = true;
    G_redraw.pallete = true;
    G_redraw.pointlist = true;
    G_redraw.pointcursor = true;
    G_redraw.instructions = true;

    G_cursorPoint = 0;

    // Create window and renderer
    SDL_Window * window = NULL;
    SDL_Renderer * renderer = NULL;
    initscreen(&window,&renderer);
    
    // First clear screen
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xff);
    SDL_RenderClear(renderer); 
 
    // Load texture for the background of the G_boxes
    SDL_Surface * surface = SDL_LoadBMP("texture.bmp");
    if (surface == NULL) {
        printf("texture.bmp not found");
        return -1;
    }
 
    // check keyboard and mouse envents
    SDL_Event e;
 
    int quit = 0;
    while (!quit)
    {
        // check events and change program status
        quit = checkEvents();
        // Redraw all the things!!  
        redrawscreen(renderer, surface);        
        SDL_RenderPresent(renderer);
        SDL_Delay(15);
    }
 
    // It's polite to free resources before exit
    SDL_FreeSurface(surface);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
