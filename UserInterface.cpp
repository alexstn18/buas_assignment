#include "UserInterface.h"

constexpr Pixel BLACK = 0x0;
constexpr Pixel WHITE = 0xFFFFFF;
constexpr short logoX = 240;
constexpr short logoY = 50;

UserInterface::UserInterface() { color = WHITE; }

UserInterface::~UserInterface() {}

void UserInterface::PrintMenu(Surface* screen, bool &playing, const vec2 &mouseAxis)
{
    logo.Draw(screen, logoX, logoY);
    screen->Print("PLAY", menuTextX - 25, menuTextY - 25, textColor, 5);
    if (mouseAxis.x > (menuTextX - 25) && mouseAxis.x < (menuTextX - 25) + 115 && mouseAxis.y >(menuTextY - 25) && mouseAxis.y < (menuTextY - 25) + 25)
    {
        textColor = WHITE;
        if (GetAsyncKeyState(VK_LBUTTON)) playing = true;
    }
    else textColor = BLACK;

    screen->Print("EXIT", (ScreenWidth / 2) - 25, (ScreenHeight / 2) + 50, exitColor, 5);
    if (mouseAxis.x > (menuTextX - 25) && mouseAxis.x < (menuTextX - 25) + 115 && mouseAxis.y >(menuTextY + 50) && mouseAxis.y < (menuTextY + 50) + 25)
    {
        exitColor = WHITE;
        if (GetAsyncKeyState(VK_LBUTTON))
        {
            SDL_Event e;
            e.type = SDL_QUIT;
            SDL_PushEvent(&e);
        }
    }
}

void UserInterface::PrintHUD(Surface* screen, Player* player)
{
    healthString = std::to_string(player->getHP());
    deathCountString = std::to_string(player->getDeathCount());
    hpIcon.DrawScaled(NULL, NULL, hpIcon.GetWidth() * 5, hpIcon.GetHeight() * 5, 0, screen);
    screen->Print(healthString.c_str(), NULL + 50, NULL + 10, WHITE, 5);
    deathIcon.DrawScaled(0, 50, deathIcon.GetWidth() * 5, deathIcon.GetHeight() * 5, 0, screen);
    screen->Print(deathCountString.c_str(), NULL + 50, NULL + 60, WHITE, 5);
}
