#include "pallete.h"
#include <algorithm> // for std::sort

bool compareColorPoint(ColorPoint cp1, ColorPoint cp2){
    return (cp1.index < cp2.index);
}

Pallete::Pallete(){
    // size of pallete is 256 by default
    this->pallete.reserve(256);

    // set default point list
    
    ColorPoint cp;
    //    i   r     g     b     a
    cp = { .index = 10, .color = { .r = 0x10, .g = 0x10, .b = 0x10, .a = 0xff}};
    this->colorpoints.push_back(cp);
    cp = { .index = 128, .color = { .r = 0xff, .g = 0xff, .b = 0xff, .a = 0xff}};
    this->colorpoints.push_back(cp);
    cp = { .index = 250, .color = { .r = 0x0f, .g = 0x00, .b = 0xff, .a = 0xff}};
    this->colorpoints.push_back(cp);


    this->recalculate();

}

void Pallete::recalculate(){
    // we force point reordering on index value 
    std::sort(this->colorpoints.begin(), this->colorpoints.end(), compareColorPoint);

    int cursor = -1;
    int step = -1;
    int delta = -1;
    ColorPoint first = this->colorpoints.front();
    ColorPoint last  = this->colorpoints.back();
    //Uint8 current = first.index;
    SDL_Color color;
    color = { .r = 0x00, .g = 0x00, .b = 0x00, .a = 0xff};
    // we assume that the list of points always have minimum of one point
    // all colors the same from begining to first point
    do {
        cursor++;
        this->pallete[cursor] = first.color;
    } while (cursor < first.index );

    // linear interpolation from point to point
    std::vector<ColorPoint>::iterator it = this->colorpoints.begin();
    while(it != this->colorpoints.end() - 1){
        //printf("%u - ", it->index);
        step = 0;
        delta = (it + 1)->index - it->index;
        for (cursor = it->index; cursor < (it + 1)->index; cursor++){
            color.r = static_cast<Uint8>((float)it->color.r + (((float)(it+1)->color.r - (float)it->color.r)*((float)step/(float)delta)));
            color.g = static_cast<Uint8>((float)it->color.g + (((float)(it+1)->color.g - (float)it->color.g)*((float)step/(float)delta)));
            color.b = static_cast<Uint8>((float)it->color.b + (((float)(it+1)->color.b - (float)it->color.b)*((float)step/(float)delta)));
            color.a = static_cast<Uint8>((float)it->color.a + (((float)(it+1)->color.a - (float)it->color.a)*((float)step/(float)delta)));
            this->pallete[cursor] = color;
            //printf("i: %u r: %u g: %u b: %u a: %u \n", cursor, color.r, color.g, color.b, color.a);
            step++;
        }

        it++; // next color point
    }
    
    // all colors the same from last point to end
    cursor = static_cast<int>(last.index) - 1;
    while (cursor < 255) {
        cursor++;
        this->pallete[cursor] = last.color;
    };
}

SDL_Color Pallete::getColor(int index){
    if (index < 0) {
        index = 0;
    }
    if (index > 255) {
        index = 255;
    }
    return this->pallete[index];
}

SDL_Color Pallete::getPointColor(int pos){
    int size = static_cast<int>(colorpoints.size());
    if (pos < 0) {
        pos = 0;
    }
    if (pos > size-1) {
        pos = size-1;
    }
    return this->colorpoints[pos].color;
}

SDL_Color * Pallete::getSDLColorArray(int &size){
    size = this->pallete.size();
    return this->pallete.data();
};

ColorPoint * Pallete::getColorPointArray(int &size){
    size = this->colorpoints.size();
    return this->colorpoints.data();
};

bool Pallete::setPointColor(int pos, SDL_Color color){
    int size = static_cast<int>(colorpoints.size());
    if (pos < 0) {
        pos = 0;
    }
    if (pos > size-1) {
        pos = size-1;
    }
    this->colorpoints[pos].color = color;
    this->recalculate();
    return true;
}
bool Pallete::setPointIndex(int pos, Uint8 newindex){
    int size = static_cast<int>(colorpoints.size());
    if (pos < 0) {
        pos = 0;
    }
    if (pos > size-1) {
        pos = size-1;
    }
    // TODO: check if there is another point with same index.
    this->colorpoints[pos].index = newindex;
    this->recalculate();
    return true;
}


Pallete::~Pallete(){

}


