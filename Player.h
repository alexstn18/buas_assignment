#pragma once
#include "surface.h"
#include "Entity.h"
#include "template.h"
#include <cassert>

using namespace Tmpl8;
class Player :
	public Entity
{
public:
	Player();

	~Player();

	void InitPlayer();

	void ReInitPlayer();

	void CollisionCheck();

	void SquishCheck();

	void hpCheck(bool &isPlaying);

	const int32_t getHP();

	const int getDeathCount();

	void Draw(Surface* screen);

	void Move();

	bool isColliding(const Sprite& sprite, int spriteX, int spriteY, const Sprite& entity, int entityX, int entityY);

	void Update(bool &playing);
protected:
	int coinHitCount = 0;
private:
	Sprite theSprite{ new Surface("assets/ball.png"), 1 };
	int spriteW{ theSprite.GetWidth() };
	int spriteH{ theSprite.GetHeight() };
	int32_t health{ 100 };
	float spriteX{ 5.0f };
	float spriteY{ 5.0f };
	float friction{ 0.0f };
	float speedX{ 2.0f };
	float speedY{ 3.0f };

	bool hitTop{ false };
	bool hitBottom{ false };
	bool hitSideL{ false };
	bool hitSideR{ false };
	bool hitSide{ false };

	int16_t bounceCount{ 0 };
	int16_t deathCount{ 0 };
	bool isSquished{ false };
	bool isBouncing{ false };
	bool isFlipped{ false };
};