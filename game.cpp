#define NOMINMAX
#include "game.h"

// background values
constexpr int lastBgValue = -3840;
constexpr int loopBgValue = -1281;

namespace Tmpl8
{
    // use another class for all elements of game state
    
    enum class ButtonState
    {
        Released, // this is mouseUp
        Pressed,
        Held
    };

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

    void Game::Init()
    {
        // ! define these in a json file
        Entity* ground{ new Entity() };
        ground->setPos({ 0, 560 });
        ground->setSize({ 1024, 160 });
        entities.push_back(ground);
        Entity* stonePlatform1{ new Entity() };
        stonePlatform1->setPos({ 0, 147 });
        stonePlatform1->setSize({ 384, 32 });
        entities.push_back(stonePlatform1);
        Entity* stonePlatform2{ new Entity() };
        stonePlatform2->setPos({ 226, 415 });
        stonePlatform2->setSize({ 384, 32 });
        entities.push_back(stonePlatform2);
        Entity* portal{ new Entity() };
        portal->setPos({ 992, 528 });
        portal->setSize({ 32, 32 });
        entities.push_back(portal);
    }

    void Game::Shutdown() {}

    void Game::Tick(float)
    {
        Timer::Get().Tick();
        isPlaying = sCast<bool>(gameState);
        bool bgLoopCheck = bgX < lastBgValue;

        bgX -= sCast<int>(100 * Timer::Get().getElapsedS());
        if (bgLoopCheck)
        {
            bgX = loopBgValue;
        }

        // if (!isPlaying)
        if (gameState == GameState::Menu)
        {
            opacityBg.Draw(screen, bgX, bgY);
            menu.Render(screen);
            menu.Update(mouseAxis, isPlaying);
            if (isPlaying == true) gameState = GameState::Playing;
        }
        else
        {
            player.InitPlayer();
            bg.Draw(screen, bgX, bgY);
            // map.Render(*screen);
            m_map.Draw(screen, 0, 0);
            if (buttonState == ButtonState::Pressed)
            {
                
                player.DrawDirection(*screen, mouseAxis);
            }
            // if (mouseUp) player.mouseRelease(mouseAxis, Timer::Get().getElapsedS());
            player.Update(isPlaying, mouseAxis, sCast<float>(Timer::Get().getElapsedS()));
            player.Render(*screen);
            hud.Update(&player);
            if(readyTextChecker == true) readyTextTime += Timer::Get().getElapsedS();
            if (readyTextTime <= 3)
            {
                readyTextChecker = false;
                // screen->Print("READY", ScreenWidth / 2, ScreenHeight / 2, 0x0, 2);
                readyTextTime = 0;
            }
            if (player.getDeathCount() >= 10)
            {
                isPlaying = false;
                if(isPlaying == false) gameState = GameState::Menu;
            }
            for (auto& e : entities)
            {
                e->Update();
                e->Render(*screen);
                Collider::CheckCollisions(player, *e);
            }
            hud.Render(screen);
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

    bool Game::getState()
    {
        if (gameState == GameState::Menu) return false;
        else if (gameState == GameState::Playing) return true;
        else if (gameState == GameState::Paused) return false;
    }

    vec2 Game::getMouseAxis()
    {
        return mouseAxis;
    }
}