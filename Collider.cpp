#include "Collider.h"

constexpr int coinHealHP = 10;

bool Collider::isColliding(const Sprite& sprite, int spriteX, int spriteY, const Sprite& entity, int entityX, int entityY)
{
    return false;
}

Collider::Collider()
{
}

Collider::~Collider()
{
}

void Collider::CollisionCheck()
{
    /*
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
        health += coinHealHP;
    }
    */
}
