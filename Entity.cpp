#include "Entity.h"

Entity::Entity()
{
}

Entity::~Entity()
{
}

void Entity::Init()
{
}

void Entity::Update()
{
}

void Entity::Draw(Surface* screen, bool collected)
{
	spike.Draw(screen, 400, 300);
	grass.Draw(screen, 25, 300);
	if (collected == false)
	{
		coin.Draw(screen, 600, 500);
	}
}
