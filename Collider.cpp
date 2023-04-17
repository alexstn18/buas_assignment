#include "Collider.h"

constexpr float velMultiplier = 0.8f;

void Collider::CheckCollisions(Player& player, Entity& entity)
{
	if (player.checkState(Player::State::Grounded)) return;
	if (BoundingBox::AABB(player.bndBox, entity.bndBox))
	{
		EdgeCheck(player, entity);
	}
}

void Collider::EdgeCheck(Player& player, Entity& entity)
{
	int bounceCount = player.getBounceCount();
	
	if (entity.type == Entity::Type::portal)
	{
		player.setPortalChecker(true);
		return;
	}

	if (entity.type == Entity::Type::spike)
	{
		player.setSpikeChecker(true);
		player.setDeathCount();
	}
	
	if (player.bndBox.previousBottom < entity.bndBox.top 
		&& player.bndBox.bottom >= entity.bndBox.top) 
	{
		player.setPos({ player.getPos().x, entity.bndBox.top - player.getSize().y });
		switch (bounceCount)
		{
		default:
			player.setState(Player::State::Bouncing);
			player.setBounceCount();
			player.setVel({ player.getVel().x, -(player.getVel().y) * velMultiplier });
			break;
		case 1:
			player.setVel({ 0.0f, 0.0f });
			player.setState(Player::State::Grounded);
			break;
		}
		player.setSquished(true);
		return;
	}

	if (player.bndBox.previousTop > entity.bndBox.bottom
		&& player.bndBox.top <= entity.bndBox.bottom)
	{
		player.setPos({ player.getPos().x, entity.bndBox.bottom + 1 });
		player.setVel({ player.getVel().x, -(player.getVel().y) * velMultiplier });
		return;
	}

	if (player.bndBox.previousLeft > entity.bndBox.right
		&& player.bndBox.left <= entity.bndBox.right)
	{
		player.setPos({ entity.bndBox.right, player.getPos().y });
		player.setVel({ -(player.getVel().x) * velMultiplier, player.getVel().y });
		return;
	}

	if (player.bndBox.previousRight < entity.bndBox.left
		&& player.bndBox.right >= entity.bndBox.left)
	{
		player.setPos({ entity.bndBox.left - player.getSize().x, player.getPos().y});
		player.setVel({ -(player.getVel().x), player.getVel().y });
		player.setBounceCount();
		return;
	}

}