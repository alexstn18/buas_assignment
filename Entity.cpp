#include "Entity.h"

void Entity::Update(float dt)
{
	if(type == Type::coin && active == true)
	{
		// if the entity is of type coin, switch through the coin's frames
		timePassed += dt;
		if (timePassed > timeIncrement)
		{
			sprite->SetFrame(coinFrame);
			coinFrame = ++coinFrame % 5;
			timePassed = 0.0f;
		}
	}
	// update the entity's bounding box
	bndBox.left = pos.x;
	bndBox.right = pos.x + size.x;
	bndBox.top = pos.y;
	bndBox.bottom = pos.y + size.y;
}
	
void Entity::Render(Surface& screen)
{
#ifdef _DEBUG
	screen.Box(bndBox.left, bndBox.top, bndBox.right, bndBox.bottom, 0xFF0000);
#endif
	
	if (type == Type::coin && active == true)
	{
		// renders the coin at its declared position (found in the Level class when loading levels)
		sprite->Draw(&screen, sCast<int>(pos.x), sCast<int>(pos.y));
	}
}

bool Entity::getActive() const
{
	return active;
}

void Entity::collectCoin()
{
	active = false;
}

void Entity::setPos(vec2 pos)
{
	this->pos = pos;
}

void Entity::setSize(vec2 size)
{
	this->size = size;
}

void Entity::playEntitySound(SFX& sfx)
{
	if (type == Type::coin && active == true)
	{
		sfx.coinSound.play();
	}

	if (type == Type::ground || type == Type::platform)
	{
		sfx.bounceSound.play();
	}
}