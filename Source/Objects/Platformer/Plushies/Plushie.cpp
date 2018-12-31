#include "Plushie.h"

#include "Objects/Platformer/Chest.h"

using namespace cocos2d;

Plushie::Plushie(ValueMap* initProperties) : HackableObject(initProperties)
{
	this->sprite = Node::create();
	this->chest = Chest::create(this->sprite);

	this->registerHackables();

	chest->close();

	this->addChild(this->chest);
}

Plushie::~Plushie()
{
}

void Plushie::update(float dt)
{
	super::update(dt);
}

void Plushie::registerHackables()
{
}

Vec2 Plushie::getButtonOffset()
{
	return Vec2(-24.0f, 96.0f);
}
