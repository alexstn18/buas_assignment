#include "Entity.h"

Entity::Entity(Type type, int ID) :
	type{ type }, ID{ ID } {}

void Entity::Update()
{
	bndBox.left = pos.x;
	bndBox.right = pos.x + size.x;
	bndBox.top = pos.y;
	bndBox.bottom = pos.y + size.y;
}

void Entity::Render(Surface& screen)
{
#ifdef _DEBUG
	screen.Box(bndBox.left, bndBox.top, bndBox.right, bndBox.bottom, 0xFF0000);
#endif
}

void Entity::setPos(vec2 pos)
{
	this->pos = pos;
}

void Entity::setSize(vec2 size)
{
	this->size = size;
}
