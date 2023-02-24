#define NOMINMAX
#include "game.h"
#include "surface.h"
#include "template.h"

// screen values

constexpr float HalfW = (ScreenWidth / 2);
constexpr float HalfH = (ScreenHeight / 2);

// color values

constexpr Pixel WHITE = 0xFFFFFF;
constexpr Pixel RED = 0xFF0000;
constexpr Pixel GREEN = 0x00FF00;
constexpr Pixel BLUE = 0x0000FF;

// sprite values

constexpr float spriteSize = 25;
constexpr float entitySize = 32;

// background values

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

    void Game::MouseUp(int button)
    {
        mouseDown = false;
    }

    void Game::MouseDown(int button)
    {
        mouseDown = true;
    }

    vec2 Game::getMouseAxis()
    {
        return mouseAxis;
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
            hud.PrintMenu(*screen, isPlaying, mouseAxis);
            if (isPlaying) player.InitPlayer();
        }
        else
        {
            bg.Draw(screen, bgX, bgY);
            // map.Draw(screen);
            m_map.Draw(screen, 0, 0);
            if (mouseDown) player.DrawDirection(*screen, mouseAxis);
            player.Draw(*screen);
            player.Update(isPlaying, &entity, mouseAxis);
            entity.Draw(*screen, player.getCollected());
            entity.Update();
            hud.PrintHUD(*screen, player, mouseAxis);
        }
    }
}