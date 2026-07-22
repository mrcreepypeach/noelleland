#ifndef NOELLE
#define NOELLE

#include "raylib.h"
#include "spriteAnimation.h"

#include <unordered_map>
#include <vector>

class noelle{
public:
    enum direction{
        left=0,
        right=1,
        up=2,
        down=3
    };

    enum class animations{
        jumpscare,
        walkLeft,
        walkRight,
        walkUp,
        walkDown
    };

    enum class sounds{
        nole,
        jumpscare
    };

    static constexpr float walkSpeed = 0.01f;
    static constexpr float movementWaitTimer = 1.0f;
    static constexpr float walkAnimSpeed = 0.20f;

    Vector2 position{0,0};
private:
    std::vector<Texture2D> noelleIdles{
      LoadTexture("res/noelle/spr_noelle_walk_left_lw/spr_noelle_walk_left_lw_0.png"), // left
      LoadTexture("res/noelle/spr_noelle_walk_right_lw/spr_noelle_walk_right_lw_0.png"), // right
      LoadTexture("res/noelle/spr_noelle_walk_up_lw/spr_noelle_walk_up_lw_0.png"), // up
      LoadTexture("res/noelle/spr_noelle_walk_down_lw/spr_noelle_walk_down_lw_0.png") // down  
    };
    
    std::vector<Texture2D> noelleWalkLeft{
        LoadTexture("res/noelle/spr_noelle_walk_left_lw/spr_noelle_walk_left_lw_0.png"),
        LoadTexture("res/noelle/spr_noelle_walk_left_lw/spr_noelle_walk_left_lw_1.png"),
        LoadTexture("res/noelle/spr_noelle_walk_left_lw/spr_noelle_walk_left_lw_2.png"),
        LoadTexture("res/noelle/spr_noelle_walk_left_lw/spr_noelle_walk_left_lw_3.png")
    };

    std::vector<Texture2D> noelleWalkRight{
        LoadTexture("res/noelle/spr_noelle_walk_right_lw/spr_noelle_walk_right_lw_0.png"),
        LoadTexture("res/noelle/spr_noelle_walk_right_lw/spr_noelle_walk_right_lw_1.png"),
        LoadTexture("res/noelle/spr_noelle_walk_right_lw/spr_noelle_walk_right_lw_2.png"),
        LoadTexture("res/noelle/spr_noelle_walk_right_lw/spr_noelle_walk_right_lw_3.png")
    };

    std::vector<Texture2D> noelleWalkUp{
        LoadTexture("res/noelle/spr_noelle_walk_up_lw/spr_noelle_walk_up_lw_0.png"),
        LoadTexture("res/noelle/spr_noelle_walk_up_lw/spr_noelle_walk_up_lw_1.png"),
        LoadTexture("res/noelle/spr_noelle_walk_up_lw/spr_noelle_walk_up_lw_2.png"),
        LoadTexture("res/noelle/spr_noelle_walk_up_lw/spr_noelle_walk_up_lw_3.png")
    };

    std::vector<Texture2D> noelleWalkDown{
        LoadTexture("res/noelle/spr_noelle_walk_down_lw/spr_noelle_walk_down_lw_0.png"),
        LoadTexture("res/noelle/spr_noelle_walk_down_lw/spr_noelle_walk_down_lw_1.png"),
        LoadTexture("res/noelle/spr_noelle_walk_down_lw/spr_noelle_walk_down_lw_2.png"),
        LoadTexture("res/noelle/spr_noelle_walk_down_lw/spr_noelle_walk_down_lw_3.png")
    };

    std::vector<Texture2D> noelleJumpscare{
        LoadTexture("res/noelle/spr_noelle_jumpscare/spr_noelle_jump_scare_0.png"),
        LoadTexture("res/noelle/spr_noelle_jumpscare/spr_noelle_jump_scare_1.png"),
        LoadTexture("res/noelle/spr_noelle_jumpscare/spr_noelle_jump_scare_2.png"),
        LoadTexture("res/noelle/spr_noelle_jumpscare/spr_noelle_jump_scare_3.png"),
        LoadTexture("res/noelle/spr_noelle_jumpscare/spr_noelle_jump_scare_4.png"),
        LoadTexture("res/noelle/spr_noelle_jumpscare/spr_noelle_jump_scare_5.png"),
        LoadTexture("res/noelle/spr_noelle_jumpscare/spr_noelle_jump_scare_6.png"),
        LoadTexture("res/noelle/spr_noelle_jumpscare/spr_noelle_jump_scare_7.png"),
        LoadTexture("res/noelle/spr_noelle_jumpscare/spr_noelle_jump_scare_8.png"),
        LoadTexture("res/noelle/spr_noelle_jumpscare/spr_noelle_jump_scare_9.png"),
        LoadTexture("res/noelle/spr_noelle_jumpscare/spr_noelle_jump_scare_10.png"),
        LoadTexture("res/noelle/spr_noelle_jumpscare/spr_noelle_jump_scare_11.png"),
        LoadTexture("res/noelle/spr_noelle_jumpscare/spr_noelle_jump_scare_12.png")
    };

    direction noelleDir {noelle::direction::left};
    bool moving {false};
    float movementTimer {0.0f};
    
    Texture2D mainSprite {noelleIdles[noelleDir]};

    animation currentAnimation;

    int currentFrame {0};
    float animationTimer {0.0f};
    bool animating {false};
    bool noMove {false};

    std::unordered_map<noelle::animations, animation> Animators{
        {noelle::animations::walkLeft, {&noelleWalkLeft, walkAnimSpeed, true, false}},
        {noelle::animations::walkRight, {&noelleWalkRight, walkAnimSpeed, true, false}},
        {noelle::animations::walkUp, {&noelleWalkUp, walkAnimSpeed, true, false}},
        {noelle::animations::walkDown, {&noelleWalkDown, walkAnimSpeed, true, false}},
        {noelle::animations::jumpscare, {&noelleJumpscare, 0.06f, false, true, 0.5f}}
    };

    std::unordered_map<noelle::sounds, Sound> NoelleSounds = {
        {noelle::sounds::nole, LoadSound("res/sounds/nole.wav")},
        {noelle::sounds::jumpscare, LoadSound("res/sounds/snd_noelle_scared.wav")}
    };

    float turnTimer {0};
    float walkTimer {0};

    float noelleJumpscareFrameTimer {0};
    float noelleWalkFrameTimer {0};

public:

    void changeDirection(direction setDir);
    direction getDirection() const;
    void triggerAnimation(noelle::animations ANIM);
    void move();
    void move(noelle::direction direc);
    void update();
    void draw() const;

    noelle();
    noelle(Vector2 pos);
    ~noelle();
};

#endif