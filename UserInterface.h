#pragma once
#include "surface.h"
#include "template.h"
#include "Player.h"
#include "game.h"
#include <string>

using namespace Tmpl8;

class UserInterface
{
public:
    UserInterface(Player &player);

    ~UserInterface();

    void PrintMenu(Surface* screen, bool &playing);

    void PrintHUD(Surface* screen);
private:
    uint32_t color;
    uint32_t textColor{ 0x0 };
    uint32_t exitColor{ 0x0 };
    uint16_t menuTextX{ ScreenWidth / 2 };
    uint16_t menuTextY{ ScreenHeight / 2 };
    std::string healthString;
    std::string deathCountString;
    Player &m_player;

    Sprite hpIcon{ new Surface("assets/heart_shaded.png"), 1 };
    Sprite deathIcon{ new Surface("assets/skullSprite.png"), 1 };
    Sprite logo{ new Surface("assets/logo.png"), 1 };
};

