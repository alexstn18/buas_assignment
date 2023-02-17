#include "Player.h"

const int damage = 25;
const int maxHP = 100;
const int spriteSetWidth = 25;
const float startingPoint = 5.0f;

Player::Player() { bounceCount = NULL; }

Player::~Player() {}

void Player::InitPlayer()
{
    health = maxHP;
    spriteX = ScreenWidth - theSprite.GetWidth() - theSprite.GetWidth();
    spriteY = startingPoint;
    speedX = 2.0f;
    speedY = 3.0f;
}

void Player::ReInitPlayer() { }

void Player::CollisionCheck()
{
    isBouncing = false;
    if (hitTop)
    {
        spriteY = NULL;
        speedY *= -0.95;
    }

    if (hitBottom)
    { //hit bottom
        spriteY = ScreenHeight - theSprite.GetHeight();
        speedY *= -0.95;
        bounceCount += 1;
        spriteH -= 10, isSquished = true;
        isBouncing = true;
    }
    if (hitSide)
    { //hit side
        if (hitSideL) // left
        {
            spriteX = NULL;
            speedX *= -0.8;
            bounceCount += 1;
            isBouncing = true, isFlipped = false;
        }
        else
        {
            spriteX = ScreenWidth - theSprite.GetWidth(); //hit right
            speedX *= -0.8;
            bounceCount += 1;
            isBouncing = true, isFlipped = true;
        }
    }
}

void Player::SquishCheck()
{
    if (isSquished)
    {
        spriteH++;
        if (spriteH >= spriteSetWidth)
        {
            spriteH = spriteSetWidth;
            isSquished = false;
        }
        
    }
}

void Player::hpCheck(bool &isPlaying)
{
    if (isBouncing)
    {
        health -= damage;
        if (health <= NULL)
        {
            health = NULL;
            isPlaying = false;
            // ReInitPlayer();
            // return;
        }
    }
    // assert(health < maxHP && "health fucked up");
}

const int32_t Player::getHP()
{
    return health;
}

const int Player::getDeathCount()
{
    return deathCount;
}

void Player::Draw(Surface* screen)
{
    theSprite.DrawScaled(static_cast<int>(spriteX), static_cast<int>(spriteY), spriteW, spriteH, isFlipped, screen);
}

void Player::Move()
{
    spriteX += speedX;
    spriteY += speedY;
    speedY++;
}

void Player::Update(bool &playing)
{
    Move();
    CollisionCheck();
    SquishCheck();
    hpCheck(playing);
}
