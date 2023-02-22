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
	// !! organize functions by grouping them
	Player();

	~Player();

	void InitPlayer();

	void ReInitPlayer();

	void CollisionCheck(Entity* entity);

	void SquishCheck();

	void mouseCheck(const vec2 &mouseAxis);

	void hpCheck(bool &isPlaying);

	int getWidth() const;

	int getHeight() const;

	int getHP() const;

	int getDeathCount() const;

	int getX() const;

	int getY() const;

	bool getCollected() const;

	void DrawDirection(Surface* screen, const vec2& mouseAxis);

	void Draw(Surface* screen);

	void Move(const vec2& mouseAxis);

	bool isColliding(int spriteX, int spriteY, int entityX, int entityY);

	void Update(bool &playing, Entity* entity, const vec2& mAxis);
private:
	Sprite theSprite{ new Surface("assets/ball.png"), 1 };
	int spriteW{ theSprite.GetWidth() };
	int spriteH{ theSprite.GetHeight() };
	int health{ 100 };
	float spriteX{ 5.0f };
	float spriteY{ 5.0f };
	float speedX{ 2.0f };
	float speedY{ 3.0f };

	bool hitTop{ false };
	bool hitBottom{ false };
	bool hitSideL{ false };
	bool hitSideR{ false };
	bool hitSide{ false };

	int bounceCount{ 0 };
	int deathCount{ 0 };
	bool isSquished{ false };
	bool isBouncing{ false };
	bool isFlipped{ false };
	bool isReleased{ false };

	bool readyForLaunch;

	bool hasCollectedCoin{ false };
};