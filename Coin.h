#pragma once
#include <iostream>
#include "surface.h"
#include "template.h"
#include "Entity.h"
#include "BoundingBox.h"

using namespace Tmpl8;

class Coin : public Entity
{
public:
	Coin(Type type, int ID) :
		Entity(type, ID) {};
	
	void Update(float dt) override;
	void Render(Surface& screen) override;

	void setActive(bool activeStatus);
	void collectCoin() override;

	int getCount() const;
	bool getActive() const;
	bool getCollected() const;
private:
	// Sprite coinSprite{ new Surface("assets/coins.png"), 6 };

	// int coinFrame{ 0 };

	// vec2 size{ coinSprite.GetWidth(), coinSprite.GetHeight() };
	// float timePassed{ 0.0f };
	// float timeIncrement{ 0.1f };

	bool hasBeenCollected{ false };
};

