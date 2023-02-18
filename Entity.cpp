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

bool Entity::isUsed(Sprite* sprite)
{
	return false;
}

void Entity::Update()
{
}

void Entity::Draw(Surface* screen)
{
	spike.Draw(screen, 400, 300);
	grass.Draw(screen, 25, 300);
	coin.Draw(screen, 600, 500);
}
