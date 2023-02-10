#include "Player.h"

const int damage = 5;
const int maxHP = 100;
const int spriteSetWidth = 25;
const float startingPoint = 5.0f;

Player::Player() { bounceCount = NULL; }

Player::~Player() {}

void Player::InitPlayer()
{
	spriteX += speedX;
	spriteY += speedY;
	speedY++;
}

void Player::ReInitPlayer() { spriteX = spriteY = startingPoint; }

void Player::CollisionCheck()
{
    if (spriteY < NULL)
    {
        spriteY = NULL;
        speedY *= -0.95;
    }

    if (spriteY > ScreenHeight - theSprite.GetHeight())
    { //hit bottom
        spriteY = ScreenHeight - theSprite.GetHeight();
        speedY *= -0.95;
        bounceCount += 1;
        spriteH -= 10, isSquished = true;
        isBouncing = true;
    }
    if (spriteX > ScreenHeight - theSprite.GetWidth() || spriteX < 0)
    { //hit side
        if (spriteX < NULL) // left
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
        if (spriteH >= spriteSetWidth) spriteH = spriteSetWidth;
        isSquished = false;
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

    if (health > maxHP) health = maxHP;
}

const int Player::getHP()
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

void Player::Update(bool &playing)
{
    CollisionCheck();
    SquishCheck();
    hpCheck(playing);
}
