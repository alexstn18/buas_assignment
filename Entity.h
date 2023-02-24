#pragma once
#include "Surface.h"
#include "template.h"
using namespace Tmpl8;
class Entity
{
public:
    Entity();
    ~Entity();
    void Init();
    void Update();
    void Draw(Surface& screen, bool collected);
private:
    Surface grassSurface{ "assets/grassSprite.png" };
    Surface spikeSurface{ "assets/spikeTile.png" };
    Surface coinSurface{ "assets/coinSpriteTest.png" };

    Sprite grass{ &grassSurface, 1 };
    Sprite spike{ &spikeSurface, 1 };
    Sprite coin{ &coinSurface, 1 };
};
