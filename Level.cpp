#include "Level.h"

Level::Level()
{
	entities.push_back(ground);
	entities.push_back(stonePlatform1);
	entities.push_back(stonePlatform2);
	entities.push_back(portal);
	PushbackSpikesIntoVector();
	PushbackCoinsIntoVector();
}

// function initializes (loads) the entities of the current level
// each level also has a specific level ID, which gets assigned at its initialization
void Level::Init(Stage level)
{
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
}
// function renders the map (stored entirely in an image) of the current level
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
		map_level_three.Draw(screen, 0, 0);
		break;
	}
}

int Level::getLevelID() const
{
	return levelID;
}
// function returns the player's spawnpoint of the current level
vec2 Level::getSpawnPoint(Stage level) const
{
	switch (level)
	{
	case Stage::ONE:
		return { 0, 50 };
	case Stage::TWO:
		return { 32, 188 };
	case Stage::THREE:
		return { 1024, 83 };
	}
	return { 0, 0 };
}

std::vector<Entity>& Level::getEntities()
{
	return entities;
}
// function loads the exact positions and sizes of all of the entities from the FIRST level
void Level::LoadFirstLevel()
{
	entities[0].setPos({ 0, 560 });
	entities[0].setSize({ 1280, 160 });

	entities[1].setPos({ 0, 147 });
	entities[1].setSize({ 215, 32 });

	entities[2].setPos({ 226, 415 });
	entities[2].setSize({ 384, 32 });

	entities[3].setPos({ 352, 496 });
	entities[3].setSize({ 32, 64 });

	// the LoadSpikes function is to preserve space and to improve readability of the code
	// loads the individual sizes and positions of each spike in the level
	LoadSpikes({ 215, 179 }, { 32, 32 },
			   { 226, 447 }, { 32, 20 },
			   { 544, 540 }, { 32, 20 },
			   { -100 , -100 }, { 0, 0 });
	
	LoadCoins({ 896, 528 }, { 32, 32 });
}
// function loads the exact positions and sizes of all of the entities from the SECOND level
void Level::LoadSecondLevel()
{
	entities[0].setPos({ 0, 688 });
	entities[0].setSize({ 1280, 32 });

	entities[1].setPos({ 0, 352 });
	entities[1].setSize({ 736, 32 });
	
	entities[2].setPos({ 704, 448 });
	entities[2].setSize({ 256, 32 });

	entities[3].setPos({64, 624});
	entities[3].setSize({32, 64});

	LoadSpikes({ 352, 324 }, { 32, 28 },
			   { 848, 420 }, { 32, 28 },
		       { 480, 660 }, { 32, 28 },
		       { 960, 660 }, { 32, 28 });

	LoadCoins({ 672, 384 }, { 32, 32 });
}
// function loads the exact positions and sizes of all of the entities from the THIRD level
void Level::LoadThirdLevel()
{
	entities[0].setPos({ 256, 560 });
	entities[0].setSize({ 1024, 160 });

	entities[1].setPos({896, 147});
	entities[1].setSize({384, 32});

	entities[2].setPos({254, 319});
	entities[2].setSize({ 800, 32 });

	entities[3].setPos({352, 496});
	entities[3].setSize({32, 64});

	LoadSpikes({ 780, 289 }, { 32, 30 },
			   { 479, 289 }, { 32, 30 },
		       { 992, 530 }, { 32, 30 },
		       { 576, 530 }, { 32, 30 });

	LoadCoins({ 415, 287 }, { 32, 32 });
}

void Level::PushbackSpikesIntoVector()
{
	entities.push_back(spike1);
	entities.push_back(spike2);
	entities.push_back(spike3);
	entities.push_back(spike4);
}

void Level::PushbackCoinsIntoVector()
{
	entities.push_back(coin1);
}

void Level::LoadSpikes(vec2 spike1Pos, vec2 spike1Size, vec2 spike2Pos, vec2 spike2Size, vec2 spike3Pos, vec2 spike3Size, vec2 spike4Pos, vec2 spike4Size)
{
	entities[4].setPos(spike1Pos);
	entities[4].setSize(spike1Size);

	entities[5].setPos(spike2Pos);
	entities[5].setSize(spike2Size);

	entities[6].setPos(spike3Pos);
	entities[6].setSize(spike3Size);

	entities[7].setPos(spike4Pos);
	entities[7].setSize(spike4Size);
}

void Level::LoadCoins(vec2 coin1Pos, vec2 coin1Size)
{
	entities[8].active = true;
	entities[8].setPos(coin1Pos);
	entities[8].setSize(coin1Size);
}