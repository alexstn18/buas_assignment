#define NOMINMAX
#include "game.h"

// background values
constexpr int lastBgValue = -3840;
constexpr int loopBgValue = -1281;

namespace Tmpl8
{
    enum class ButtonState
    {
        Released, // this is mouseUp
        Pressed,
        Held
    };

    ButtonState buttonState;
    
    void Game::Init()
    {
        coin.Init();
        level.Init(currentLevel);
    }
   
    void Game::Shutdown() {}

    void Game::Tick(float)
    {
        Timer::Get().Tick();
        bool bgLoopCheck = bgX < lastBgValue;

        bgX -= sCast<int>(100 * Timer::Get().getElapsedS());
        if (bgLoopCheck)
        {
            bgX = loopBgValue;
        }
        
        if (gameState == GameState::Menu)
        {
            opacityBg.Draw(screen, bgX, bgY);
            menu.Render(screen);
            menu.Update(mouseAxis);
            if (isPlaying == true)
            {
                gameState = GameState::Playing;
                player.InitPlayer(level.getSpawnPoint(currentLevel));
            }
        }
        else
        {
            CheckLevel();
            bg.Draw(screen, bgX, bgY);
            level.Render(currentLevel, screen);
            if (buttonState == ButtonState::Pressed)
            {
                player.DrawDirection(*screen, mouseAxis);
            }
            for (auto& e : level.getEntities())
            {
                e.Update();
                e.Render(*screen);
                Collider::CheckCollisions(player, e, coin);
            }
            player.Update(isPlaying, mouseAxis, sCast<float>(Timer::Get().getElapsedS()));
            player.Render(*screen);
            switch (currentLevel)
            {
            case Level::Stage::ONE:
                coin.Render(*screen, 215, 115);
                break;
            case Level::Stage::TWO:
                coin.Init();
                coin.Render(*screen, 672, 384);
                break;
            case Level::Stage::THREE:
                coin.Init();
                coin.Render(*screen, 672, 384);
                break;
            }
            coin.Update();
            
            hud.Update(&player, level, coin);
            if (player.getDeathCount() >= 16)
            {
                isPlaying = false;
                if (isPlaying == false)
                {
                    gameState = GameState::Menu;
                    currentLevel = Level::Stage::ONE;
                    level.Init(currentLevel);
                    player.resetDeathCount();
                }
                
            }
            if (player.getSpikeChecker() == true)
            {
                player.InitPlayer(level.getSpawnPoint(currentLevel));
            }
            if (player.getWaterChecker() == true)
            {
                player.InitPlayer(level.getSpawnPoint(currentLevel));
            }
            hud.Render(screen);
        }
    }

    void Game::CheckLevel()
    {
        if (currentLevel == Level::Stage::ONE && player.getPortalChecker() == true)
        {
            currentLevel = Level::Stage::TWO;
            level.Init(currentLevel);
            player.InitPlayer(level.getSpawnPoint(currentLevel));
        }
        else if (currentLevel == Level::Stage::TWO && player.getPortalChecker() == true)
        {
            currentLevel = Level::Stage::THREE;
            level.Init(currentLevel);
            player.InitPlayer(level.getSpawnPoint(currentLevel));
        }
        else if (currentLevel == Level::Stage::THREE && player.getPortalChecker() == true)
        {
            isPlaying = false;
            gameState = GameState::Menu;
            currentLevel = Level::Stage::ONE;
            player.InitPlayer(level.getSpawnPoint(currentLevel));
        }
    }

    void Game::MouseUp(int button)
    {
        if (gameState == GameState::Menu) menu.ButtonChecker(mouseAxis, isPlaying);
        if (isPlaying && player.checkState(Player::State::Grounded))
        {
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
    Level::Stage Game::getCurrentLevel()
    {
        return currentLevel;
    }
}