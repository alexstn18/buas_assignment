#pragma once
#include "surface.h"
#include "template.h"

using namespace Tmpl8;

class Coin
{
public:
	void Init();
	void Update();
	void Render(Surface& screen, int xPos, int yPos);

	void setActive(bool activeStatus);
	void setCollected(bool collectedStatus);

	int getCount() const;
	bool getActive() const;
	bool getCollected() const;
private:
	Sprite coinSprite{ new Surface("assets/coin.png"), 1 };

	int coinCount{ 0 };

	bool isActive{ false };
	bool hasBeenCollected{ false };
};

