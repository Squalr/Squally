#include "Entity.h"

Entity::Entity()
{
	this->scheduleUpdate();
}


Entity::~Entity()
{
}

void Entity::onEnter()
{
	Node::onEnter();
}

void Entity::update(float dt)
{
	Node::update(dt);
}

float Entity::GetWidth()
{
	return this->sprite->getContentSize().width;
}

float Entity::GetHeight()
{
	return this->sprite->getContentSize().height;
}
