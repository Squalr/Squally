#include "Plushie.h"

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
	HackableObject::update(dt);
}

void Plushie::registerHackables()
{
	this->size = Vec2(256.0f, 256.0f);// this->chest->chestClosedSprite->getContentSize();
}

Vec2 Plushie::getButtonOffset()
{
	return Vec2(-24.0f, 96.0f);
}
