#include "Animal.h"

#include "cocos/2d/CCSprite.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

Animal::Animal(ValueMap& initProperties) : HackableObject(initProperties)
{
	this->spriteNode = Node::create();
	this->cage = Sprite::create(ObjectResources::ChestBaseFront);

	this->addChild(this->spriteNode);
	this->addChild(this->cage);
}

Animal::~Animal()
{
}

void Animal::update(float dt)
{
	super::update(dt);
}

Vec2 Animal::getButtonOffset()
{
	return Vec2(-24.0f, 96.0f);
}
