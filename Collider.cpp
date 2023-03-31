#include "Collider.h"

void Collider::CheckCollisions(Player& player, Entity& entity)
{
	if (BoundingBox::AABB(player.bndBox, entity.bndBox))
	{
		EdgeCheck(player, entity);
	}
}

void Collider::EdgeCheck(Player& player, Entity& entity)
{
	// thing (entity) does not move in this example. but should also use previous position for the first check.
	if (player.bndBox.previousBottom < entity.bndBox.top // Reverse check of IsOverlap (no overlap) using previous position.
		&& player.bndBox.bottom >= entity.bndBox.top) // Same check as in IsOverlap
	{
		if (player.getVel().x > 0)
		{
			player.setState(Player::State::Bouncing);
		}
		else
		{
			player.setState(Player::State::Grounded);
		}
		player.setPos({ player.getPos().x, entity.bndBox.top - player.getSize().y });
		switch (player.getBounceCount())
		{
		case 0:
			player.setVel({ player.getVel().x, -(player.getVel().y) / 1.5f });
			break;
		case 1:
			player.setVel({ player.getVel().x, -(player.getVel().y) / 1.75f });
			break;
		case 2:
			player.setVel({ player.getVel().x, -(player.getVel().y) / 2.0f });
			break;
		default:
			player.setVel({ player.getVel().x, 0.0f });
			player.setState(Player::State::Grounded);
			// velocity.x = 0;
			break;
		}
		player.setBounceCount({ player.getBounceCount() + 1 });
		return;
	}

	if (player.bndBox.previousTop > entity.bndBox.bottom
		&& player.bndBox.top <= entity.bndBox.bottom)
	{
		player.setPos({ player.getPos().x, entity.bndBox.bottom - player.getSize().y });
		player.setVel({ player.getVel().x, player.getVel().y / 1.75f });
		return;
	}

	if (player.bndBox.previousLeft > entity.bndBox.right
		&& player.bndBox.left <= entity.bndBox.right)
	{
		player.setPos({ player.getPos().x, entity.bndBox.left - player.getSize().y });
		// player.setVel({ player.getVel().x / 1.5f, player.getVel().y });
		return;
	}

	if (player.bndBox.previousRight < entity.bndBox.left
		&& player.bndBox.right >= entity.bndBox.left)
	{
		player.setPos({ player.getPos().x, entity.bndBox.right - player.getSize().y });
		// player.setVel({ -(player.getVel().x) / 1.5f, player.getVel().y });
		return;
	}
}
