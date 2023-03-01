#pragma once
#include "surface.h"
#include "Entity.h"
#include "template.h"
#include <cassert>
#include <Windows.h>

using namespace Tmpl8;
class Player
{
public:
	void InitPlayer();

	void Update(bool &playing, Entity* entity, const vec2& mAxis, float dt);

	void mouseRelease(const vec2& mouseAxis);

	void DrawDirection(Surface& screen, const vec2& mouseAxis);
	void Draw(Surface& screen);

	int getWidth() const;
	int getHeight() const;
	int getHP() const;
	int getBounceCount() const;
	int getDeathCount() const;
	vec2 getPos() const;
	vec2 getVel() const;
	bool getCollected() const;

	void resetBounceCount();
	bool isColliding(int spriteX, int spriteY, int entityX, int entityY);
private:
	void Physics(float dt);
	void SquishCheck(float dt);
	void mouseCheck(const vec2& mouseAxis);
	void CollisionCheck(Entity* entity, float dt);
	// void hpCheck(bool &isPlaying);

	Sprite theSprite{ new Surface("assets/ball.png"), 1 };

	int spriteW{ theSprite.GetWidth() };
	int spriteH{ theSprite.GetHeight() };
	int health{ 100 };
	int bounceCount{ 0 };
	int deathCount{ 0 };
	
	float gravity{ 300.0f };
	float launchImpulse{ 200.0f };

	vec2 pos{ 5.0f };
	vec2 velocity{ 0.0f };
	vec2 speed{ 200.0f, 300.0f };

	bool hitTop{ false };
	bool hitBottom{ false };
	bool hitSideL{ false };
	bool hitSideR{ false };
	bool hitSide{ false };
	bool isSquished{ false };
	bool isBouncing{ false };
	bool isFlipped{ false };
	bool isReleased{ false };
	bool readyForLaunch{ false };
	bool hasCollectedCoin{ false };
};