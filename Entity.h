#pragma once
#include "Surface.h"
#include "template.h"
#include "BoundingBox.h"

using namespace Tmpl8;

class Entity
{
public:
    enum class Type
    {
        ground,
        platform,
        portal,
        spike,
        coin
    };

    Type type;

    BoundingBox bndBox;
    
    Entity(Type type, int ID);

    virtual void Update();

    virtual void Render(Surface& screen);

    void setPos(vec2 pos);
    void setSize(vec2 size);

private:
    int ID{ 0 };

    vec2 pos{ };
    vec2 size{ };
};
