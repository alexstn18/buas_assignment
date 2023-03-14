#include "Player.h"

// health values
constexpr int damage = 5;
constexpr int maxHP = 100;

// sprite SET width
constexpr int spriteSetWidth = 25;

// sprite SET starting point
constexpr float startingPoint = 0.0f;

void Player::InitPlayer()
{
    state = State::Stopped;
    health = maxHP;
    pos.x = 0 + theSprite.GetWidth();
    pos.y = ScreenHeight - theSprite.GetHeight();
    speed.x = 200.0f;
    speed.y = 300.0f;
    isFlipped = false;
    // do a flow chart of 
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
        velocity.y = velocity.y / 1.75f;
    }

    if (hitBottom)
    { //hit bottom
        isSquished = true;
        pos.y = sCast<float>(ScreenHeight - theSprite.GetHeight());
        // velocity.y = -launchForce.y;
        velocity.x *= 0.98f;
        spriteSize.y -= 250 * dt;
        isBouncing = true; state = bouncing;

        switch (bounceCount)
        {
        case 0:
            velocity.y = -velocity.y / 1.5f;
            break;
        case 1:
            velocity.y = -velocity.y / 1.75f;
            break;
        case 2:
            velocity.y = -velocity.y / 2.0f;
            break;
        default:
            velocity.y = 0;
            state = stopped;
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
            velocity.x = velocity.x / 1.5f;
            // bounceCount += 1;
            isBouncing = true, isFlipped = false;
        }
        else
        {
            pos.x = sCast<float>(ScreenWidth - theSprite.GetWidth()); //hit right
            velocity.x = -velocity.x / 1.5f;
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
        velocity.y = -velocity.y / 1.25f;
        // bounceCount += 1;
        spriteSize.y -= 100 * dt, isSquished = true;
    }
    if (isColliding(sCast<int>(pos.x), sCast<int>(pos.y), 600, 500))
    {
        // coinHitCount = 1;
        if (hasCollectedCoin == false) health += 5;
        hasCollectedCoin = true;
    }
}

void Player::startState(State newState)
{
    switch (newState)
    {
    case State::Stopped:
        break;
    case State::Bouncing:
        break;
    }
}

void Player::endState(State oldState)
{
    switch (oldState)
    {
    case State::Stopped:
        break;
    case State::Bouncing:
        break;
    }
}

void Player::SquishCheck(float dt)
{
    // isSquished = spriteH < 25 || spriteW < 25;
    if (isSquished)
    {
        spriteSize.y = 5000.0f * dt;
        // spriteH += sCast<int>(500.0f * dt);
        if (spriteSize.y >= spriteSetWidth)
        {
            spriteSize.y = spriteSetWidth;
            isSquished = false;
        }
    }
}

void Player::mouseCheck(const vec2& mouseAxis)
{
    initialFlipped = isFlipped;
    if (isReleased == false)
    {
        if (mouseAxis.x < pos.x) isFlipped = true;
        else if (mouseAxis.x > pos.x) isFlipped = false;
    }
    else isFlipped = initialFlipped;
}

void Player::mouseRelease(const vec2& mouseAxis)
{
    ballDirection = vec2(mouseAxis.x - pos.x, mouseAxis.y - pos.y).normalized();
    velocity = ballDirection * launchImpulse;
    
    bounceCount = 0;
}

vec2 Player::getSize() const
{
    return spriteSize;
}

vec2 Player::getPos() const
{
    return pos;
}

vec2 Player::getVel() const
{
    return velocity;
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

bool Player::getCollected() const
{
    return hasCollectedCoin;
}

void Player::setDirColor(Pixel color)
{
    dirColor = color;
}

void Player::setState(State newState)
{
    if (newState != state)
    {
        endState(state);
        startState(newState);
        state = newState;
    }
}

void Player::DrawDirection(Surface& screen, const vec2 &mouseAxis)
{
    screen.Line(pos.x + (theSprite.GetWidth() / 2.0f), pos.y + theSprite.GetHeight() - 3.0f, mouseAxis.x, mouseAxis.y, dirColor);
}

void Player::Render(Surface& screen)
{
    theSprite.DrawScaled(sCast<int>(pos.x), sCast<int>(pos.y), sCast<int>(spriteSize.x), sCast<int>(spriteSize.y), isFlipped, &screen);
    //debugging collision box for player
    screen.Box(sCast<int>(pos.x), sCast<int>(pos.y), sCast<int>(pos.x) + sCast<int>(spriteSize.x), sCast<int>(pos.y) + sCast<int>(spriteSize.y), 0xFFFFFF);
}

bool Player::isColliding(int spriteX, int spriteY, int entityX, int entityY)
{
    return ((spriteX + spriteSize.x) > entityX
           && (spriteX - spriteSize.x) < entityX)
           && ((spriteY + spriteSize.y) > entityY 
           && (spriteY - spriteSize.y) < entityY);
}

void Player::Update(bool &playing, Entity* entity, const vec2 &mAxis, float dt)
{
    // only use update for states
    Physics(dt);
    // hpCheck(playing);
    CollisionCheck(entity, dt);
    SquishCheck(dt);
    mouseCheck(mAxis);
}