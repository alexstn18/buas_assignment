#pragma once
#include "surface.h"
#include "template.h"
#include "Player.h"
#include "Entity.h"
#include "Level.h"
#include <string>

using namespace Tmpl8;

class HUD
{
public:
	void Render(Surface* screen);
	void Update(Player* player, Level& level, int coin);

	std::string getCoinString() const;
private:
	Sprite hpIcon{ new Surface("assets/heart_shaded.png"), 1 };
	Sprite deathIcon{ new Surface("assets/skullSprite.png"), 1 };

	std::string healthString;
	std::string deathCountString;
	std::string levelString;
	std::string coinString;
};

