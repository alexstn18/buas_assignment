#include "Player.h"

// health values
constexpr int damage = 5;
constexpr int maxHP = 100;

// sprite SET width
constexpr int spriteSetWidth = 25;

// sprite SET starting point
constexpr float startingPoint = 5.0f;

// PLEASE make a state ((MACHINE)) enum thank you

void Player::InitPlayer()
{
    health = maxHP;
    pos = startingPoint;
    speed.x = 200.0f;
    speed.y = 300.0f;
    isFlipped = false;
}

void Player::Physics(float dt)
{
    velocity.y += gravity * dt;
    
    pos += velocity * dt;
}

void Player::CollisionCheck(Entity* entity, float dt)
{
    hitTop = pos.y < 0;
    hitBottom = pos.y > ScreenHeight - theSprite.GetHeight();
    hitSideL = pos.x < 0;
    hitSideR = pos.x > ScreenWidth - theSprite.GetWidth();
    hitSide = hitSideL || hitSideR;

    isBouncing = false;

    if (hitTop)
    {
        pos.y = 0;
        speed.y *= 9.5f * dt;
    }

    if (hitBottom)
    { //hit bottom
        pos.y = sCast<float>(ScreenHeight - theSprite.GetHeight());
        // velocity.y = -launchForce.y;
        velocity.x *= 0.98f;
        spriteH -= 250 * dt;
        isSquished = true;
        isBouncing = true;

        switch (bounceCount)
        {
        case 0:
            velocity.y = -velocity.y / 1.5f;
            break;
        case 1:
            velocity.y = -velocity.y / 2.0f;
            break;
        case 2:
            velocity.y = -velocity.y / 2.5f;
            break;
        default:
            velocity.y = 0;
            // velocity.x = 0;
            break;
        }
        bounceCount += 1;
    }
    if (hitSide)
    { //hit side
        if (hitSideL) // left
        {
            pos.x = 0;
            speed.x *= -8.0f * dt;
            // bounceCount += 1;
            isBouncing = true, isFlipped = false;
        }
        else
        {
            pos.x = sCast<float>(ScreenWidth - theSprite.GetWidth()); //hit right
            speed.x *= -8.0f * dt;
            // bounceCount += 1;
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
        speed.y *= -0.99f * dt;
        // bounceCount += 1;
        spriteH -= 100 * dt, isSquished = true;
    }
    if (isColliding(sCast<int>(pos.x), sCast<int>(pos.y), 600, 500))
    {
        // coinHitCount = 1;
        if (hasCollectedCoin == false) health += 5;
        hasCollectedCoin = true;
    }
}

void Player::SquishCheck(float dt)
{
    // isSquished = spriteH < 25 || spriteW < 25;
    if (isSquished)
    {
        spriteH += sCast<int>(500.0f * dt);
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

/*
void Player::hpCheck(bool &isPlaying)
{
    if (isBouncing)
    {
        // health -= damage;
        if (health <= 0)
        {
            health = 0;
            isPlaying = false;
        }
    }
    if (health > maxHP) health = maxHP;
    // assert(health < maxHP && "health fucked up");
}
*/

void Player::mouseRelease(const vec2& mouseAxis)
{
    vec2 ballDirection;

    ballDirection = vec2(mouseAxis.x - pos.x, mouseAxis.y - pos.y).normalized();
    velocity = ballDirection * launchImpulse;
    
    bounceCount = 0;
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

int Player::getBounceCount() const
{
    return bounceCount;
}

int Player::getDeathCount() const
{
    return deathCount;
}

vec2 Player::getPos() const
{
    return pos;
}

vec2 Player::getVel() const
{
    return velocity;
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
    //debugging collision box for player
    screen.Box(sCast<int>(pos.x), sCast<int>(pos.y), sCast<int>(pos.x) + theSprite.GetWidth(), sCast<int>(pos.y) + theSprite.GetHeight(), 0xFFFFFF);
}

void Player::resetBounceCount()
{
    bounceCount = 0;
}

bool Player::isColliding(int spriteX, int spriteY, int entityX, int entityY)
{
    return ((spriteX + spriteW) > entityX && (spriteX - spriteW) < entityX) &&
           ((spriteY + spriteH) > entityY && (spriteY - spriteH) < entityY);
}

void Player::Update(bool &playing, Entity* entity, const vec2 &mAxis, float dt)
{
    Physics(dt);
    // hpCheck(playing);
    CollisionCheck(entity, dt);
    SquishCheck(dt);
    mouseCheck(mAxis);
}