#include "Plushie.h"

Plushie::Plushie()
{
	this->chest = Chest::create();

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
	this->setPreviewImage(Resources::Objects_ChestClosed);
	this->setButtonOffset(Vec2(-24.0f, 96.0f));
}
