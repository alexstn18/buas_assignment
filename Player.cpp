#include "Player.h"
#include <string>
#include <iostream>

// health values
constexpr int damage = 5;
constexpr int maxHP = 230;

// sprite SET starting point
constexpr float startingPoint = 0.0f;

void Player::InitPlayer(vec2 spawnPoint)
{
    // initialize all the player's stats with their default values
    pos = spawnPoint;
    velocity = 0;
    health = maxHP;
    bounceCount = 0;
    state = State::Bouncing;
    hasHitWater = false;
    hasHitSpike = false;
    hasHitPortal = false;
    isFlipped = false;
}

void Player::Physics(float dt)
{
    // physics will not apply if the player's state is grounded, so the player can remain stationary in it's grounded state
    if (state == State::Grounded)
    {
        return;
    }
    StorePosition(); // stores the bounding box of the player

    velocity.y += gravity * dt; 
    pos += velocity * dt;
#ifdef _DEBUG
    // std::cout << velocity.x << " " << velocity.y << std::endl;
#endif
    UpdateBoundingBox(); // updates the player's bounding box after it's velocity has been modified
}

void Player::CollisionCheck(float dt)
{
    // screen collision check
    bool hitTop = pos.y < 0;
    bool hitSide = pos.x > ScreenWidth - theSprite.GetWidth() || pos.x < 0;

    if (hitTop)
    {
        pos.y = 0;
    }

    if (hitSide)
    {
        if (pos.x < 0)
        {
            pos.x = 0;
        }
        else
        {
            pos.x = static_cast<float>( ScreenWidth - theSprite.GetWidth() );
        }
    }
}

// State machine section
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

// state machine setter
void Player::setState(State newState)
{
    if (newState != state)
    {
        endState(state);
        startState(newState);
        state = newState;
    }
}
// state machine checker
bool Player::checkState(State state)
{
    if (state == this->state) return true;
    else return false;
}

// checker section
void Player::mouseCheck(const vec2& mouseAxis)
{
    // this function makes the player sprite follow the mouse's direction
    initialFlipped = isFlipped;
    if (isReleased == false)
    {
        if (mouseAxis.x < pos.x) isFlipped = true;
        else if (mouseAxis.x > pos.x) isFlipped = false;
    }
    else isFlipped = initialFlipped;
}

void Player::HitWaterCheck(vec2 spawnPos)
{
    bool hitBottom = pos.y > ScreenHeight - theSprite.GetHeight();
    // bottom collision check => water check
    if (hitBottom)
    {
        deathCount++;
        hasHitWater = true;
        InitPlayer(spawnPos);
    }
}

void Player::mouseRelease(const vec2& mouseAxis)
{
    // this function stores the direction that the player is aiming for, then the player's velocity is calculated using this direction and the launch impulse
    setState(State::Bouncing);

    ballDirection = vec2(mouseAxis.x - pos.x, mouseAxis.y - pos.y).normalized();
    
    
#ifdef _DEBUG
    std::cout << "pos: " << pos.x << " " << pos.y << std::endl;
    std::cout << "mouseAxis: " << mouseAxis.x << " " << mouseAxis.y << std::endl;
    std::cout << "unnormalized: " << mouseAxis.x - pos.x << " " << mouseAxis.y - pos.y << std::endl;
    std::cout << "normalized:" << ballDirection.x << " " << ballDirection.y << std::endl;
    std::cout << "launch impulse: " << launchImpulse << std::endl;
    std::cout << std::endl;
#endif  
    velocity = ballDirection * launchImpulse;

    bounceCount = 0;
}

void Player::UpdateBoundingBox()
{
    // updates the bounding box of the player
    bndBox.left = pos.x;
    bndBox.right = pos.x + spriteSize.x;
    bndBox.top = pos.y;
    bndBox.bottom = pos.y + spriteSize.y;
}

// Getter section
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

bool Player::getSpikeChecker() const
{
    return hasHitSpike;
}

bool Player::getWaterChecker() const
{
    return hasHitWater;
}

// Setter section
void Player::setDirColor(Pixel color)
{
    dirColor = color;
}

void Player::setBounceCount()
{
    bounceCount++;
}

void Player::setDeathCount()
{
    deathCount++;
}

void Player::resetDeathCount()
{
    deathCount = 0;
}

void Player::setPortalChecker(bool portalChecker)
{
    this->hasHitPortal = portalChecker;
}

void Player::setSpikeChecker(bool spikeChecker)
{
    hasHitSpike = spikeChecker;
}

void Player::setPos(vec2 pos)
{
    this->pos = pos;
}

void Player::setVel(vec2 vel)
{
    this->velocity = vel;
}


// Rendering section
void Player::DrawDirection(Surface& screen, const vec2 &mouseAxis)
{
    // draws a line from the player's position to the mouse's position, representing the direction of the movement
    screen.Line(pos.x + (theSprite.GetWidth() / 2.0f), pos.y + theSprite.GetHeight() - 12.0f, mouseAxis.x, mouseAxis.y, dirColor);
}

void Player::Render(Surface& screen)
{
    // draws the player to the screen
    theSprite.DrawScaled(sCast<int>(pos.x), sCast<int>(pos.y), sCast<int>(spriteSize.x), sCast<int>(spriteSize.y), isFlipped, &screen);
    //debugging collision box for player
#ifdef _DEBUG
    screen.Box(sCast<int>(pos.x), sCast<int>(pos.y), sCast<int>(pos.x) + sCast<int>(spriteSize.x), sCast<int>(pos.y) + sCast<int>(spriteSize.y), 0xFFFFFF);
#endif    
}

// health
void Player::damageHealth(int damage)
{
    // damage the player
    health -= damage;
}

void Player::healHealth(int heal)
{
    // heal the player + override check
    
    health += heal;

    if (health > maxHP)
    {
        health = maxHP;
    }
    
}

void Player::StorePosition()
{
    // stores the bounding box of the player
    bndBox.previousLeft = bndBox.left;
    bndBox.previousRight = bndBox.right;
    bndBox.previousTop = bndBox.top;
    bndBox.previousBottom = bndBox.bottom;
}

void Player::Update(bool &playing, const vec2 &mAxis, float dt)
{
    Physics(dt);
    CollisionCheck(dt);
    mouseCheck(mAxis);
}