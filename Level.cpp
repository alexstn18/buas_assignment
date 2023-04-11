#include "Level.h"

Level::Level()
{
	Init(Stage::ONE);
	entities.push_back(ground);
	entities.push_back(stonePlatform1);
	entities.push_back(stonePlatform2);
	entities.push_back(portal);
}

void Level::Init(Stage level)
{
	// Entity* spike1{ new Entity() };
	switch (level)
	{
	case Stage::ONE:
		LoadFirstLevel();
		levelID = 1;
		break;
	case Stage::TWO:
		LoadSecondLevel();
		levelID = 2;
		break;
	case Stage::THREE:
		LoadThirdLevel();
		levelID = 3;
		break;
	default:
		break;
	}
	// please replace this with a switch statement
	// + refactor this into functions
}

void Level::Render(Stage level, Surface* screen)
{
	switch (level)
	{
	case Stage::ONE:
		map_level_one.Draw(screen, 0, 0);
		break;
	case Stage::TWO:
		map_level_two.Draw(screen, 0, 0);
		break;
	case Stage::THREE:
		map_level_one.Draw(screen, 0, 0);
		break;
	}
}

int Level::getLevelID() const
{
	return levelID;
}

vec2 Level::getSpawnPoint(Stage level) const
{
	switch (level)
	{
	case Stage::ONE:
		return { 0, 0 };
	case Stage::TWO:
		return { 0, 0 };
	case Stage::THREE:
		return { 0, 0 };
	}
	return { 0, 0 };
}

std::vector<Entity>& Level::getEntities()
{
	return entities;
}

void Level::LoadFirstLevel()
{
	entities.push_back(ground);
	entities.push_back(stonePlatform1);
	entities.push_back(stonePlatform2);
	entities.push_back(portal);
	
	entities[0].setPos({ 0, 560 });
	entities[0].setSize({ 1024, 160 });
	
	entities[1].setPos({ 0, 147 });
	entities[1].setSize({ 384, 32 });

	entities[2].setPos({ 226, 415 });
	entities[2].setSize({ 384, 32 });
	
	entities[3].setPos({ 992, 496 });
	entities[3].setSize({ 32, 64 });
}

void Level::LoadSecondLevel()
{
	entities[0].setPos({ 0, 688 });
	entities[0].setSize({ 1280, 32 });

	entities[1].setPos({ 0, 352 });
	entities[1].setSize({ 736, 32 });
	
	entities[2].setPos({ 704, 416 });
	entities[2].setSize({ 256, 32 });

	entities[3].setPos({64, 624});
	entities[3].setSize({32, 64});
}

void Level::LoadThirdLevel()
{
	entities[0].setPos({ 100, 400 });
	entities[0].setSize({ 1024, 160 });

	stonePlatform1.setPos({ 100, 247 });
	stonePlatform1.setSize({ 384, 32 });

	stonePlatform2.setPos({ 326, 515 });
	stonePlatform2.setSize({ 384, 32 });

	portal.setPos({ 992, 528 });
	portal.setSize({ 32, 32 });
}
