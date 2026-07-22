#ifndef SELECTIONBOX
#define SELECTIONBOX

#include <string>

#include "raylib.h"
#include "raymath.h"

#include "settings.h"

class selectionBox{
public:
    
    Rectangle box;
    Vector2 boxPosition {0,0};
    bool selected = false;

private:

    std::string ActualSetting;
    const float fontSize {20};
    Vector2 boxTextPosition {0,0};
    Vector2 settingTextPosition{0,0};
    std::string boxText {"Setting"};
    std::string settingText {"value to set"};

public:

    selectionBox(Vector2 pos, std::string setText, std::variant<bool, double> set, Font font){
        int totalSize;
        
        // setting stuff

        boxText = setText;
        // settingText = std::to_string(); // Set this to display the current setting

        Vector2 boxTextSize = MeasureTextEx(font, boxText.c_str(), fontSize, 1);
        Vector2 settingTextSize = MeasureTextEx(font, settingText.c_str(), fontSize, 1);
        
        // calculate where the center would be
        Vector2 finalPos = boxTextSize + settingTextSize;


        // set the ultimate position

        boxPosition = finalPos;

        // placing other stuff relative to box position

        boxTextPosition.x = boxPosition.x + 25;
        boxTextPosition.y = boxPosition.y;

        settingTextPosition.x = boxTextPosition.x + 25;
        settingTextPosition.y = boxTextPosition.y;



    }

    void changeSetting(){

    }

    void draw(Font font){
        Color a = WHITE;
        // Iterate through settings, find type of setting

        for (const auto& [key, value] : settings){
            
        }
        /*
        if (setting){
            a = GREEN;
        }
        else{
            a = RED;
        }
        */
        DrawRectangle(boxPosition.x, boxPosition.y, 10, 10, WHITE); // debug box
        DrawTextEx(font, boxText.c_str(), boxTextPosition, 20, 1, WHITE); // Option text draw
        DrawTextEx(font, settingText.c_str(), settingTextPosition, 20, 1, a); // Setting text draw
    

    }
};

#endif