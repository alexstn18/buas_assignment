#define NOMINMAX
#include "game.h"
#include "surface.h"
#include "template.h"

constexpr Pixel WHITE = 0xFFFFFF;
constexpr Pixel RED = 0xFF0000;
constexpr Pixel GREEN = 0x00FF00;
constexpr Pixel BLUE = 0x0000FF;

constexpr float HalfW = (ScreenWidth / 2);
constexpr float HalfH = (ScreenHeight / 2);

constexpr float spriteSize = 25;
constexpr float entitySize = 32;

namespace Tmpl8
{
    void Game::Init()
    {
    }

    void Game::Shutdown() {}
    // Surface tiles("assets/rogueDBtiles.png");
    Sprite opacityBg(new Surface("assets/halfOpacityBackground.png"), 1);
    Sprite grass(new Surface("assets/grassSprite.png"), 1);
    Sprite spike(new Surface("assets/spikeTile.png"), 1);
    Sprite coin(new Surface("assets/coinSpriteTest.png"), 1);

    void Game::Tick(float deltaTime)
    {
        deltaTime /= 1000.f;
        deltaTime = std::min(deltaTime * 1.0f, 30.0f);
        Update();
    }

    void Game::Update()
    {
        bgX--;

        if (bgX < -3841)
        {
            bgX = 0;
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
            hud.PrintHUD(screen, &player);
            player.Draw(screen);
            player.Update(isPlaying);
        }

    }
}
