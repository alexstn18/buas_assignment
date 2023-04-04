#include "Player.h"
#include <string>
#include <iostream>

// health values
constexpr int damage = 5;
constexpr int maxHP = 100;

// sprite SET width
constexpr int spriteSetWidth = 25;

// sprite SET starting point
constexpr float startingPoint = 0.0f;

class Game;

void Player::InitPlayer()
{
    // state = State::Grounded;
    health = maxHP;
    speed.x = 200.0f;
    speed.y = 300.0f;
    isFlipped = false;
    // do a flow chart of 
}

void Player::Physics(float dt)
{
    if (state == State::Grounded)
    {
        return;
    }
    StorePosition();

    velocity.y += gravity * dt;
    pos += velocity * dt;
#ifdef _DEBUG
    std::cout << velocity.x << " " << velocity.y << std::endl;
#endif
    UpdateBoundingBox();
}

void Player::CollisionCheck(float dt)
{
    if (pos.x < 0)
    {
        pos.x = ScreenWidth - theSprite.GetWidth() + 1;
    }
    else if (pos.x > ScreenWidth)
    {
        pos.x = 0 + theSprite.GetWidth();
    }

    if (pos.y > ScreenHeight)
    {
        pos.y = 0;
    }
}

void Player::startState(State newState)
{
    switch (newState)
    {
    case State::Grounded:
        velocity.x = 0;
        velocity.y = 0;
        break;
    case State::Bouncing:
        break;
    }
}

void Player::endState(State oldState)
{
    switch (oldState)
    {
    case State::Grounded:
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
    // if(Game::GameState::Playing)
        setState(State::Bouncing);

    ballDirection = vec2(mouseAxis.x - pos.x, mouseAxis.y - pos.y).normalized();
    velocity = ballDirection * launchImpulse;
    
    bounceCount = 0;
}

void Player::UpdateBoundingBox()
{
    bndBox.left = pos.x;
    bndBox.right = pos.x + spriteSize.x;
    bndBox.top = pos.y;
    bndBox.bottom = pos.y + spriteSize.y;
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

bool Player::getPortalChecker() const
{
    return hasHitPortal;
}

void Player::setDirColor(Pixel color)
{
    dirColor = color;
}

void Player::setBounceCount()
{
    bounceCount++;
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

void Player::setSquished(bool squished)
{
    isSquished = squished;
}

void Player::setPortalChecker(bool portalChecker)
{
    this->hasHitPortal = portalChecker;
}

bool Player::checkState(State state)
{
    if (state == this->state) return true;
    else return false;
}

void Player::setPos(vec2 pos)
{
    this->pos = pos;
}

void Player::setVel(vec2 vel)
{
    this->velocity = vel;
}

void Player::DrawDirection(Surface& screen, const vec2 &mouseAxis)
{
    screen.Line(pos.x + (theSprite.GetWidth() / 2.0f), pos.y + theSprite.GetHeight() - 3.0f, mouseAxis.x, mouseAxis.y, dirColor);
}

void Player::Render(Surface& screen)
{
    theSprite.DrawScaled(sCast<int>(pos.x), sCast<int>(pos.y), sCast<int>(spriteSize.x), sCast<int>(spriteSize.y), isFlipped, &screen);
    //debugging collision box for player
#ifdef _DEBUG
    screen.Box(sCast<int>(pos.x), sCast<int>(pos.y), sCast<int>(pos.x) + sCast<int>(spriteSize.x), sCast<int>(pos.y) + sCast<int>(spriteSize.y), 0xFFFFFF);
#endif    
}

bool Player::isColliding(int spriteX, int spriteY, int entityX, int entityY)
{
    return ((spriteX + spriteSize.x) > entityX
           && (spriteX - spriteSize.x) < entityX)
           && ((spriteY + spriteSize.y) > entityY 
           && (spriteY - spriteSize.y) < entityY);
}

void Player::StorePosition()
{
    bndBox.previousLeft = bndBox.left;
    bndBox.previousRight = bndBox.right;
    bndBox.previousTop = bndBox.top;
    bndBox.previousBottom = bndBox.bottom;
}

void Player::Update(bool &playing, const vec2 &mAxis, float dt)
{
    // only use update for states
    Physics(dt);
    // hpCheck(playing);
    CollisionCheck(dt);
    SquishCheck(dt);
    mouseCheck(mAxis);
}