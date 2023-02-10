#include "Collider.h"

constexpr int coinHealHP = 10;

bool Collider::isColliding(const Sprite& sprite, int spriteX, int spriteY, const Sprite& entity, int entityX, int entityY)
{
    return false;
}

Collider::Collider() { /*m_sprite1X = m_sprite1Y = NULL;*/ }

Collider::~Collider() {}

/*
    if (isColliding(sprite1, static_cast<int>(sprite1X), static_cast<int>(sprite1Y), sprite2, 400, 300))
    {
        // deathCount += 1;
        // ReInitPlayer(), InitPlayer();
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
