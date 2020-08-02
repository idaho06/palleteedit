#include "actions.h"
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

enum GUIElement {
    BOX_RED, BOX_GREEN, BOX_BLUE, BOX_ALPHA, BOX_PALLETE, GUI_NONE};

GUIElement getGUIElement(int x, int y){
    GUIElement gui = GUI_NONE;
    
    // check RED BOX
    if ((x >= G_boxRx[0]) && (x <= G_boxRx[2]) &&
       (y >= G_boxRy[0]) && (y <= G_boxRy[2]) ) {
        gui = BOX_RED;
        //printf("RED!\n");
    }
    // check GREEN BOX
    if ((x >= G_boxGx[0]) && (x <= G_boxGx[2]) &&
       (y >= G_boxGy[0]) && (y <= G_boxGy[2]) ) {
        gui = BOX_GREEN;
        //printf("GREEN!\n");
    }
    // check BLUE BOX
    if ((x >= G_boxBx[0]) && (x <= G_boxBx[2]) &&
       (y >= G_boxBy[0]) && (y <= G_boxBy[2]) ) {
        gui = BOX_BLUE;
        //printf("BLUE!\n");
    }
    // check ALPHA BOX
    if ((x >= G_boxAx[0]) && (x <= G_boxAx[2]) &&
       (y >= G_boxAy[0]) && (y <= G_boxAy[2]) ) {
        gui = BOX_ALPHA;
        //printf("ALPHA!\n");
    }
    // check PALLETE BOX
    if ((x >= G_boxPx[0]) && (x <= G_boxPx[2]) &&
       (y >= G_boxPy[0]) && (y <= G_boxPy[2]) ) {
        gui = BOX_PALLETE;
        //printf("ALPHA!\n");
    }

    return gui;
}



int leftClick(){
    GUIElement gui = GUI_NONE;
    int x, y, value;
    SDL_GetMouseState(&x, &y);
    gui = getGUIElement(x, y);

    switch(G_state){
        case SELECT_POINT: {
            switch(gui){
                case BOX_RED:{
                    // get new value for RED             
                    value = x - G_boxRx[0];
                    // get the current selected point's color
                    SDL_Color color = G_pallete.getPointColor(G_cursorPoint);
                    // change the red part
                    color.r = (Uint8)value;
                    // update the point in the pallete
                    G_pallete.setPointColor(G_cursorPoint, color);
                    // mark for redraw the gui pallete
                    G_redraw.pallete = true;
                    G_redraw.pointlist = true;
                    G_redraw.pointcursor = true;
                    break;
                }
                case BOX_GREEN:{
                    // get new value for GREEN             
                    value = x - G_boxGx[0];
                    // get the current selected point's color
                    SDL_Color color = G_pallete.getPointColor(G_cursorPoint);
                    // change the green part
                    color.g = (Uint8)value;
                    // update the point in the pallete
                    G_pallete.setPointColor(G_cursorPoint, color);
                    // mark for redraw the gui pallete
                    G_redraw.pallete = true;
                    G_redraw.pointlist = true;
                    G_redraw.pointcursor = true;
                    break;
                }
                case BOX_BLUE:{
                    // get new value for BLUE             
                    value = x - G_boxBx[0];
                    // get the current selected point's color
                    SDL_Color color = G_pallete.getPointColor(G_cursorPoint);
                    // change the blue part
                    color.b = (Uint8)value;
                    // update the point in the pallete
                    G_pallete.setPointColor(G_cursorPoint, color);
                    // mark for redraw the gui pallete
                    G_redraw.pallete = true;
                    G_redraw.pointlist = true;
                    G_redraw.pointcursor = true;
                    break;
                }
                case BOX_ALPHA:{
                    // get new value for ALPHA             
                    value = x - G_boxAx[0];
                    // get the current selected point's color
                    SDL_Color color = G_pallete.getPointColor(G_cursorPoint);
                    // change the alpha part
                    color.a = (Uint8)value;
                    // update the point in the pallete
                    G_pallete.setPointColor(G_cursorPoint, color);
                    // mark for redraw the gui pallete
                    G_redraw.pallete = true;
                    G_redraw.pointlist = true;
                    G_redraw.pointcursor = true;
                    break;
                }
                case BOX_PALLETE:{
                    // get new value for index in PALLETE             
                    value = x - G_boxPx[0];
                    // update the point in the pallete
                    G_pallete.setPointIndex(G_cursorPoint, (Uint8)value);
                    // mark for redraw the gui pallete
                    G_redraw.pallete = true;
                    G_redraw.pointlist = true;
                    G_redraw.pointcursor = true;
                    break;
                }
            }            
            break;
        }
    }            


    return 0;
}
