#pragma once
#include "Surface.h"
#include "template.h"
#include "BoundingBox.h"

using namespace Tmpl8;

class Entity
{
public:
    BoundingBox bndBox;
    
    void Init();
    virtual void Update();

    virtual void Render(Surface& screen);

    void setPos(vec2 pos);
    void setSize(vec2 size);
private:
    vec2 pos{ };
    vec2 size{ };
    
};
