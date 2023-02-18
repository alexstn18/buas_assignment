#include "Player.h"

const int damage = 5;
const int maxHP = 100;
const int spriteSetWidth = 25;
const float startingPoint = 5.0f;

Player::Player() { bounceCount = NULL; }

Player::~Player() {}

void Player::InitPlayer()
{
    health = maxHP;
    spriteX = startingPoint;
    spriteY = startingPoint;
    speedX = 2.0f;
    speedY = 3.0f;
    isFlipped = false;
}

void Player::ReInitPlayer() { }

void Player::CollisionCheck()
{
    hitTop = spriteY < NULL;
    hitBottom = spriteY > ScreenHeight - theSprite.GetHeight();
    hitSideL = spriteX < 0;
    hitSideR = spriteX > ScreenWidth - theSprite.GetWidth();
    hitSide = hitSideL || hitSideR;

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
        health += 10;
    }
}

void Player::SquishCheck()
{
    // isSquished = spriteH < 25 || spriteW < 25;
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
    /* MOUSE MOVEMENT
    bool isReleased = true;
    vec2 ballDirection = vec2(mouseAxis.x - ballCoord.x, mouseAxis.y - ballCoord.y).normalized();
    screen->Line(ballCoord.x + (ball.GetWidth() / 2), ballCoord.y + ball.GetHeight() - 1, mouseAxis.x, mouseAxis.y, 0xFFFFFF);
    ball.Draw(screen, ballCoord.x, ballCoord.y);
    if (GetAsyncKeyState(VK_LBUTTON))
    {
        isReleased = false;
        if (!isReleased)
        {
            ballCoord.x += (ballDirection.x * speed);
            ballCoord.y += (ballDirection.y * speed);
        }
    }
    else isReleased = true;
    */
}

bool Player::isColliding(const Sprite& sprite, int spriteX, int spriteY, const Sprite& entity, int entityX, int entityY)
{
    return ((spriteX + spriteW) > entityX && (spriteX - spriteW) < entityX) &&
           ((spriteY + spriteH) > entityY && (spriteY - spriteH) < entityY);
}

void Player::Update(bool &playing)
{
    hpCheck(playing);
    CollisionCheck();
    SquishCheck();
    Move();
}
