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

    vec2 spikePos{ 400.0f, 300.0f };
    vec2 grassPos{ 25.0f, 300.0f };
    vec2 coinPos{ 600.0f, 500.0f };
};
