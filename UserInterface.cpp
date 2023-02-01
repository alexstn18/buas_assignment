#include "UserInterface.h"

UserInterface::UserInterface()
{
	color = 0xFFFFFF;
	healthString = std::to_string(health);
	deathCountString = std::to_string(deathCount);
}

UserInterface::~UserInterface()
{
}

void UserInterface::PrintMenu(Surface* screen, bool &playing)
{
    logo.Draw(screen, 240, 50);
    screen->Print("PLAY", menuTextX - 25, menuTextY - 25, textColor, 5);
    if (mouseAxis.x > (menuTextX - 25) && mouseAxis.x < (menuTextX - 25) + 115 && mouseAxis.y >(menuTextY - 25) && mouseAxis.y < (menuTextY - 25) + 25)
    {
        textColor = WHITE;
        if (GetAsyncKeyState(VK_LBUTTON))
        {
            isPlaying = true;
        }
    }
    else
    {

        textColor = 0x000000;
    }
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

void UserInterface::PrintHUD()
{
    hpIcon.DrawScaled(0, 0, hpIcon.GetWidth() * 5, hpIcon.GetHeight() * 5, 0, screen);
    screen->Print(healthString.c_str(), NULL + 50, NULL + 10, WHITE, 5);
    deathIcon.DrawScaled(0, 50, deathIcon.GetWidth() * 5, deathIcon.GetHeight() * 5, 0, screen);
    screen->Print(deathCountString.c_str(), NULL + 50, NULL + 60, WHITE, 5);
}
