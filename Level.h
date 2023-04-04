#pragma once
#include "template.h"
#include "surface.h"
#include "Game.h"
#include "Player.h"
#include "Entity.h"
#include <vector>

using namespace Tmpl8;

class Level
{
public:
	enum class Levels
	{
		STAGE_1,
		STAGE_2,
		STAGE_3
	};
	
	Levels level;

	Level();

	void Init(Entity* ground, std::vector<Entity*>stonePlatforms, std::vector<Entity*>spikes, Entity* portal);
	void Update(Game& game, Player& player);
	void Render(Surface* screen);
private:
	Sprite map_level_one{ new Surface("assets/tutorialTileMap.png"), 1};
	// Sprite map_level_two{ new Surface("assets/tutorialTileMap.png"), 1 };
	// Sprite map_level_three{ new Surface("assets/tutorialTileMap.png"), 1 };
};