#include "Level.h"

Level::Level()
{
	Init(Stage::ONE);
	entities.push_back(ground);
	entities.push_back(stonePlatform1);
	entities.push_back(stonePlatform2);
	entities.push_back(portal);
	PushbackSpikesIntoVector();
	PushbackCoinsIntoVector();
}

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
		return { 0, 50 };
	case Stage::TWO:
		return { 32, 188 };
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
	PushbackSpikesIntoVector();
	PushbackCoinsIntoVector();
	
	entities[0].setPos({ 0, 560 });
	entities[0].setSize({ 1024, 160 });
	
	entities[1].setPos({ 0, 147 });
	entities[1].setSize({ 384, 32 });

	entities[2].setPos({ 226, 415 });
	entities[2].setSize({ 384, 32 });
	
	entities[3].setPos({ 384, 496 });
	entities[3].setSize({ 32, 64 });

	LoadSpikes({ 31, 179 }, { 32, 32 },
			   { 215, 179 }, { 32, 32 },
		       { 256, 528 }, { 32, 32 },
		       { 544, 528 }, { 32, 32 });

	LoadCoins({ 215, 115 }, { 32, 32 });
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

	LoadSpikes({ 352, 320 }, { 32, 32 },
			   { 848, 384 }, { 32, 32 },
		       { 480, 656 }, { 32, 32 },
		       { 960, 656 }, { 32, 32 });

	LoadCoins({ 672, 384 }, { 32, 32 });
}

void Level::LoadThirdLevel()
{

	entities[0].setPos({ 100, 400 });
	entities[0].setSize({ 1024, 160 });

	entities[1].setPos({100, 247});
	entities[1].setSize({384, 32});

	entities[2].setPos({326, 515});
	entities[2].setSize({ 384, 32 });

	entities[3].setPos({992, 528});
	entities[3].setSize({32, 32});

	LoadSpikes({ 352, 320 }, { 32, 32 },
		{ 848, 384 }, { 32, 32 },
		{ 480, 656 }, { 32, 32 },
		{ 960, 656 }, { 32, 32 });

	LoadCoins({ 215, 115 }, { 32, 32 });
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
	entities[8].setPos(coin1Pos);
	entities[8].setSize(coin1Size);
}
