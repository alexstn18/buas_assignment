#include "Level.h"

Level::Level()
{
	level = Levels::STAGE_1;
}

void Level::Init(Entity* ground, std::vector<Entity*>stonePlatforms, std::vector<Entity*>spikes, Entity* portal)
{
	Entity* stonePlatform1{ new Entity() };
	Entity* stonePlatform2{ new Entity() };
	stonePlatforms.push_back(stonePlatform1);
	stonePlatforms.push_back(stonePlatform2); 
	// Entity* spike1{ new Entity() };
	if (level == Levels::STAGE_1)
	{
		ground->setPos({ 0, 560 });
		ground->setSize({ 1024, 160 });  
		stonePlatform1->setPos({ 0, 147 }); 
		stonePlatform1->setSize({ 384, 32 });
		stonePlatform2->setPos({ 226, 415 }); 
		stonePlatform2->setSize({ 384, 32 }); 
		portal->setPos({ 992, 528 }); 
		portal->setSize({ 32, 32 }); 
	}
	else if (level == Levels::STAGE_2)
	{
		ground->setPos({ 0, 560 });
		ground->setSize({ 1024, 160 });
		stonePlatform1->setPos({ 0, 147 });
		stonePlatform1->setSize({ 384, 32 });
		stonePlatform2->setPos({ 226, 415 });
		stonePlatform2->setSize({ 384, 32 });
		portal->setPos({ 992, 528 });
		portal->setSize({ 32, 32 });
	}
	else if (level == Levels::STAGE_3)
	{
		ground->setPos({ 0, 560 });
		ground->setSize({ 1024, 160 });
		stonePlatform1->setPos({ 0, 147 });
		stonePlatform1->setSize({ 384, 32 });
		stonePlatform2->setPos({ 226, 415 });
		stonePlatform2->setSize({ 384, 32 });
		portal->setPos({ 992, 528 });
		portal->setSize({ 32, 32 });
	}
}


void Level::Update(Game& game, Player& player)
{
	if (level == Levels::STAGE_1 && player.getPortalChecker() == true)
	{
		level = Levels::STAGE_2;
		player.setPortalChecker(false);
	}
	else if (level == Levels::STAGE_2 && player.getPortalChecker() == true)
	{
		level = Levels::STAGE_3;
		player.setPortalChecker(false);
		player.InitPlayer();
	}
	else if (level == Levels::STAGE_3 && player.getPortalChecker() == true)
	{
		game.gameState = Game::GameState::Menu;
		player.setPortalChecker(false);
	}
}

void Level::Render(Surface* screen)
{
	if (level == Levels::STAGE_1) 
	{
		map_level_one.Draw(screen, 0, 0);
	}
	else if (level == Levels::STAGE_2) 
	{
		// map_level_two.Draw(screen, 0, 0);
	}
	else if (level == Levels::STAGE_3)
	{
		// map_level_three.Draw(screen, 0, 0);
	}
}
