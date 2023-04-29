#include "Menu.h"

// logo values
constexpr short logoX = 240;
constexpr short logoY = 50;
constexpr short winImgX = 480;
constexpr short winImgY = 500;

// text values
constexpr short textSize = 5;

using namespace Tmpl8;

void Menu::Render(Surface* screen, HUD& hud)
{
    // Menu logo and button(s) display
    logo.Draw(screen, logoX, logoY);
    if (gameOver == true)
    {
        screen->Print("GAME OVER!", menuTextX - 25, menuTextY - 50, 0xFF0000, 2);
    }
    if (!finished) screen->Print("PLAY", menuTextX - 25, menuTextY - 25, textColor, textSize);
    else
    {
        // if the player has finished the game, this displays the win screen
        screen->Print("CONGRATS ON FINISHING THE GAME!", menuTextX - 225, menuTextY - 25, textColor, 3);
        screen->Print("COLLECTED COINS : ", menuTextX - 100, menuTextY + 10, textColor, 2);
        screen->Print(hud.getCoinString().c_str(), menuTextX + 110, menuTextY + 10, textColor, 2);
        winImage.Draw(screen, winImgX, winImgY);
    }
    screen->Print("EXIT", (ScreenWidth / 2) - 25, (ScreenHeight / 2) + 50, exitColor, textSize);
}

void Menu::Update(const vec2& mouseAxis, bool& finished, bool& gameOver)
{
    this->finished = finished;
    this->gameOver = gameOver;
    if(!finished)
        isHoveringPlay = mouseAxis.x > (menuTextX - 25)
                      && mouseAxis.x < (menuTextX - 25) + 115
                      && mouseAxis.y > (menuTextY - 25)
                      && mouseAxis.y < (menuTextY - 25) + 25;

    isHoveringExit = mouseAxis.x > (menuTextX - 25)
                  && mouseAxis.x < (menuTextX - 25) + 115
                  && mouseAxis.y > (menuTextY + 50)
                  && mouseAxis.y < (menuTextY + 50) + 25;

    if (isHoveringPlay)
    {
        // menuSound.play();
        textColor = 0xFFFFFF;
    }
    else
    {
        textColor = 0x0;
    }

    if (isHoveringExit)
    {
        // menuSound.play();
        exitColor = 0xFFFFFF;
    }
    else
    {
        exitColor = 0x0;
    }
}

void Menu::ButtonChecker(const vec2& mouseAxis, bool& playing)
{
    if (isHoveringPlay && !finished)
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
