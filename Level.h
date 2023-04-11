#pragma once
#include "template.h"
#include "surface.h"
#include "Player.h"
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
	
	std::vector<Entity>entities;
	
	vec2 spawnPointPos;

	Entity ground{ Entity(Entity::Type::ground, 0) };
	Entity stonePlatform1{ Entity(Entity::Type::platform, 1) };
	Entity stonePlatform2{ Entity(Entity::Type::platform, 1) };
	Entity portal{ Entity(Entity::Type::portal, 2) };

	Sprite map_level_one{ new Surface("assets/level1map.png"), 1 };
	Sprite map_level_two{ new Surface("assets/level2map.png"), 1 };
	// Sprite map_level_three{ new Surface("assets/tutorialTileMap.png"), 1 };
	// Sprite winImage{ new Surface("assets/winImage.png", 1) };
};