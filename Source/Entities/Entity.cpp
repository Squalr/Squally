#include "Entity.h"
#include "Resources.h"
#include "cocos2d.h"

using namespace cocos2d;

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
