#pragma once
#include "template.h"
#include "surface.h"
#include "Entity.h"
#include <vector>

struct Level
{
	Entity* ground{ new Entity() };
	// Entity* stonePlatform1{ new Entity() };
	// Entity* stonePlatform2{ new Entity() };
	std::vector<Entity*> stonePlatforms;
	std::vector<Entity*> spikes;
	Entity* portal{ new Entity() };

	void Init()
	{

	}
};