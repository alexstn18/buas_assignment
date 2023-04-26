#pragma once
#include "Surface.h"
#include "template.h"
#include "BoundingBox.h"
#include "SFX.h"

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

    BoundingBox bndBox;
    
    Entity::Entity(Type type, int ID, Sprite* sprite = nullptr) :
        type{ type }, ID{ ID }, sprite{ sprite } {}
    
    virtual void Update(float dt);

    virtual void Render(Surface& screen);

    Type type;

    int ID{ 0 };
    bool active{ true };

    bool getActive() const;

    virtual void collectCoin();

    void setPos(vec2 pos);
    void setSize(vec2 size);

    void playEntitySound(SFX& sfx);
protected:
    vec2 pos{ };
    vec2 size{ };
private:
    Sprite* sprite{ nullptr };
    
    int coinFrame{ 0 };
    
    float timePassed{ 0.0f };
    float timeIncrement{ 0.1f };
};
