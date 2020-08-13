#include "pallete.h"
#include <algorithm> // for std::sort
#include <fstream> // for std::ofstream and std::ifstream

bool compareColorPoint(ColorPoint cp1, ColorPoint cp2){
    return (cp1.index < cp2.index);
}

Pallete::Pallete(){
    // size of pallete is 256 by default
    this->pallete.reserve(256);

    // lets blank it
    Uint8 i = 0xff;
    SDL_Color c = {.r = 0x00, .g = 0x00, .b = 0x00, .a = 0xff};
    do {
        this->pallete.push_back(c);
    } while (i--);

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
    if (!this->isIndexUsed(newindex)){
        this->colorpoints[pos].index = newindex;
        this->recalculate();
        return true;
    } else {
        return false;
    }
}

bool Pallete::isIndexUsed(int index){
    bool found = false;
    std::vector<ColorPoint>::iterator it = this->colorpoints.begin();
    while(it != this->colorpoints.end()){
        if (it->index == index) {
            found = true;
        }
        it++; // next color point
    }
 
    return found;
}

bool Pallete::setPointIndexLeft(int pos){
    int size = static_cast<int>(colorpoints.size());
    if (pos < 0) {
        pos = 0;
    }
    if (pos > size-1) {
        pos = size-1;
    }
    // if point is the first, then set index to 0x00
    if (pos == 0){
        this->colorpoints[pos].index = 0x00;
    } else {
        // else, set index to (point-1).index + 1
        this->colorpoints[pos].index = this->colorpoints[pos-1].index + 0x01;
    }
    this->recalculate();
    return true;
}

bool Pallete::setPointIndexRight(int pos){
    int size = static_cast<int>(colorpoints.size());
    if (pos < 0) {
        pos = 0;
    }
    if (pos > size-1) {
        pos = size-1;
    }
    // if point is the last, then set index to 0xff
    if (pos == size-1) {
        this->colorpoints[pos].index = 0xff;
    } else {
        // else, set index to (point+1).index - 1
        this->colorpoints[pos].index = this->colorpoints[pos+1].index - 0x01;
    }
    this->recalculate();
    return true;
}

bool Pallete::newPointColor(int pos, SDL_Color color){
    if (!this->isIndexUsed(pos)){
        ColorPoint cp;
        //    i   r     g     b     a
        cp = { .index = static_cast<Uint8>(pos), 
            .color = { .r = color.r, .g = color.g, .b = color.b, .a = color.a}};
        this->colorpoints.push_back(cp);
        this->recalculate();
        return true;
    } else {
        return false;
    }
}

bool Pallete::delPoint(int pos){
    int size = static_cast<int>(colorpoints.size());
    if (pos < 0) {
        pos = 0;
    }
    if (pos > size-1) {
        pos = size-1;
    }
    if (size > 1) {
        this->colorpoints.erase(this->colorpoints.begin()+pos);
        this->recalculate();
        return true;
    } else {
        return false;
    }
}

bool Pallete::savePalleteArray(){
    bool result = false;
    int size = 0;
    int elementSize = sizeof(SDL_Color);
    SDL_Color * palleteArray = this->getSDLColorArray(size);

    printf("array size: %d\nPointer: %p\n", size, (void *)palleteArray);

    if((size>0) && (palleteArray != nullptr)){
        std::ofstream palleteFile ("pallete.pal",
                std::ios::out | std::ios::binary | std::ios::trunc);
        if (palleteFile.is_open()){
            palleteFile.write((char *)palleteArray, size*elementSize);
            palleteFile.close();
            result = true;
        }
    }
    return result;
}

bool Pallete::savePointsArray(int slot){
    if (slot < 1) {slot = 1;}
    if (slot > 4) {slot = 4;}
    char file[80];
    SDL_snprintf(file, 80, "points%d.pps", slot); 
    bool result = false;
    int size = 0;
    int elementSize = sizeof(ColorPoint);
    ColorPoint * pointArray = this->getColorPointArray(size);

    printf("array size: %d\nPointer: %p\n", size, (void *)pointArray);

    if((size>0) && (pointArray != nullptr)){
        std::ofstream pointsFile (file,
                std::ios::out | std::ios::binary | std::ios::trunc);
        if (pointsFile.is_open()){
            pointsFile.write((char *)pointArray, size*elementSize);
            pointsFile.close();
            result = true;
        }
    }
    return result;
}

bool Pallete::loadPointsArray(int slot){
    bool result = false;
    if (slot < 1) {slot = 1;}
    if (slot > 4) {slot = 4;}
    char file[80];
    SDL_snprintf(file, 80, "points%d.pps", slot);
    std::vector<ColorPoint> loadColorPoints;
    ColorPoint cp = { .index = 0, .color = { .r = 0x00, .g = 0x00, .b = 0x00, .a = 0xff}};
    std::streamsize colorPointSize = sizeof(ColorPoint);
    int fileSize = 0;
    
    // first, get file size
    // http://www.cplusplus.com/doc/tutorial/files/
    std::streampos begin,end;
    std::ifstream pointsFile (file,
        std::ios::in|std::ios::binary); // open the file
    if (pointsFile.is_open()){ // if file has been open
        begin = pointsFile.tellg(); // get the begin..
        pointsFile.seekg(0, std::ios::end); // go to end..
        end = pointsFile.tellg(); // get the end
        fileSize = end - begin; // calculate file size
    }    

    if (    (fileSize > 0) && // if file size is non empty and...
            (fileSize % colorPointSize == 0) && // file size is multiple of point size and...
            pointsFile.is_open() ) { // the file is still open
        pointsFile.clear(); // clear file flags
        pointsFile.seekg(0, std::ios::beg); // go back to beginning of file
        while(pointsFile.read((char*)&cp, colorPointSize)){ // while we can read a point..
            loadColorPoints.push_back(cp); // store the point in vector
        }
        pointsFile.close(); // we reached end of file, so close it
    }

    if (loadColorPoints.size() > 0) {
        this->colorpoints.clear();
        this->colorpoints = loadColorPoints; // copy vector
        this->recalculate();
        result = true;
    }
    return result;
}

Pallete::~Pallete(){

}


