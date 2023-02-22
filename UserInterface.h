#pragma once
#include "surface.h"
#include "template.h"
#include "Player.h"
#include "Windows.h"
#include <SDL.h>
#include <string>

namespace Tmpl8
{
    class UserInterface
    {
    public:
        UserInterface();
        
        ~UserInterface();

        void PrintMenu(Surface& screen, bool& playing, const vec2& mouseAxis);

        void PrintHUD(Surface& screen, Player& player, const vec2& mouseAxis);
    private:
        uint32_t color;
        uint32_t textColor{ 0x0 };
        uint32_t exitColor{ 0x0 };
        uint16_t menuTextX{ ScreenWidth / 2 };
        uint16_t menuTextY{ ScreenHeight / 2 };
        std::string healthString;
        std::string deathCountString;

        Sprite hpIcon{ new Surface("assets/heart_shaded.png"), 1 };
        Sprite deathIcon{ new Surface("assets/skullSprite.png"), 1 };
        Sprite logo{ new Surface("assets/logo.png"), 1 };
    };


}