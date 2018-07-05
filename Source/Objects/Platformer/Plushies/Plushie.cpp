#include "Plushie.h"

Plushie::Plushie(ValueMap* initProperties) : HackableObject(initProperties)
{
	this->sprite = Node::create();
	this->chest = Chest::create(initProperties, this->sprite);

	this->registerHackables();

	chest->close();

	this->addChild(this->chest);
}

Plushie::~Plushie()
{
}

void Plushie::update(float dt)
{

}

void Plushie::registerHackables()
{
	this->size = chest->size;
	// this->setButtonOffset(Vec2(-24.0f, 96.0f));
}
