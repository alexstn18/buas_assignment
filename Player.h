#pragma once
#include "surface.h"
#include "template.h"

using namespace Tmpl8;

class Player
{
public:
	void InitPlayer();

	void ReInitPlayer();

	void CollisionCheck();

	void SquishCheck();

	void hpCheck();

	void Draw(Surface* screen);
private:
	Sprite theSprite{ new Surface("assets/ball.png"), 1 };
	int spriteW = theSprite.GetWidth();
	int spriteH = theSprite.GetHeight();
	int16_t health = 100;
	float spriteX{ 5.0f };
	float spriteY{ 5.0f };
	float friction{ 0.0f };
	float speedX{ 2.0f };
	float speedY{ 3.0f };

	int bounceCount;
	bool isSquished = spriteH < 25 || spriteW < 25;
	bool isBouncing = false;
	bool isFlipped = false;
};