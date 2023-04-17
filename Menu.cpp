#include "Menu.h"

// logo values
constexpr short logoX = 240;
constexpr short logoY = 50;

// text values
constexpr short textSize = 5;

using namespace Tmpl8;

void Menu::Render(Surface* screen)
{
    logo.Draw(screen, logoX, logoY);
    screen->Print("PLAY", menuTextX - 25, menuTextY - 25, textColor, textSize);
    screen->Print("EXIT", (ScreenWidth / 2) - 25, (ScreenHeight / 2) + 50, exitColor, textSize);
}

void Menu::Update(const vec2& mouseAxis)
{
    isHoveringPlay = mouseAxis.x > (menuTextX - 25)
        && mouseAxis.x < (menuTextX - 25) + 115
        && mouseAxis.y >(menuTextY - 25)
        && mouseAxis.y < (menuTextY - 25) + 25;
    isHoveringExit = mouseAxis.x > (menuTextX - 25)
        && mouseAxis.x < (menuTextX - 25) + 115
        && mouseAxis.y >(menuTextY + 50)
        && mouseAxis.y < (menuTextY + 50) + 25;

    if (isHoveringPlay)
    {
        textColor = 0xFFFFFF;
    }
    else textColor = 0x0;

    if (isHoveringExit)
    {
        exitColor = 0xFFFFFF;
    }
    else exitColor = 0x0;
}

void Menu::ButtonChecker(const vec2& mouseAxis, bool& playing)
{
    if (isHoveringPlay)
    {
        playing = true;
    }

    if (isHoveringExit)
    {
        SDL_Event e{};
        e.type = SDL_QUIT;
        SDL_PushEvent(&e);
    }
}
