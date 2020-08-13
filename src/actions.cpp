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
extern SDL_Event G_event;

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
        case SELECT_POINT: 
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

    return 0;
}

int rightClick() {
    GUIElement gui = GUI_NONE;
    int x, y, value;
    SDL_GetMouseState(&x, &y);
    gui = getGUIElement(x, y);

    switch(G_state){
        case SELECT_POINT: 
            switch(gui){
                case BOX_PALLETE:
                    value = x - G_boxPx[0];
                    if (G_pallete.newPointColor(value, G_pallete.getPointColor(G_cursorPoint))) {
                        G_redraw.pallete = true;
                        G_redraw.pointlist = true;
                        G_redraw.pointcursor = true;
                    }
                    break;
                
            } // end of swith(gui)
            break;
        
    } // end of swith(G_state)
 
    return 0;
}

int movePointLeft() {
    if (G_pallete.setPointIndexLeft(G_cursorPoint)){
        G_redraw.pallete = true;
        G_redraw.pointlist = true;
        G_redraw.pointcursor = true;                
        return 0;
    } else {
        return -1;
    }
}

int movePointRight() {
    if (G_pallete.setPointIndexRight(G_cursorPoint)){
        G_redraw.pallete = true;
        G_redraw.pointlist = true;
        G_redraw.pointcursor = true;                
        return 0;
    } else {
        return -1;
    }
}

int delPoint(){
    if(G_pallete.delPoint(G_cursorPoint)){
        G_redraw.pallete = true;
        G_redraw.pointlist = true;
        G_redraw.pointcursor = true;
        return 0;
    } else {
        return -1;
    }
}

int savePalleteArray(){
    if (G_pallete.savePalleteArray()){
        printf("Pallete saved\n");
    }
    
    return 0;
}

int savePointsArray(int slot){
    if (G_pallete.savePointsArray(slot)){
        printf("Points saved to slot %d\n", slot);
    }
    
    return 0;
}

int loadPointsArray(int slot){
    if (G_pallete.loadPointsArray(slot)){
        printf("Points load from slot %d\n", slot);
        G_redraw.pallete = true;
        G_redraw.pointlist = true;
        G_redraw.pointcursor = true;
    }
    return 0;
}

int checkEvents(){
    while (SDL_PollEvent(&G_event)){
        switch(G_event.type){
            case SDL_QUIT: 
                return 1;
                break;
            
            /************
             * KEYBOARD *
             ************/               
            case SDL_KEYUP: 
                switch (G_event.key.keysym.sym) {
                    case SDLK_SPACE: 
                        break;
                    
                    case SDLK_ESCAPE: 
                        return 1;                  
                        break;
                    
                    case SDLK_r: 
                        G_redraw.ui = true;
                        G_redraw.pallete = true;
                        G_redraw.pointcursor = true;
                        G_redraw.pointlist = true;
                        G_redraw.instructions = true;
                        break;
                    
                    case SDLK_DOWN: 
                        G_cursorPoint++;
                        G_redraw.pallete = true;
                        G_redraw.pointcursor = true;
                        break;
                    
                    case SDLK_UP: 
                        G_cursorPoint--;
                        G_redraw.pallete = true;
                        G_redraw.pointcursor = true;
                        break;
                    
                    case SDLK_a: 
                        movePointLeft();                
                        break;
                    
                    case SDLK_d: 
                        movePointRight();                
                        break;
                    
                    case SDLK_BACKSPACE: 
                        delPoint();
                        break;
                    
                    case SDLK_F1: 
                        loadPointsArray(1);
                        break;
                    case SDLK_F2: 
                        loadPointsArray(2);
                        break;
                    case SDLK_F3: 
                        loadPointsArray(3);
                        break;
                    case SDLK_F4: 
                        loadPointsArray(4);
                        break;

                    case SDLK_F5: 
                        savePalleteArray();
                        break;
                    
                    case SDLK_F6: 
                        savePointsArray(1);
                        break;
                    case SDLK_F7: 
                        savePointsArray(2);
                        break;
                    case SDLK_F8: 
                        savePointsArray(3);
                        break;
                    case SDLK_F9: 
                        savePointsArray(4);
                        break;
                                         
                    case SDLK_F10: 
                        break;
                                         
                } // end of switch (G_event.key.keysym.sym)
                break;
            // end of case SDL_KEYUP: 
            /*****************
             * MOUSE BUTTONS *
             *****************/                  
            case SDL_MOUSEBUTTONDOWN: 
                switch (G_event.button.button) {
                    case SDL_BUTTON_LEFT: 
                        leftClick(); // checks mouse click position and changes point values                 
                        break;
                    
                    case SDL_BUTTON_RIGHT: 
                        rightClick(); // create a new point
                        break;
                    
                }                          
                break;                          
            
        } // end of switch(G_event.type)
    } // end of while (SDL_PollEvent(&G_event))
    return 0;
}


