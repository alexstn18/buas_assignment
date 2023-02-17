#pragma once
#include "Surface.h"
#include "template.h"
using namespace Tmpl8;

class Entity
{
public:
    void Init();
    bool isUsed(Sprite* sprite);
    void Update();
    void Draw(Surface* screen);
private:
    Sprite grass{ new Surface("assets/grassSprite.png"), 1 };
    Sprite spike{ new Surface("assets/spikeTile.png"), 1 };
    Sprite coin{ new Surface("assets/coinSpriteTest.png"), 1 };
};