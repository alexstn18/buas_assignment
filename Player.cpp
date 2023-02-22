#include "Player.h"
// health values
const int damage = 5;
const int maxHP = 100;
// sprite SET width
const int spriteSetWidth = 25;
// sprite SET starting point
const float startingPoint = 5.0f;

Player::Player()
{
    readyForLaunch = false; 
    bounceCount = NULL; 
}

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

void Player::CollisionCheck(Entity* entity)
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
        spriteY = sCast<float>(ScreenHeight - theSprite.GetHeight());
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
            spriteX = sCast<float>(ScreenWidth - theSprite.GetWidth()); //hit right
            speedX *= -0.8;
            bounceCount += 1;
            isBouncing = true, isFlipped = true;
        }
    }
    if (isColliding(sCast<int>(spriteX), sCast<int>(spriteY), 400, 300))
    {
        deathCount += 1;
        InitPlayer();
        //playAnim(anim);
        //anim = deathAnim;
    }
    if (isColliding(sCast<int>(spriteX), sCast<int>(spriteY), 25, 300))
    {
        speedY *= -0.99;
        bounceCount += 1;
        spriteH -= 10, isSquished = true;
    }
    if (isColliding(sCast<int>(spriteX), sCast<int>(spriteY), 600, 500))
    {
        // coinHitCount = 1;
        if (hasCollectedCoin == false) health += 5;
        hasCollectedCoin = true;
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

void Player::mouseCheck(const vec2& mouseAxis)
{
    bool initialFlipped;
    initialFlipped = isFlipped;
    if (isReleased == false)
    {
        if (mouseAxis.x < spriteX) isFlipped = true;
        else if (mouseAxis.x > spriteX) isFlipped = false;
    }
    else isFlipped = initialFlipped;
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
        }
    }
    if (health > maxHP) health = maxHP;
    // assert(health < maxHP && "health fucked up");
}

const int Player::getWidth()
{
    return theSprite.GetWidth();
}

const int Player::getHeight()
{
    return theSprite.GetHeight();
}

const int32_t Player::getHP()
{
    return health;
}

const int Player::getDeathCount()
{
    return deathCount;
}

const int Player::getX()
{
    return spriteX;
}

const int Player::getY()
{
    return spriteY;
}

bool Player::getCollected()
{
    return hasCollectedCoin;
}

void Player::DrawDirection(Surface* screen, const vec2 &mouseAxis)
{
    screen->Line(spriteX + (theSprite.GetWidth() / 2), spriteY + theSprite.GetHeight() - 3, mouseAxis.x, mouseAxis.y, 0xFFFFFF);
}

void Player::Draw(Surface* screen)
{
    theSprite.DrawScaled(sCast<int>(spriteX), sCast<int>(spriteY), spriteW, spriteH, isFlipped, screen);
}

void Player::Move(const vec2 &mouseAxis)
{
    //spriteX += speedX;
    //spriteY += speedY;
    // speedY++;
    isReleased = true;
    vec2 ballDirection;
    
    if (GetAsyncKeyState(VK_LBUTTON))
    {
        isReleased = false;
        if (!isReleased)
        {
            ballDirection = vec2(mouseAxis.x - spriteX, mouseAxis.y - spriteY).normalized();
            spriteX += (ballDirection.x * speedX) * 0.8f;
            spriteY += (ballDirection.y * -(speedY)) * 0.8f;
            readyForLaunch = true;
        }
    }
    else
    {
        isReleased = true;
    }
    if (readyForLaunch)
    {
        speedX += 1.2f;
        speedY -= 1.2f;
        readyForLaunch = false;
    }
    else
    {
        speedX = 2.0f;
        speedY = 3.0f;
    }
}

bool Player::isColliding(int spriteX, int spriteY, int entityX, int entityY)
{
    return ((spriteX + spriteW) > entityX && (spriteX - spriteW) < entityX) &&
           ((spriteY + spriteH) > entityY && (spriteY - spriteH) < entityY);
}

void Player::Update(bool &playing, Entity* entity, const vec2 &mAxis)
{
    hpCheck(playing);
    CollisionCheck(entity);
    SquishCheck();
    mouseCheck(mAxis);
    Move(mAxis);
}