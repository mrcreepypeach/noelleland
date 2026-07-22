#ifndef GAMESTATE
#define GAMESTATE

struct gameState{
    const bool DEBUG {false}; // Change if not debug

    float gameTime {0.0f};
    bool paused {false};
};

extern gameState game;

#endif