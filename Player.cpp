#include "Player.h"

// health values
constexpr int damage = 5;
constexpr int maxHP = 100;

// sprite SET width
constexpr int spriteSetWidth = 25;

// sprite SET starting point
constexpr float startingPoint = 5.0f;

Player::Player()
{
    readyForLaunch = false; 
    bounceCount = NULL; 
}

Player::~Player() {}

void Player::InitPlayer()
{
    health = maxHP;
    pos.x = startingPoint;
    pos.y = startingPoint;
    speed.x = 2.0f;
    speed.y = 3.0f;
    isFlipped = false;
}

void Player::ReInitPlayer() { }

void Player::CollisionCheck(Entity* entity)
{
    hitTop = pos.y < NULL;
    hitBottom = pos.y > ScreenHeight - theSprite.GetHeight();
    hitSideL = pos.x < 0;
    hitSideR = pos.x > ScreenWidth - theSprite.GetWidth();
    hitSide = hitSideL || hitSideR;

    isBouncing = false;

    if (hitTop)
    {
        pos.y = NULL;
        speed.y *= -0.95;
    }

    if (hitBottom)
    { //hit bottom
        pos.y = sCast<float>(ScreenHeight - theSprite.GetHeight());
        speed.y *= -0.95;
        bounceCount += 1;
        spriteH -= 10, isSquished = true;
        isBouncing = true;
    }
    if (hitSide)
    { //hit side
        if (hitSideL) // left
        {
            pos.x = NULL;
            speed.x *= -0.8;
            bounceCount += 1;
            isBouncing = true, isFlipped = false;
        }
        else
        {
            pos.x = sCast<float>(ScreenWidth - theSprite.GetWidth()); //hit right
            speed.x *= -0.8;
            bounceCount += 1;
            isBouncing = true, isFlipped = true;
        }
    }
    if (isColliding(sCast<int>(pos.x), sCast<int>(pos.y), 400, 300))
    {
        deathCount += 1;
        InitPlayer();
        // isReleased = true;
        //playAnim(anim);
        //anim = deathAnim;
    }
    if (isColliding(sCast<int>(pos.x), sCast<int>(pos.y), 25, 300))
    {
        speed.y *= -0.99;
        bounceCount += 1;
        spriteH -= 10, isSquished = true;
    }
    if (isColliding(sCast<int>(pos.x), sCast<int>(pos.y), 600, 500))
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
        if (mouseAxis.x < pos.x) isFlipped = true;
        else if (mouseAxis.x > pos.x) isFlipped = false;
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

int Player::getWidth() const
{
    return theSprite.GetWidth();
}

int Player::getHeight() const
{
    return theSprite.GetHeight();
}

int Player::getHP() const
{
    return health;
}

int Player::getDeathCount() const
{
    return deathCount;
}

int Player::getX() const
{
    return sCast<int>(pos.x);
}

int Player::getY() const
{
    return sCast<int>(pos.y);
}

bool Player::getCollected() const
{
    return hasCollectedCoin;
}

void Player::DrawDirection(Surface& screen, const vec2 &mouseAxis)
{
    screen.Line(pos.x + (theSprite.GetWidth() / 2.0f), pos.y + theSprite.GetHeight() - 3.0f, mouseAxis.x, mouseAxis.y, 0xFFFFFF);
}

void Player::Draw(Surface& screen)
{
    theSprite.DrawScaled(sCast<int>(pos.x), sCast<int>(pos.y), spriteW, spriteH, isFlipped, &screen);
}

void Player::Move(const vec2 &mouseAxis, float dt)
{
    //pos.x += speedX;
    //pos.y += speedY;
    // speedY++;
    vec2 ballDirection;
    isReleased = true;
    
    if (GetAsyncKeyState(VK_LBUTTON))
    {
        isReleased = false;
        if (!isReleased)
        {
            ballDirection = vec2(mouseAxis.x - pos.x, mouseAxis.y - pos.y).normalized();
            pos.x += ((ballDirection.x * speed.x) * 0.8f) * dt;
            pos.y += ((ballDirection.y * -(speed.y)) * 0.8f) * dt;
            readyForLaunch = true;
        }
    }
    else
    {
        isReleased = true;
    }

    if (readyForLaunch)
    {
        speed.x = launchForce.x;
        speed.y = launchForce.y;
        readyForLaunch = false;
    }
    else
    {
        speed.x = 2.0f;
        speed.y = 3.0f;
    }
}

bool Player::isColliding(int spriteX, int spriteY, int entityX, int entityY)
{
    return ((spriteX + spriteW) > entityX && (spriteX - spriteW) < entityX) &&
           ((spriteY + spriteH) > entityY && (spriteY - spriteH) < entityY);
}

void Player::Update(bool &playing, Entity* entity, const vec2 &mAxis, float dt)
{
    hpCheck(playing);
    CollisionCheck(entity);
    SquishCheck();
    mouseCheck(mAxis);
    Move(mAxis, dt);
}