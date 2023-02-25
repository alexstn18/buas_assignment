#include "Entity.h"

Entity::Entity() {}

Entity::~Entity() {}

void Entity::Init()
{
}

void Entity::Update()
{
}

void Entity::Draw(Surface& screen, bool collected)
{
	spike.Draw(&screen, sCast<int>(spikePos.x), sCast<int>(spikePos.y));
	grass.Draw(&screen, sCast<int>(grassPos.x), sCast<int>(grassPos.y));

	if (collected == false)
	{
		coin.Draw(&screen, sCast<int>(coinPos.x), sCast<int>(coinPos.y));
	}
}
