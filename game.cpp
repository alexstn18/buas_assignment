#define NOMINMAX
#include "game.h"

// background values
constexpr int lastBgValue = -3840;
constexpr int loopBgValue = -1281;

namespace Tmpl8
{
    enum class ButtonState // mouse button state machine
    {
        Released, // this is mouseUp
        Pressed,
        Held
    };

    ButtonState buttonState;
    
    void Game::Init()
    {
        level.Init(currentLevel); // initializes the level
        Audio::Device::setMasterVolume(0.4f); // sets the game's master volume to 40%
        sfx.portalSound.setVolume(0.5f); // 50% volume
        sfx.ambience.setVolume(0.3f); // 30% volume
    }
   
    void Game::Shutdown() {}

    void Game::Tick(float)
    {
        Timer::Get().Tick();
        float delta = sCast<float>(Timer::Get().getElapsedS()); // deltaTime
        bool bgLoopCheck = bgX < lastBgValue; // background loop checker
        
        bgX -= 100 * delta; // constantly move/animate the background
        if (bgLoopCheck)
        {
            // loops the background
            bgX = loopBgValue;
        }
        
        if (gameState == GameState::Menu)
        {
            // menu functionality, preceded by line 135 from game.cpp
            coinCount = 0; // useful after the player game overs (20 deaths)
            opacityBg.Draw(screen, sCast<int>(bgX), 0); // draw the half opacity background when in menu
            menu.Render(screen, hud); // render the menu buttons and logo (or finish screen if the game is finished)
            menu.Update(mouseAxis, hasFinishedGame, hasGameOvered);
            if (isPlaying == true)
            {
                // available after line 135, when the player clicks on the "PLAY" button
                gameState = GameState::Playing;
                player.InitPlayer(level.getSpawnPoint(currentLevel));
            }
        }
        else
        {
            // non-menu gameplay functionality
            hasGameOvered = false;
            sfx.ambience.play();
            bg.Draw(screen, sCast<int>(bgX), 0);
            CheckLevel();
            level.Render(currentLevel, screen);
            player.Update(isPlaying, mouseAxis, delta);
            for (auto& e : level.getEntities())
            {
                // gets all the level's entities, and updates, renders and checks collision with them and the player
                e.Update(delta);
                e.Render(*screen);
                Collider::CheckCollisions(player, e, sfx, coinCount);
            }
            player.HitWaterCheck(level.getSpawnPoint(currentLevel));
            if (buttonState == ButtonState::Pressed)
            {
                // if the mouse button is pressed, play the click sound and draw the trajectory direction from the player to the mouse
                if (!hasPlayedSound) sfx.clickSound.play();
                hasPlayedSound = true;
                player.DrawDirection(*screen, mouseAxis);
            }
            else
            {
                hasPlayedSound = false;
            }
            player.Render(*screen);
            
            hud.Update(&player, level, coinCount);
            if (player.getDeathCount() >= 25)
            {
                // game over check
                isPlaying = false;
                hasGameOvered = true;
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
                // if the player has hit the spike, play the death sound and initialize the player
                player.InitPlayer(level.getSpawnPoint(currentLevel));
                sfx.deathSound.play();
            }
            
            if (player.getWaterChecker() == true)
            {
                // if the player has hit water, initialize the player
                sfx.deathSound.play();
                player.InitPlayer(level.getSpawnPoint(currentLevel));
            }
            
            if (player.getHP() <= 0)
            {
                player.InitPlayer(level.getSpawnPoint(currentLevel));
                player.setDeathCount();
            }
            
            hud.Render(screen);
        }
    }

    void Game::CheckLevel()
    {
        // function individually checks for each level if the player has hit the portal
        // if player has hit portal, then change and initialize the next level
        // and initialize the player based on the current, now next level's spawnpoint
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
            // menu button functionality that is only available while the gameState is Menu
            menu.ButtonChecker(mouseAxis, isPlaying);
        }

        if (isPlaying && player.checkState(Player::State::Grounded))
        {
            // if the player is grounded, the player is now able to move after he presses and releases left mouse click
            player.setDirColor(0xFFFFFF);
            player.mouseRelease(mouseAxis);
        }
        else
        {
            player.setDirColor(0xFF0000);
        }
        // releases the mouse button
        hasPlayedSound = false;
        mouseDown = false;
        buttonState = ButtonState::Released;
    }
   
    void Game::MouseDown(int button)
    {
        if(!hasPlayedSound) sfx.clickSound.play();
        hasPlayedSound = true;
        mouseDown = true;
        buttonState = ButtonState::Pressed;
    }
}