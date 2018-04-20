#include "PlushieMonkey.h"

PlushieMonkey* PlushieMonkey::create()
{
	PlushieMonkey* instance = new PlushieMonkey();

	instance->autorelease();

	return instance;
}

PlushieMonkey::PlushieMonkey()
{
	this->sprite = Sprite::create(Resources::Plushies_MONKEY);
}

PlushieMonkey::~PlushieMonkey()
{
}

void Plushie::update(float dt)
{

}

