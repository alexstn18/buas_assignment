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
    screen->Print(levelString.c_str(), ScreenWidth - 30, ScreenHeight - 30, WHITE, 3);
    screen->Print("COINS: ", ScreenWidth - 130, 0 + 5, WHITE, 3);
    screen->Print(coinString.c_str(), ScreenWidth - 20, 0 + 5, WHITE, 3);
}

void HUD::Update(Player* player, Level& level, int count)
{
    healthString = std::to_string(player->getHP());
    deathCountString = std::to_string(player->getDeathCount());
    levelString = std::to_string(level.getLevelID());
    coinString = std::to_string(count);
}