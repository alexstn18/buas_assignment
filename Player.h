#pragma once
#include "surface.h"
#include "template.h"
#include <cassert>

using namespace Tmpl8;

class Player
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

	void Update(bool &playing);
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

	bool hitTop = spriteY < NULL;
	bool hitBottom = spriteY > ScreenHeight - theSprite.GetHeight();
	bool hitSideL = spriteX < 0;
	bool hitSideR = spriteX > ScreenWidth - theSprite.GetWidth();
	bool hitSide = hitSideL || hitSideR;

	int16_t bounceCount{ 0 };
	int16_t deathCount{ 0 };
	bool isSquished = spriteH < 25 || spriteW < 25;
	bool isBouncing = false;
	bool isFlipped = false;
};