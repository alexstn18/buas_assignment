#include "Player.h"

Player::Player()
{
    // bounceCount = 0;
}

Player::~Player()
{
}

void Player::InitPlayer()
{
	spriteX += speedX;
	spriteY += speedY;
	speedY++;
}

void Player::ReInitPlayer()
{
	spriteX = 5.0f;
	spriteY = 5.0f;
}

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
        if (spriteH >= 25)
        {
            spriteH = 25;
        }
        isSquished = false;
    }
}

void Player::hpCheck()
{
    if (isBouncing)
    {
        health -= 5;
        if (health <= NULL)
        {
            health = NULL;
            // isPlaying = false;
            // ReInitPlayer();
            return;
        }
    }

    if (health > 100) health = 100;
}

void Player::Draw(Surface* screen)
{
    theSprite.DrawScaled(static_cast<int>(spriteX), static_cast<int>(spriteY), spriteW, spriteH, isFlipped, screen);
}
