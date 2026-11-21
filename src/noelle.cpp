#include "noelle.h"
#include <raylib.h>

#include <iostream>

void noelle::changeDirection(noelle::direction setDir){
    if (noelleDir != setDir){
        noelleDir = setDir;
        mainSprite = noelleIdles[noelleDir];
    }
}

noelle::direction noelle::getDirection() const { return noelleDir; }

void noelle::triggerAnimation(noelle::animations ANIM){
    noelle::currentAnimation = Animators.at(ANIM);
    if (ANIM == noelle::animations::jumpscare){
        PlaySound(NoelleSounds[noelle::sounds::jumpscare]);
        moving = false;
    }
    currentFrame = 0;
    animationTimer = 0.0f;
    animating = true;
}

void noelle::move(){
    if (!moving){
        moving = true;

        // lerp their position over a distance

        switch (noelleDir){
            case noelle::direction::left: {
                triggerAnimation(noelle::animations::walkLeft);
                
                break;
            }
            case noelle::direction::right: {
                triggerAnimation(noelle::animations::walkRight);
                
                break;
            }
            case noelle::direction::up: {
                triggerAnimation(noelle::animations::walkUp);
                
                break;
            }
            case noelle::direction::down: {
                triggerAnimation(noelle::animations::walkDown);
                
                break;
            }
            default: {
                std::cout << "No direction given for movement, defaulting to left\n";
                triggerAnimation(noelle::animations::walkLeft);

                break;
            }
        }
    }
}

void noelle::move(noelle::direction direc){
    if (direc){noelleDir = direc;}
    noelle::move();
}

void noelle::update() {
    if (!moving && (GetTime() - movementTimer) >= movementWaitTimer && !noMove){

        if (GetRandomValue(1, 10) == 10){
            movementTimer = GetTime();
            move(static_cast<noelle::direction>(GetRandomValue(0,3)));
        }
    }
    else if (moving){
        
        if ((GetTime() - walkTimer) >= walkSpeed && !noMove){
            walkTimer = GetTime();

            switch(noelleDir){
                case noelle::direction::left: {this->position.x -= 1.0f; break;}
                case noelle::direction::right: {this->position.x += 1.0f; break;}
                case noelle::direction::up: {this->position.y -= 1.0f; break;}
                case noelle::direction::down: {this->position.y += 1.0f; break;}
                default: {this->position.x += 1.0f; break;}
            }
        }
    }

    if (animating){
        animationTimer += GetFrameTime();

        if (currentAnimation.special){ noMove = true; movementTimer = GetTime(); }

        if (animationTimer >= currentAnimation.frameTime){
            animationTimer -= currentAnimation.frameTime;
            currentFrame++;

            if (currentFrame >= currentAnimation.frames->size()){
                if (currentAnimation.looping){
                    currentFrame = 0;
                }
                else{
                    
                    currentFrame = currentAnimation.frames->size() - 1;
                    animating = false;
                    if (currentAnimation.special){
                        noMove = false;
                    }
                }
            }
        
        }
        mainSprite = (*currentAnimation.frames)[currentFrame];
    }
}

void noelle::draw() const {
    DrawTexturePro(
        mainSprite,
        {0, 0, static_cast<float>(mainSprite.width), static_cast<float>(mainSprite.height)},
        {position.x, position.y, mainSprite.width * 2.0f, mainSprite.height * 2.0f}, // scaling and positioning
        Vector2{mainSprite.width * 0.5f, mainSprite.height * 0.5f},
        0.0f,
        WHITE
    );
}

noelle::noelle(){
    this->position = Vector2{0,0};
}

noelle::noelle(Vector2 pos){

    if (pos.x >= 0 && pos.y >= 0){
        this->position = pos;
    }
    else{
        this->position = Vector2{0,0};
    }
        
}
noelle::~noelle(){
    for(Texture2D a : noelleIdles){UnloadTexture(a);}
    for(Texture2D a : noelleWalkLeft){UnloadTexture(a);}
    for(Texture2D a : noelleWalkRight){UnloadTexture(a);}
    for(Texture2D a : noelleWalkUp){UnloadTexture(a);}
    for(Texture2D a : noelleWalkDown){UnloadTexture(a);}
    for(Texture2D a : noelleJumpscare){UnloadTexture(a);}
    for(const auto& [name, sound] : NoelleSounds){ UnloadSound(sound); }
}