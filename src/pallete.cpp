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
    cp = { .index = 127, .color = { .r = 0x00, .g = 0x00, .b = 0x00, .a = 0x44}};
    this->colorpoints.push_back(cp);
    cp = { .index = 128, .color = { .r = 0xff, .g = 0xff, .b = 0xff, .a = 0xcc}};
    this->colorpoints.push_back(cp);

    this->recalculate();

}

void Pallete::recalculate(){
    // we force point reordering on index value 
    std::sort(this->colorpoints.begin(), this->colorpoints.end(), compareColorPoint);

    int cursor = -1;
    ColorPoint first = this->colorpoints.front();
    ColorPoint last  = this->colorpoints.back();
    // we assume that the list of points always have minimum of one point
    // all colors the same from begining to first point
    do {
        cursor++;
        this->pallete[cursor] = first.color;
    } while (cursor < first.index );

    // TODO: linear interpolation from point to point
    
    // all colors the same from last point to end
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


