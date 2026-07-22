#ifndef SPRITEANIMATION
#define SPRITEANIMATION

#include "raylib.h"
#include <vector>

struct animation{
    const std::vector<Texture2D>* frames;
    float frameTime;
    bool looping;
    bool special;
    float pauseTime = 0;
};

#endif