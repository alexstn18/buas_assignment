#include "Entity.h"

void Entity::Update(float dt)
{
	if(type == Type::coin && active == true)
	{
		timePassed += dt;
		if (timePassed > timeIncrement)
		{
			sprite->SetFrame(coinFrame);
			coinFrame = ++coinFrame % 5;
			timePassed = 0.0f;
		}
	}

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
		sprite->Draw(&screen, pos.x, pos.y);
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