#define NOMINMAX
#include "game.h"
#include "surface.h"
#include "template.h"
#include <SDL.h>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>

#define WHITE 0xFFFFFF
#define RED 0xFF0000
#define GREEN 0x00FF00
#define BLUE 0x0000FF

using namespace std;

#define HalfW (ScreenWidth / 2)
#define HalfH (ScreenHeight / 2)

#define spriteSize 25
#define entitySize 32
namespace Tmpl8
{
    int bounceCount;
    uint32_t color;
    uint32_t textColor = 0x000000;
    uint32_t exitColor = 0x000000;
    uint16_t deathCount = 0;
    int16_t health = 100;
    std::string healthString;
    std::string deathCountString;
    float spriteX { 5.0f }, spriteY { 5.0f }, friction { 0.0f }, speedX { 2.0f }, speedY { 3.0f };
    int spikeX{ }, spikeY{ };
    int coinHitCount = 0;
    int bgX = 0, bgY = 0;
    bool isPlaying = false, isBouncing = false, isFlipped = false;

    void InitPlayer()
    {
        spriteX += speedX;
        spriteY += speedY;
        speedY++;
    }

    void ReInitPlayer() { spriteX = 5.0f, spriteY = 5.0f; }

    void Game::Init() {}

    void Game::Shutdown() {}
    // Surface tiles("assets/rogueDBtiles.png");
    Sprite bg(new Surface("assets/bgScroll.png"), 1);
    Sprite opacityBg(new Surface("assets/halfOpacityBackground.png"), 1);
    Sprite theSprite(new Surface("assets/ball.png"), 1);
    Sprite grass(new Surface("assets/grassSprite.png"), 1);
    Sprite spike(new Surface("assets/spikeTile.png"), 1);
    Sprite coin(new Surface("assets/coinSpriteTest.png"), 1);
    int spriteW = theSprite.GetWidth();
    int spriteH = theSprite.GetHeight();
    Sprite hpIcon(new Surface("assets/heart_shaded.png"), 1);
    Sprite deathIcon(new Surface("assets/skullSprite.png"), 1);
    Sprite logo(new Surface("assets/logo.png"), 1);

    bool isColliding(const Sprite& sprite, int spriteX, int spriteY, const Sprite &entity, int entityX, int entityY)
    {
        return ((spriteX + spriteW) > entityX && (spriteX - spriteW) < entityX) &&
            ((spriteY + spriteH) > entityY && (spriteY - spriteH) < entityY);
    }

    void Game::Tick(float deltaTime)
    {
        color = 0xFFFFFF;
        deltaTime /= 1000.f;
        deltaTime = std::min(deltaTime * 1.0f, 30.0f);

        bool isSquished = spriteH < 25 || spriteW < 25;

        healthString = std::to_string(health);
        deathCountString = std::to_string(deathCount);

        friction = (spriteY - mouseAxis.y) / 15;
        if (friction < NULL)
        {
            friction = -friction;
        }
        else if (friction == 0)
        {
            color = 0xFF0000;
        }

        bgX--;

        if (bgX < -3841)
        {
            bgX = 0;
        }

        // screen->Clear(0x699EFC);
        // std::cout << friction << "\n";
        if (!isPlaying)
        {
            opacityBg.Draw(screen, bgX, bgY);
            uint16_t menuTextX = ScreenWidth / 2, menuTextY = ScreenHeight / 2;
            logo.Draw(screen, 240, 50);
            screen->Print("PLAY", menuTextX - 25, menuTextY - 25, textColor, 5);
            if (mouseAxis.x > (menuTextX - 25) && mouseAxis.x < (menuTextX - 25) + 115 && mouseAxis.y > (menuTextY - 25) && mouseAxis.y < (menuTextY - 25) + 25)
            {
                textColor = WHITE;
                if (GetAsyncKeyState(VK_LBUTTON))
                {
                    isPlaying = true;
                }
            }
            else
            {
                textColor = 0x000000;
            }
            screen->Print("EXIT", (ScreenWidth / 2) - 25, (ScreenHeight / 2) + 50, exitColor, 5);
            if (mouseAxis.x > (menuTextX - 25) && mouseAxis.x < (menuTextX - 25) + 115 && mouseAxis.y >(menuTextY + 50) && mouseAxis.y < (menuTextY + 50) + 25)
            {
                exitColor = WHITE;
                if (GetAsyncKeyState(VK_LBUTTON))
                {
                    SDL_Event e;
                    e.type = SDL_QUIT;
                    SDL_PushEvent(&e);
                }
            }
        }

        if(isPlaying)
        {
            bg.Draw(screen, bgX, bgY);
            InitPlayer();
            if (spriteY < NULL)
            {
                spriteY = NULL;
                speedY *= -0.95;
            }

            if (spriteY > screen->GetHeight() - theSprite.GetHeight())
            { //hit bottom
                spriteY = screen->GetHeight() - theSprite.GetHeight();
                speedY *= -0.95;
                bounceCount += 1;
                spriteH -= 10, isSquished = true;
                isBouncing = true;
            }
            if (spriteX > screen->GetWidth() - theSprite.GetWidth() || spriteX < 0)
            { //hit side
                if (spriteX < NULL) // left
                {
                    spriteX = NULL;
                    speedX *= -0.8;
                    bounceCount += 1;
                    isBouncing = true, isFlipped = false;
                }
                else
                {
                    spriteX = screen->GetWidth() - theSprite.GetWidth(); //hit right
                    speedX *= -0.8;
                    bounceCount += 1;
                    isBouncing = true, isFlipped = true;
                }  
            }

            if (isSquished)
            {
                spriteH++;
                if (spriteH >= 25)
                {
                    spriteH = 25;
                }
                isSquished = false;
            }

            if (isBouncing)
            {
                health -= 5;
                if (health <= NULL)
                {
                    health = NULL;
                    isPlaying = false;
                    // ReInitPlayer();
                    return;

                }
                isBouncing = false;
            }

            if (health > 100) health = 100;
            

            theSprite.DrawScaled(static_cast<int>(spriteX), static_cast<int>(spriteY), spriteW, spriteH, isFlipped, screen);
            spike.Draw(screen, 400, 300);
            grass.Draw(screen, 25, 300);
            coin.Draw(screen, 600, 500);
            if (isColliding(theSprite, static_cast<int>(spriteX), static_cast<int>(spriteY), spike, 400, 300))
            {
                deathCount += 1;
                ReInitPlayer(), InitPlayer();
                //anim = deathAnim;
                //playAnim(anim);
            }
            if (isColliding(theSprite, static_cast<int>(spriteX), static_cast<int>(spriteY), grass, 25, 300))
            {
                speedY *= -0.99;
                bounceCount += 1;
                spriteH -= 10, isSquished = true;
            }
            if (isColliding(theSprite, static_cast<int>(spriteX), static_cast<int>(spriteY), coin, 600, 500))
            {
                coinHitCount = 1;
                health += 10;
            }

            // if (coinHitCount == 1) coin.~Sprite();

            hpIcon.DrawScaled(0, 0, hpIcon.GetWidth() * 5, hpIcon.GetHeight() * 5, 0, screen);
            screen->Print(healthString.c_str(), NULL + 50, NULL + 10, WHITE, 5);
            deathIcon.DrawScaled(0, 50, deathIcon.GetWidth() * 5, deathIcon.GetHeight() * 5, 0, screen);
            screen->Print(deathCountString.c_str(), NULL + 50, NULL + 60, WHITE, 5);
        }
    }
}