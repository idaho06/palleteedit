#ifndef GLOBALS_H
#define GLOBALS_H

#include "redrawscreen.h"
#include "pallete.h"

#define WIDTH 640
#define HEIGHT 480

#define BOXXLEN 255
#define BOXYLEN 31

#define BOXRX 32*1
#define BOXRY 32*1

#define BOXGX 32*1
#define BOXGY 32*3

#define BOXBX 32*1
#define BOXBY 32*5

#define BOXAX 32*1
#define BOXAY 32*7

#define BOXPX 32*1
#define BOXPY 32*9

/***********
 * Globals *
 ***********/

Sint16 G_boxRx[4] = { (Sint16)BOXRX, (Sint16)BOXRX+BOXXLEN, (Sint16)BOXRX+BOXXLEN, (Sint16)BOXRX }; 
Sint16 G_boxRy[4] = { (Sint16)BOXRY, (Sint16)BOXRY, (Sint16)BOXRY+BOXYLEN, (Sint16)BOXRY+BOXYLEN }; 

Sint16 G_boxGx[4] = { (Sint16)BOXGX, (Sint16)BOXGX+BOXXLEN, (Sint16)BOXGX+BOXXLEN, (Sint16)BOXGX }; 
Sint16 G_boxGy[4] = { (Sint16)BOXGY, (Sint16)BOXGY, (Sint16)BOXGY+BOXYLEN, (Sint16)BOXGY+BOXYLEN }; 

Sint16 G_boxBx[4] = { (Sint16)BOXBX, (Sint16)BOXBX+BOXXLEN, (Sint16)BOXBX+BOXXLEN, (Sint16)BOXBX }; 
Sint16 G_boxBy[4] = { (Sint16)BOXBY, (Sint16)BOXBY, (Sint16)BOXBY+BOXYLEN, (Sint16)BOXBY+BOXYLEN }; 

Sint16 G_boxAx[4] = { (Sint16)BOXAX, (Sint16)BOXAX+BOXXLEN, (Sint16)BOXAX+BOXXLEN, (Sint16)BOXAX }; 
Sint16 G_boxAy[4] = { (Sint16)BOXAY, (Sint16)BOXAY, (Sint16)BOXAY+BOXYLEN, (Sint16)BOXAY+BOXYLEN }; 

Sint16 G_boxPx[4] = { (Sint16)BOXPX, (Sint16)BOXPX+BOXXLEN, (Sint16)BOXPX+BOXXLEN, (Sint16)BOXPX }; 
Sint16 G_boxPy[4] = { (Sint16)BOXPY, (Sint16)BOXPY, (Sint16)BOXPY+BOXYLEN, (Sint16)BOXPY+BOXYLEN }; 

/* defined in redrawscreen.h
struct G_redraw_t {
    bool ui;
    bool G_pallete;
    bool pointlist;
    bool pointcursor;
} G_redraw;
*/

G_redraw_t G_redraw;

/* defined in redrawscreen.h
enum G_state_t {
    SELECT_POINT, EDIT_POINT, STATE_END
};
*/

G_state_t G_state; // main G_state of the program

SDL_Event G_event; // SDL event

Pallete G_pallete; // main class for calculating the G_pallete

int G_cursorPoint; // point selector

#endif /* GLOBALS_H */
