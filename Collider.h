#pragma once
#include "Player.h"
#include "Entity.h"
#include "BoundingBox.h"
#include "SFX.h"

class Collider
{
public:
	static void CheckCollisions(Player& player, Entity& entity, SFX& sfx, int& coinCount);
	static void EdgeCheck(Player& player, Entity& entity, SFX& sfx, int& coinCount);
};