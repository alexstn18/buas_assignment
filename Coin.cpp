#include "Coin.h"

void Coin::Update(float dt)
{
	/*
	timePassed += dt;
	if (timePassed > timeIncrement)
	{
		coinSprite.SetFrame(coinFrame);
		coinFrame = ++coinFrame % 5;
		timePassed = 0.0f;
	}
	std::cout << active << "\n";
	*/
}

void Coin::Render(Surface& screen)
{
	/*
	if (active)
	{
		coinSprite.Draw(&screen, pos.x, pos.y);
	}
	*/
}

void Coin::setActive(bool activeStatus)
{
	active = activeStatus;
}

void Coin::collectCoin()
{
	// coinCount += 1;
	active = false;
}

/*
int Coin::getCount() const
{
	return coinCount;
}
*/

bool Coin::getActive() const
{
	return active;
}

bool Coin::getCollected() const
{
	return hasBeenCollected;
}