#pragma once
#include "surface.h"
#include "Entity.h"
#include "template.h"
#include "BoundingBox.h"
#include <cassert>
#include <algorithm>

using namespace Tmpl8;
class Player
{
public:
	enum class State
	{
		Grounded,
		Bouncing
	};
	
	BoundingBox bndBox;

	void InitPlayer(vec2 spawnPoint);

	void Update(bool &playing, const vec2& mAxis, float dt);

	void mouseRelease(const vec2& mouseAxis);

	void UpdateBoundingBox();
	void HitWaterCheck(vec2 spawnPos);

	void DrawDirection(Surface& screen, const vec2& mouseAxis);
	void Render(Surface& screen);

	void damageHealth(int damage);
	void healHealth(int heal);
	
	int getHP() const;
	int getBounceCount() const;
	int getDeathCount() const;
	vec2 getSize() const;
	vec2 getPos() const;
	vec2 getVel() const;
	bool getCollected() const;
	bool getPortalChecker() const;
	bool getSpikeChecker() const;
	bool getWaterChecker() const;

	void setPos(vec2 pos);
	void setVel(vec2 vel);
	void setDirColor(Pixel color);
	void setBounceCount();
	void setDeathCount();
	void resetDeathCount();
	void setPortalChecker(bool portalChecker);
	void setSpikeChecker(bool spikeChecker);

	void setState(State newState);
	bool checkState(State state);
	
private:
	void Physics(float dt);
	void mouseCheck(const vec2& mouseAxis);
	void CollisionCheck(float dt);
	void StorePosition();

	void startState(State newState);
	void endState(State oldState);

	State state;

	Sprite theSprite{ new Surface("assets/ballRed.png"), 1 };
	
	Pixel dirColor{ 0xFFFFFF };

	int health{ 100 };
	int bounceCount{ 0 };
	int deathCount{ 0 };
	
	float gravity{ 420.0f };
	float launchImpulse{ 300.0f };

	vec2 spriteSize{ sCast<float>(theSprite.GetWidth(), sCast<float>(theSprite.GetHeight())) };
	vec2 pos{ 0.0f, 200.0f };
	vec2 ballDirection{ 0.0f };
	vec2 velocity{ 0.0f };

	bool hitTop{ false };
	bool hitBottom{ false };
	bool hitSideL{ false };
	bool hitSideR{ false };
	bool hitSide{ false };
	bool isBouncing{ false };
	bool isFlipped{ false };
	bool isReleased{ false };
	bool initialFlipped{ false };
	bool hasCollectedCoin{ false };
	bool hasHitPortal{ false };
	bool hasHitSpike{ false };
	bool hasHitWater{ false };
};