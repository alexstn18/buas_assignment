#include "Coin.h"

void Coin::Init()
{
	hasBeenCollected = false;
	isActive = true;
}

void Coin::Update()
{
	if (hasBeenCollected == true)
	{
		if (isActive == true) coinCount += 1;
		isActive = false;
	}
}

void Coin::Render(Surface& screen, int xPos, int yPos)
{
	if (isActive == true)
	{
		coinSprite.Draw(&screen, xPos, yPos);
	}
}

void Coin::setActive(bool activeStatus)
{
	isActive = activeStatus;
}

void Coin::setCollected(bool collectedStatus)
{
	hasBeenCollected = collectedStatus;
}

int Coin::getCount() const
{
	return coinCount;
}

bool Coin::getActive() const
{
	return isActive;
}

bool Coin::getCollected() const
{
	return hasBeenCollected;
}
