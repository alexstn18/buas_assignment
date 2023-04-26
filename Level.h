#pragma once
#include "template.h"
#include "surface.h"
#include "Player.h"
#include "Coin.h"
#include "Entity.h"
#include <vector>
#include <array>

using namespace Tmpl8;

class Level
{
public:
	enum class Stage
	{
		ONE,
		TWO,
		THREE
	};
	
	int levelID{ 0 };

	Level();

	void Init(Stage level);
	void Render(Stage level, Surface* screen);
	
	int getLevelID() const;
	vec2 getSpawnPoint(Stage level) const;
	std::vector<Entity>& getEntities();
private:
	void LoadFirstLevel();
	void LoadSecondLevel();
	void LoadThirdLevel();
	void PushbackSpikesIntoVector();
	void PushbackCoinsIntoVector();
	void LoadSpikes(vec2 spike1Pos, vec2 spike1Size,
					vec2 spike2Pos, vec2 spike2Size,
					vec2 spike3Pos, vec2 spike3Size,
					vec2 spike4Pos, vec2 spike4Size);
	void LoadCoins(vec2 coin1Pos, vec2 coin1Size);
	std::vector<Entity>entities;

	vec2 spawnPointPos;
	Sprite coinSprite{ new Surface("assets/coins.png"), 6 };

	// Entity ground{ Entity(Entity::Type::ground, 0) };
	Entity ground{ Entity::Type::ground, 0 };
	Entity stonePlatform1{ Entity::Type::platform, 1 };
	Entity stonePlatform2{ Entity::Type::platform, 1 };
	Entity portal{ Entity::Type::portal, 2 };
	Entity spike1{ Entity::Type::spike, 3 };
	Entity spike2{ Entity::Type::spike, 3 };
	Entity spike3{ Entity::Type::spike, 3 };
	Entity spike4{ Entity::Type::spike, 3 };
	// Coin coin1{ Coin::Type::coin, 4 };
	Entity coin1{ Entity::Type::coin, 4, &coinSprite };

	Sprite map_level_one{ new Surface("assets/level1map.png"), 1 };
	Sprite map_level_two{ new Surface("assets/level2map.png"), 1 };
	Sprite map_level_three{ new Surface("assets/level3map.png"), 1 };
};	