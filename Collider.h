#pragma once
#include "Player.h"
#include "Entity.h"
#include "Coin.h"
#include "BoundingBox.h"

class Collider
{
public:
	static void CheckCollisions(Player& player, Entity& entity, Coin& coin);
	static void EdgeCheck(Player& player, Entity& entity, Coin& coin);
};