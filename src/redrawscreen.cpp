#define TLEN 255

#include "pallete.h"
#include "redrawscreen.h"
#include <SDL2_gfxPrimitives.h>

// Globals used here
extern Pallete G_pallete; 
extern struct G_redraw_t G_redraw;
extern Sint16 G_boxRx[]; 
extern Sint16 G_boxRy[]; 
extern Sint16 G_boxGx[]; 
extern Sint16 G_boxGy[]; 
extern Sint16 G_boxBx[]; 
extern Sint16 G_boxBy[]; 
extern Sint16 G_boxAx[]; 
extern Sint16 G_boxAy[]; 
extern Sint16 G_boxPx[]; 
extern Sint16 G_boxPy[]; 
extern int G_cursorPoint; 
extern enum G_state_t G_state;

int redrawscreen(SDL_Renderer * renderer, SDL_Surface * surface){
    // index and text char array
    Uint8 i;
    char text[TLEN+1];
    SDL_Color color;

    if (G_redraw.ui) {
       
        // texts
        SDL_strlcpy(text,"Pallete Editor, by Idaho06 of AkInOsOfT L.s.D.",TLEN);
        stringRGBA (renderer, 0, 0, text, 255, 255, 0, 255);

        /* Red G_box */
        SDL_strlcpy(text,"- RED -", TLEN);
        stringRGBA (renderer, G_boxRx[0], G_boxRy[0] - 9, text, 255, 0, 0, 255);
        rectangleRGBA(renderer, G_boxRx[0] - 1, G_boxRy[0] - 1, G_boxRx[2] + 2, G_boxRy[2] + 2, 255, 255, 255, 255);
        //texturedPolygon(renderer, G_boxRx, G_boxRy, 4, surface, 0, 0);
        i = 0xff;
        do {
            vlineRGBA(renderer, G_boxRx[0] + (Sint16)i, G_boxRy[0], G_boxRy[2], i, 0x00, 0x00, 0xff);
        } while (i--);


        /* Green G_box */
        SDL_strlcpy(text,"- GREEN -", TLEN);
        stringRGBA (renderer, G_boxGx[0], G_boxGy[0] - 9, text, 0, 255, 0, 255);
        rectangleRGBA(renderer, G_boxGx[0] - 1, G_boxGy[0] - 1, G_boxGx[2] + 2, G_boxGy[2] + 2, 255, 255, 255, 255);
        //texturedPolygon(renderer, G_boxGx, G_boxGy, 4, surface, 0, 0);
        i = 0xff;
        do {
            vlineRGBA(renderer, G_boxGx[0] + (Sint16)i, G_boxGy[0], G_boxGy[2], 0x00, i, 0x00, 0xff);
        } while (i--);


        /* Blue G_box */
        SDL_strlcpy(text,"- BLUE -", TLEN);
        stringRGBA (renderer, G_boxBx[0], G_boxBy[0] - 9, text, 0, 0, 255, 255);
        rectangleRGBA(renderer, G_boxBx[0] - 1, G_boxBy[0] - 1, G_boxBx[2] + 2, G_boxBy[2] + 2, 255, 255, 255, 255);
        //texturedPolygon(renderer, G_boxBx, G_boxBy, 4, surface, 0, 0);
        i = 0xff;
        do {
            vlineRGBA(renderer, G_boxBx[0] + (Sint16)i, G_boxBy[0], G_boxBy[2], 0x00, 0x00, i, 0xff);
        } while (i--);


        /* Alpha G_box */
        SDL_strlcpy(text,"- ALPHA -", TLEN);
        stringRGBA (renderer, G_boxAx[0], G_boxAy[0] - 9, text, 255, 255, 255, 255);
        rectangleRGBA(renderer, G_boxAx[0] - 1, G_boxAy[0] - 1, G_boxAx[2] + 2, G_boxAy[2] + 2, 255, 255, 255, 255);
        // alpha color is drawn in G_redraw.pallete

        /* Pallete G_box */
        SDL_strlcpy(text,"- PALLETE -", TLEN);
        stringRGBA (renderer, G_boxPx[0], G_boxPy[0] - 9, text, 255, 255, 255, 255);
        rectangleRGBA(renderer, G_boxPx[0] - 1, G_boxPy[0] - 1, G_boxPx[2] + 2, G_boxPy[2] + 2, 255, 255, 255, 255);
        
        // do not G_redraw in next frame
        G_redraw.ui = false;
    }
    if (G_redraw.pallete){
        // Draw alpha with current color
        texturedPolygon(renderer, G_boxAx, G_boxAy, 4, surface, 0, 0);
        i = 0xff;
        do {
            color = G_pallete.getPointColor(G_cursorPoint);
            vlineRGBA(renderer, G_boxAx[0] + (Sint16)i, G_boxAy[0], G_boxAy[2], color.r, color.g, color.b, i);
        } while (i--);


        // G_pallete G_redraw here
        texturedPolygon(renderer, G_boxPx, G_boxPy, 4, surface, 0, 0);
        // here we call the G_pallete library to draw the result G_pallete
        i = 0xff;
        do {
            color = G_pallete.getColor(i);
            vlineRGBA(renderer, G_boxPx[0] + (Sint16)i, G_boxPy[0], G_boxPy[2], color.r, color.g, color.b, color.a);
        } while (i--);
        G_redraw.pallete = false;
    }

    // colorpoint data
    ColorPoint * colorpoints = NULL;
    int size = 0;

    // colorpoint list position and size
    int rx, ry, width, height;
    rx = 32 * 10;
    ry = 32 * 1;
    width = 36*8;
    height = 256;

    if (G_redraw.pointlist){
      // first we delete previous data
        boxRGBA(renderer, rx, ry, rx + width, ry + height, 0x00, 0x00, 0x00, 0xff);

        // for each point in the list
        colorpoints = G_pallete.getColorPointArray(size);

        for (int i = 0; i < size; i++){
            //printf("index: %d red: %d green: %d blue: %d alpha: %d \n", colorpoints[i].index, colorpoints[i].color.r, colorpoints[i].color.g, colorpoints[i].color.b, colorpoints[i].color.a); 
            SDL_snprintf(text, TLEN, "i: %d", colorpoints[i].index); 
            stringRGBA(renderer, rx+(8*1), ry+(i*10), text, 0xff, 0xff, 0xff, 0xff);
            SDL_snprintf(text, TLEN, "R: %d", colorpoints[i].color.r); 
            stringRGBA(renderer, rx+(8*8), ry+(i*10), text, 0xff, 0xff, 0xff, 0xff);
            SDL_snprintf(text, TLEN, "G: %d", colorpoints[i].color.g); 
            stringRGBA(renderer, rx+(8*15), ry+(i*10), text, 0xff, 0xff, 0xff, 0xff);
            SDL_snprintf(text, TLEN, "B: %d", colorpoints[i].color.b); 
            stringRGBA(renderer, rx+(8*22), ry+(i*10), text, 0xff, 0xff, 0xff, 0xff);
            SDL_snprintf(text, TLEN, "A: %d", colorpoints[i].color.a); 
            stringRGBA(renderer, rx+(8*29), ry+(i*10), text, 0xff, 0xff, 0xff, 0xff);
        }; 

        G_redraw.pointlist = false;
    }

    if (G_redraw.pointcursor){
        // G_redraw cursor for selected point
        // first we delete every possible selection
        colorpoints = G_pallete.getColorPointArray(size);
        // cursor in bounds
        if (G_cursorPoint < 0) {G_cursorPoint = 0;}
        if (G_cursorPoint > size - 1) {G_cursorPoint = size - 1;}

        // delete previous cursors
        for (int i = 0; i < size; i++){
            rectangleRGBA(renderer, rx+(8*0), ry+(i*10)-2, rx+(8*0)+width, ry+((i+1)*10)-1, 0x00, 0x00, 0x00, 0xff);
        }
        // draw cursor
        rectangleRGBA(renderer, rx+(8*0), ry+(G_cursorPoint*10)-2, rx+(8*0)+width, ry+((G_cursorPoint+1)*10)-1, 0xff, 0xff, 0x00, 0xff);

        // draw red value for current point
        boxRGBA(renderer, G_boxRx[0], G_boxRy[2]+2, G_boxRx[2], G_boxRy[2]+16, 0x00, 0x00, 0x00, 0xff );
        vlineRGBA(renderer, 
                G_boxRx[0] + (Sint16)colorpoints[G_cursorPoint].color.r, 
                G_boxRy[2]+2, G_boxRy[2]+16, 0xff, 0xff, 0x00, 0xff);
        // draw green value for current point
        boxRGBA(renderer, G_boxGx[0], G_boxGy[2]+2, G_boxGx[2], G_boxGy[2]+16, 0x00, 0x00, 0x00, 0xff );
        vlineRGBA(renderer, 
                G_boxGx[0] + (Sint16)colorpoints[G_cursorPoint].color.g, 
                G_boxGy[2]+2, G_boxGy[2]+16, 0xff, 0xff, 0x00, 0xff);
        // draw blue value for current point
        boxRGBA(renderer, G_boxBx[0], G_boxBy[2]+2, G_boxBx[2], G_boxBy[2]+16, 0x00, 0x00, 0x00, 0xff );
        vlineRGBA(renderer, 
                G_boxBx[0] + (Sint16)colorpoints[G_cursorPoint].color.b, 
                G_boxBy[2]+2, G_boxBy[2]+16, 0xff, 0xff, 0x00, 0xff);
        // draw alpha value for current point
        boxRGBA(renderer, G_boxAx[0], G_boxAy[2]+2, G_boxAx[2], G_boxAy[2]+16, 0x00, 0x00, 0x00, 0xff );
        vlineRGBA(renderer, 
                G_boxAx[0] + (Sint16)colorpoints[G_cursorPoint].color.a, 
                G_boxAy[2]+2, G_boxAy[2]+16, 0xff, 0xff, 0x00, 0xff);
        // draw all point in the pallete. The selected one with a larger line
        boxRGBA(renderer, G_boxPx[0], G_boxPy[2]+2, G_boxPx[2], G_boxPy[2]+16, 0x00, 0x00, 0x00, 0xff );
        for (int i = 0; i < size; i++){
            vlineRGBA(renderer, 
                G_boxPx[0] + (Sint16)colorpoints[i].index, 
                G_boxPy[2]+2, G_boxPy[2]+8, 0xff, 0xff, 0x00, 0xff);
        }
        vlineRGBA(renderer, 
                G_boxPx[0] + (Sint16)colorpoints[G_cursorPoint].index, 
                G_boxPy[2]+2, G_boxPy[2]+16, 0xff, 0xff, 0x00, 0xff);
                
        // no more cursor drawing for next frame
        G_redraw.pointcursor = false;
    }

    rx = 8*4;
    ry = 8*48;
    width = 8*40;
    height = 8*10;

    if (G_redraw.instructions){
        //delete old text
        boxRGBA(renderer, rx, ry, rx + width, ry + height, 0x00, 0x00, 0x00, 0xff);
        // write text for current program status
        switch (G_state){
            case SELECT_POINT: 
            {
                SDL_strlcpy(text,"UP, DOWN   : select point in pallete", TLEN);
                stringRGBA (renderer, rx+(8*0), ry+(8*0), text, 0x88, 0x88, 0x88, 0xff);
                SDL_strlcpy(text,"LEFT CLICK : change value", TLEN);
                stringRGBA (renderer, rx+(8*0), ry+(8*1), text, 0x88, 0x88, 0x88, 0xff);
                SDL_strlcpy(text,"RIGHT CLICK: create point", TLEN);
                stringRGBA (renderer, rx+(8*0), ry+(8*2), text, 0x88, 0x88, 0x88, 0xff);
                SDL_strlcpy(text,"DEL        : delete point", TLEN);
                stringRGBA (renderer, rx+(8*0), ry+(8*3), text, 0x88, 0x88, 0x88, 0xff);
                SDL_strlcpy(text,"A, D       : move point left, right", TLEN);
                stringRGBA (renderer, rx+(8*0), ry+(8*4), text, 0x88, 0x88, 0x88, 0xff);
                SDL_strlcpy(text,"F5 : save pallete array", TLEN);
                stringRGBA (renderer, rx+(8*0), ry+(8*7), text, 0x88, 0x88, 0x88, 0xff);
                SDL_strlcpy(text,"F6 : save color points", TLEN);
                stringRGBA (renderer, rx+(8*0), ry+(8*8), text, 0x88, 0x88, 0x88, 0xff);
                SDL_strlcpy(text,"ESC: exit", TLEN);
                stringRGBA (renderer, rx+(8*0), ry+(8*9), text, 0x88, 0x88, 0x88, 0xff);
                break;
            }
        }
        G_redraw.instructions = false;
    }

    return 0;
}
