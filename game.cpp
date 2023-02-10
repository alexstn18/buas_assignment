#define NOMINMAX
#include "game.h"
#include "surface.h"
#include "template.h"

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



        // screen->Clear(0x699EFC);
        // std::cout << friction << "\n";
        if (!isPlaying)
        {
            
            
        }

        if (isPlaying)
        {
            
            // InitPlayer();

            spike.Draw(screen, 400, 300);
            grass.Draw(screen, 25, 300);
            coin.Draw(screen, 600, 500);
            // if (coinHitCount == 1) coin.~Sprite();
        }
    }
}

void Game::Run()
{
    bgX--;

    if (bgX < -3841)
    {
        bgX = 0;
    }

    if(!isPlaying)
    {
        opacityBg.Draw(screen, bgX, bgY);
        hud.PrintMenu(screen, isPlaying, mouseAxis);
    }
    else
    {
        hud.PrintHUD(screen, &player);
        bg.Draw(screen, bgX, bgY);
        player.Draw(screen);
        player.InitPlayer();
        player.Update(isPlaying);
    }
    
}
