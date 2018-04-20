#include "Plushie.h"

Plushie::Plushie()
{

	this->registerHackables();
}

Plushie::~Plushie()
{
}

void Plushie::update(float dt)
{

}

void Plushie::open()
{

}

void Plushie::registerHackables()
{
	this->setPreviewImage(Resources::Objects_WarpGateOpen);
	this->setButtonOffset(Vec2(0, -128.0f));
}
