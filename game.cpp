#define NOMINMAX
#include "game.h"
#include "surface.h"
#include "template.h"

constexpr float HalfW = (ScreenWidth / 2);
constexpr float HalfH = (ScreenHeight / 2);

constexpr Pixel WHITE = 0xFFFFFF;
constexpr Pixel RED = 0xFF0000;
constexpr Pixel GREEN = 0x00FF00;
constexpr Pixel BLUE = 0x0000FF;

constexpr float spriteSize = 25;
constexpr float entitySize = 32;

constexpr int32_t lastBgValue = -3840;
constexpr int32_t loopBgValue = -1281;

namespace Tmpl8
{
    void Game::Init() {}

    void Game::Shutdown() {}

    void Game::Tick(float deltaTime)
    {
        deltaTime /= 1000.f;
        deltaTime = std::min(deltaTime * 1.0f, 30.0f);
        Update();
    }

    void Game::Update()
    {
        bgX--;
        if (bgX < lastBgValue)
        {
            bgX = loopBgValue;
        }

        if (!isPlaying)
        {
            opacityBg.Draw(screen, bgX, bgY);
            hud.PrintMenu(screen, isPlaying, mouseAxis);
            if (isPlaying) player.InitPlayer();
        }
        else
        {
            bg.Draw(screen, bgX, bgY);
            map.Draw(screen);
            player.Draw(screen);
            player.Update(isPlaying);
            entity.Draw(screen);
            entity.Update();
            hud.PrintHUD(screen, &player);
        }
    }
}