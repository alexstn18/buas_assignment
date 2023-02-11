#pragma once
#include "template.h"
#include "surface.h"
#include "game.h"
#include "Player.h"
#include "Entity.h"

namespace Tmpl8
{
	class Collider :
		public Player, public Entity
	{
	public:
		Collider();
		~Collider();
		// void CollisionCheck(Sprite& sprite1, Sprite& sprite2, float sprite1X, float sprite1Y);
	protected:
		bool isColliding(const Sprite& sprite, int spriteX, int spriteY, const Sprite& entity, int entityX, int entityY);
	};

}

