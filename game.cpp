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
        level.Init(currentLevel);
        Audio::Device::setMasterVolume(0.4f);
        sfx.portalSound.setVolume(0.5f);
        sfx.ambience.setVolume(0.3f);
    }
   
    void Game::Shutdown() {}

    void Game::Tick(float)
    {
        Timer::Get().Tick();
        float delta = sCast<float>(Timer::Get().getElapsedS());
        bool bgLoopCheck = bgX < lastBgValue;
        
        bgX -= sCast<int>(100 * delta);
        if (bgLoopCheck)
        {
            bgX = loopBgValue;
        }
        
        if (gameState == GameState::Menu)
        {
            coinCount = 0;
            opacityBg.Draw(screen, bgX, bgY);
            menu.Render(screen);
            menu.Update(mouseAxis, hasFinishedGame);
            if (isPlaying == true)
            {
                gameState = GameState::Playing;
                player.InitPlayer(level.getSpawnPoint(currentLevel));
            }
        }
        else
        {
            sfx.ambience.play();
            bg.Draw(screen, bgX, bgY);
            CheckLevel();
            level.Render(currentLevel, screen);
            for (auto& e : level.getEntities())
            {
                e.Update(delta);
                e.Render(*screen);
                Collider::CheckCollisions(player, e, sfx, coinCount);
            }
            player.Update(isPlaying, mouseAxis, delta);
            player.HitWaterCheck(level.getSpawnPoint(currentLevel));
            if (buttonState == ButtonState::Pressed)
            {
                sfx.clickSound.play();
                player.DrawDirection(*screen, mouseAxis);
            }
            player.Render(*screen);
            
            hud.Update(&player, level, coinCount);
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
                sfx.deathSound.play();
                player.InitPlayer(level.getSpawnPoint(currentLevel));
            }
            if (player.getWaterChecker() == true)
            {
                sfx.deathSound.play();
                player.InitPlayer(level.getSpawnPoint(currentLevel));
            }
            hud.Render(screen);
        }
    }

    void Game::CheckLevel()
    {
        if (currentLevel == Level::Stage::ONE && player.getPortalChecker() == true)
        {
            sfx.portalSound.play();
            currentLevel = Level::Stage::TWO;
            level.Init(currentLevel);
            player.InitPlayer(level.getSpawnPoint(currentLevel));
        }
        else if (currentLevel == Level::Stage::TWO && player.getPortalChecker() == true)
        {
            sfx.portalSound.play();
            currentLevel = Level::Stage::THREE;
            level.Init(currentLevel);
            player.InitPlayer(level.getSpawnPoint(currentLevel));
        }
        else if (currentLevel == Level::Stage::THREE && player.getPortalChecker() == true)
        {
            sfx.ambience.stop();
            sfx.winSound.play();
            gameState = GameState::Menu;
            isPlaying = false;
            hasFinishedGame = true;
        }
    }

    void Game::MouseUp(int button)
    {
        if (gameState == GameState::Menu)
        {
            menu.ButtonChecker(mouseAxis, isPlaying);
            
        }
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
        sfx.clickSound.play();
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