#define NOMINMAX
#include "game.h"

// color values
constexpr Pixel BLACK = 0x0;
constexpr Pixel WHITE = 0xFFFFFF;
constexpr Pixel RED = 0xFF0000;
constexpr Pixel GREEN = 0x00FF00;
constexpr Pixel BLUE = 0x0000FF;

// sprite values
constexpr float spriteSize = 25;
constexpr float entitySize = 32;

// background values
constexpr int lastBgValue = -3840;
constexpr int loopBgValue = -1281;

namespace Tmpl8
{
    enum ButtonState
    {
        Up,
        JustUp,
        Down,
        JustDown
    };

    ButtonState mouseKey;

    /* FROM THEMPERROR
    void Game::MouseDown(int key)
    {
      mouseKey = JustUp;
    };


    void Game::MouseDown(int key)
    {
      mouseKey = JustDown;
    };

    void Game::Tick(float dt)
    {
       if(mouseKey == JustUp)
       {
          mouseKey = Up;
       } 
       else if(mouseKey == JustDown)
       {
          mouseKey = Down;
       }

    //.. Game code;;
      if(mouseKey == JustDown) 
        //Logic that only needs to fire once on click

      if(mouseKey == JustDown || mouseKey == Down)
        //Logic that happens every frame we hold the button down
}
    */

    void Game::Init() {}

    void Game::Shutdown() {}

    void Game::Tick(float)
    {
        Timer::Get().Tick();
        bool bgLoopCheck = bgX < lastBgValue;

        bgX -= 100 * Timer::Get().getElapsedS();
        std::cout << player.getVel().x << " " << player.getVel().y << "\n";
        if (bgLoopCheck)
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
            // map.Draw(*screen);
            m_map.Draw(screen, 0, 0);
            if (mouseDown)
            {
                // player.resetBounceCount();
                player.DrawDirection(*screen, mouseAxis);
            }
                // if (mouseUp) player.mouseRelease(mouseAxis, Timer::Get().getElapsedS());
            player.Update(isPlaying, &entity, mouseAxis, Timer::Get().getElapsedS());
            player.Draw(*screen);
            if (player.getHP() <= 0) isPlaying = false;
            entity.Update();
            entity.Draw(*screen, player.getCollected());
            hud.PrintHUD(*screen, player, mouseAxis);
        }
    }

    void Game::MouseUp(int button)
    {
        if(isPlaying && player.getVel().sqrLentgh() < 0.001)
        {
            player.mouseRelease(mouseAxis);
        }   
        mouseDown = false;
    }

    void Game::MouseDown(int button)
    {
        // player.DrawDirection(*screen, mouseAxis);
        mouseDown = true;
    }

    vec2 Game::getMouseAxis()
    {
        return mouseAxis;
    }
}