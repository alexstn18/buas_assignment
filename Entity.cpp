#include "Entity.h"

void Entity::Init()
{
}

void Entity::Update()
{
}

void Entity::Render(Surface& screen, bool collected)
{
	spike.Draw(&screen, sCast<int>(spikePos.x), sCast<int>(spikePos.y));
	//debug collision box for spike
	screen.Box(sCast<int>(spikePos.x), sCast<int>(spikePos.y), sCast<int>(spikePos.x) + spike.GetWidth(), sCast<int>(spikePos.y) + spike.GetHeight(), 0xFFFFFF);
	grass.Draw(&screen, sCast<int>(grassPos.x), sCast<int>(grassPos.y));
	//debug collision box for grass
	screen.Box(sCast<int>(grassPos.x), sCast<int>(grassPos.y), sCast<int>(grassPos.x) + grass.GetWidth(), sCast<int>(grassPos.y) + grass.GetHeight(), 0xFFFFFF);

	if (collected == false)
	{
		coin.Draw(&screen, sCast<int>(coinPos.x), sCast<int>(coinPos.y));
		//debug collision box for coin
		screen.Box(sCast<int>(coinPos.x), sCast<int>(coinPos.y), sCast<int>(coinPos.x) + coin.GetWidth(), sCast<int>(coinPos.y) + coin.GetHeight(), 0xFFFFFF);
	}
}
