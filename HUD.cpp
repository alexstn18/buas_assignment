#include "HUD.h"

// used colors
constexpr Pixel BLACK = 0x0;
constexpr Pixel WHITE = 0xFFFFFF;

using namespace Tmpl8;

void HUD::Render(Surface* screen)
{
    hpIcon.DrawScaled(0, 0, hpIcon.GetWidth() * 5, hpIcon.GetHeight() * 5, false, screen);
    screen->Print(healthString.c_str(), 0 + 50, 0 + 10, WHITE, 5);
    deathIcon.DrawScaled(0, 50, deathIcon.GetWidth() * 5, deathIcon.GetHeight() * 5, false, screen);
    screen->Print(deathCountString.c_str(), 0 + 50, 0 + 60, WHITE, 5);
}

void HUD::Update(Player* player)
{
    healthString = std::to_string(player->getHP());
    deathCountString = std::to_string(player->getDeathCount());
}
