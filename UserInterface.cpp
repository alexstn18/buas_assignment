#include "UserInterface.h"

// used colors
constexpr Pixel BLACK = 0x0;
constexpr Pixel WHITE = 0xFFFFFF;

// logo values
constexpr short logoX = 240;
constexpr short logoY = 50;

// text values
constexpr short textSize = 5;

UserInterface::UserInterface() { color = WHITE; }

// !! remove playing and make the function return a true value
void UserInterface::PrintMenu(Surface& screen, bool &playing, const vec2 &mouseAxis)
{
    bool isPressingMouse1 = GetAsyncKeyState(VK_LBUTTON);
    bool isHoveringPlay = mouseAxis.x > (menuTextX - 25)
                          && mouseAxis.x < (menuTextX - 25) + 115
                          && mouseAxis.y >(menuTextY - 25)
                          && mouseAxis.y < (menuTextY - 25) + 25;
    bool isHoveringExit = mouseAxis.x > (menuTextX - 25) 
                          && mouseAxis.x < (menuTextX - 25) + 115
                          && mouseAxis.y >(menuTextY + 50)
                          && mouseAxis.y < (menuTextY + 50) + 25;

    logo.Draw(&screen, logoX, logoY);

    screen.Print("PLAY", menuTextX - 25, menuTextY - 25, textColor, textSize);
    if (isHoveringPlay)
    {
        textColor = WHITE;
        // PLEASE HELP
        if (isPressingMouse1)
        {
            Sleep(200);
            playing = true;
        }
    }
    else textColor = BLACK;

    screen.Print("EXIT", (ScreenWidth / 2) - 25, (ScreenHeight / 2) + 50, exitColor, textSize);
    if (isHoveringExit)
    {
        exitColor = WHITE;
        if (isPressingMouse1)
        {
            SDL_Event e{};
            e.type = SDL_QUIT;
            SDL_PushEvent(&e);
        }
    }
    else exitColor = BLACK;
}

void UserInterface::PrintHUD(Surface& screen, Player& player, const vec2& mouseAxis)
{
    healthString = std::to_string(player.getHP());
    deathCountString = std::to_string(player.getDeathCount());
    
    hpIcon.DrawScaled(0, 0, hpIcon.GetWidth() * 5, hpIcon.GetHeight() * 5, false, &screen);
    screen.Print(healthString.c_str(), 0 + 50, 0 + 10, WHITE, 5);
    deathIcon.DrawScaled(0, 50, deathIcon.GetWidth() * 5, deathIcon.GetHeight() * 5, false, &screen);
    screen.Print(deathCountString.c_str(), 0 + 50, 0 + 60, WHITE, 5);
}
