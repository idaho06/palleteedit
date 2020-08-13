#pragma once

// includes
//
#include <SDL2/SDL.h>
#include <vector>

// Color definition
// for color we are using SDL_Color https://wiki.libsdl.org/SDL_Color
struct ColorPoint {
    Uint8 index;
    SDL_Color color;
};


// This class creates an array of colors
class Pallete{
    private:
        std::vector<ColorPoint> colorpoints;
        std::vector<SDL_Color> pallete;
        void recalculate();
        bool isIndexUsed(int index);
    public:
        Pallete(); // default to 256 colors in the pallete
        // Pallete(int size); // ?? 
        SDL_Color * getSDLColorArray(int &size);
        ColorPoint * getColorPointArray(int &size);
        SDL_Color getColor(int index);
        SDL_Color getPointColor(int pos);
        bool setPointColor(int pos, SDL_Color color);
        //bool setPoint(int index, SDL_Color color);
        bool setPointIndex(int pos, Uint8 newindex);
        bool setPointIndexLeft(int pos);
        bool setPointIndexRight(int pos);
        bool newPointColor(int pos, SDL_Color color);
        bool delPoint(int pos);
        bool savePalleteArray();
        bool savePointsArray(int slot = 1);
        ~Pallete();
};

