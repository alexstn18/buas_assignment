#define NOMINMAX
#include "game.h"

// background values
constexpr int lastBgValue = -3840;
constexpr int loopBgValue = -1281;

namespace Tmpl8
{
    // use another class for all elements of game state
    enum class GameState
    {
        Menu,
        Playing,
        Paused
    };
    
    enum class ButtonState
    {
        Released, // this is mouseUp
        Pressed,
        Held
    };

    GameState gameState;
    ButtonState buttonState;

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

        bgX -= sCast<int>(100 * Timer::Get().getElapsedS());
        // std::cout << player.getVel().x << " " << player.getVel().y << "\n";
        if (bgLoopCheck)
        {
            bgX = loopBgValue;
        }

        // if (!isPlaying)
        if(gameState == GameState::Menu)
        {
            opacityBg.Draw(screen, bgX, bgY);
            hud.PrintMenu(*screen, isPlaying, mouseAxis);
            if (gameState == GameState::Playing) player.InitPlayer();
        }
        else
        {
            bg.Draw(screen, bgX, bgY);
            // map.Render(*screen);
            m_map.Draw(screen, 0, 0);
            screen->Line(0, 178, 383, 178, 0xFFFFFF); // first line top
            screen->Line(0, 560, 1023, 560, 0xFFFFFF);
            screen->Line(226, 415, 609, 415, 0xFFFFFF); // box around thing
            screen->Line(226, 446, 609, 446, 0xFFFFFF); // box around thing
            screen->Line(226, 416, 226, 445, 0xFFFFFF); // box around thing
            screen->Line(609, 416, 609, 445, 0xFFFFFF); // grass line
            if (buttonState == ButtonState::Pressed)
            {
                player.DrawDirection(*screen, mouseAxis);
            }
            // if (mouseUp) player.mouseRelease(mouseAxis, Timer::Get().getElapsedS());
            player.Update(isPlaying, &entity, mouseAxis, sCast<float>(Timer::Get().getElapsedS()));
            player.Render(*screen);
            if(readyTextChecker == true) readyTextTime += Timer::Get().getElapsedS();
            if (readyTextTime <= 3)
            {
                readyTextChecker = false;
                screen->Print("READY", ScreenWidth / 2, ScreenHeight / 2, 0x0, 2);
                readyTextTime = 0;
            }
            if (player.getDeathCount() >= 10)
            {
                
                isPlaying = false;
                gameState = GameState::Menu;
            }
            entity.Update();
            entity.Render(*screen, player.getCollected());
            hud.PrintHUD(*screen, player, mouseAxis);
        }
    }

    void Game::MouseUp(int button)
    {
        if (isPlaying && player.getVel().sqrLentgh() < 0.001)
        {
            readyTextTime = 0;
            readyTextChecker = true;
            player.setDirColor(0xFFFFFF);
            player.mouseRelease(mouseAxis);
        }
        else
        {
            player.setDirColor(0xFF0000);
        }
        mouseDown = false;
        buttonState = ButtonState::Released;
    }
    
    void Game::MouseDown(int button)
    {
        // player.DrawDirection(*screen, mouseAxis);
        mouseDown = true;
        buttonState = ButtonState::Pressed;
    }

    vec2 Game::getMouseAxis()
    {
        return mouseAxis;
    }
}