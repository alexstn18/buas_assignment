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
    int spikeX{ }, spikeY{ };
    int coinHitCount = 0;
    int bgX = 0, bgY = 0;

    void Game::Init() {}

    void Game::Shutdown() {}
    // Surface tiles("assets/rogueDBtiles.png");
    Sprite bg(new Surface("assets/bgScroll.png"), 1);
    Sprite opacityBg(new Surface("assets/halfOpacityBackground.png"), 1);
    Sprite grass(new Surface("assets/grassSprite.png"), 1);
    Sprite spike(new Surface("assets/spikeTile.png"), 1);
    Sprite coin(new Surface("assets/coinSpriteTest.png"), 1);

    bool isColliding(const Sprite& sprite, int spriteX, int spriteY, const Sprite &entity, int entityX, int entityY)
    {
        return ((spriteX + spriteW) > entityX && (spriteX - spriteW) < entityX) &&
            ((spriteY + spriteH) > entityY && (spriteY - spriteH) < entityY);
    }

    void Game::Tick(float deltaTime)
    {
        
        deltaTime /= 1000.f;
        deltaTime = std::min(deltaTime * 1.0f, 30.0f);

        /* mouse trajectory line
        friction = (spriteY - mouseAxis.y) / 15;
        if (friction < NULL)
        {
            friction = -friction;
        }
        else if (friction == 0)
        {
            color = 0xFF0000;
        }
        */

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

        if (isPlaying)
        {
            bg.Draw(screen, bgX, bgY);
            // InitPlayer();

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
        }
    }
}