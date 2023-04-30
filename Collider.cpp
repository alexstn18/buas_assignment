#include "Collider.h"
// Initial implementation from Erik Cupak (@ecupak)
// Additional help from Joey van Haren (@chadjoey)

constexpr float velMultiplier = 0.6f;

void Collider::CheckCollisions(Player& player, Entity& entity, SFX& sfx, int& coinCount)
{
	if (player.checkState(Player::State::Grounded)) return; // 
	if (BoundingBox::AABB(player.bndBox, entity.bndBox))
	{
		EdgeCheck(player, entity, sfx, coinCount);
	}
}

// this function is only called if the bounding boxes of the player and any entity collide
void Collider::EdgeCheck(Player& player, Entity& entity, SFX& sfx, int& coinCount)
{
	int bounceCount = player.getBounceCount();

	entity.playEntitySound(sfx);

	if (entity.type == Entity::Type::ground || entity.type == Entity::Type::platform)
	{
		// each bounce costs the player 5 health
		player.damageHealth(5);
	}

	if (entity.type == Entity::Type::portal)
	{
		// if statement that tracks whether the player has hit a portal
		player.setPortalChecker(true);
		return;
	}
	if (entity.type == Entity::Type::spike)
	{
		// if statement that tracks whether the player has hit a spike
		player.setSpikeChecker(true);
		player.setDeathCount();
		player.setPos({ player.getPos().x - 10, player.getPos().y - 30 }); // set position to prevent another collision with the same object after it was already hit during the same life
		return;
	}

	if (entity.type == Entity::Type::coin)
	{
		// if statement that tracks whether the player has hit a coin
		if (entity.getActive())
		{
			// if the coin is active, the player is able to collect it and the coinCount increases
			entity.collectCoin();
			player.healHealth(10);
			coinCount++;
		}
		return;
	}
	

	if (player.bndBox.previousBottom <= entity.bndBox.top
		&& player.bndBox.bottom >= entity.bndBox.top)
	{
		// if the player's bottom bounding box has collided with an entity's top bounding box

		player.setPos({ player.getPos().x, entity.bndBox.top - player.getSize().y });
		
		switch (bounceCount)
		{
		case 0:
			player.setState(Player::State::Bouncing);
			player.setBounceCount();
			player.setVel({ player.getVel().x, -(player.getVel().y) * velMultiplier });
			break;
		case 1: // the fact that there is no break here lets it continue the behavior from the previous case
		case 2:
			if (player.getVel().y < 100.0f)
			{
				// if the player's y velocity is too low, it may as well just stop and set it to a grounded state
				bounceCount = 0;
				player.setVel({ 0.0f, 0.0f });
				player.setState(Player::State::Grounded);
			}
			else
			{
				// if the player's y velocity is too high, it continues to bounce here...
				// ...to prevent it from immediately stopping on the floor (a tiny bit more realistic)
				player.setState(Player::State::Bouncing);
				player.setBounceCount();
				player.setVel({ player.getVel().x, -(player.getVel().y) * velMultiplier });
			}
			break;
		case 3:
			player.setVel({ 0.0f, 0.0f });
			player.setState(Player::State::Grounded);
			break;
		}
		return;
	}

	if (player.bndBox.previousTop > entity.bndBox.bottom
		&& player.bndBox.top <= entity.bndBox.bottom)
	{
		// if the player's top bounding box has collided with an entity's bottom bounding box
		player.setPos({ player.getPos().x, entity.bndBox.bottom + 1 });
		player.setVel({ player.getVel().x, -(player.getVel().y) * velMultiplier });
		return;
	}

	if (player.bndBox.previousLeft > entity.bndBox.right
		&& player.bndBox.left <= entity.bndBox.right)
	{
		// if the player's left bounding box has collided with an entity's right bounding box
		player.setPos({ entity.bndBox.right, player.getPos().y });
		player.setVel({ -(player.getVel().x) * velMultiplier, player.getVel().y });
		return;
	}
	
	if (player.bndBox.previousRight < entity.bndBox.left
		&& player.bndBox.right >= entity.bndBox.left)
	{
		// if the player's right bounding box has collided with an entity's left bounding box
		player.setPos({ entity.bndBox.left - player.getSize().x, player.getPos().y });
		player.setVel({ -(player.getVel().x), player.getVel().y });
		player.setBounceCount();
		return;
	}
}
