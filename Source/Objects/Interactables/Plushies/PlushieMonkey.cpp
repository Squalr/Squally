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

	this->registerHackables();

	this->chest->contentNode->addChild(this->sprite);
}

PlushieMonkey::~PlushieMonkey()
{
}

void PlushieMonkey::update(float dt)
{

}

void PlushieMonkey::registerHackables()
{
	Plushie::registerHackables();

	this->registerData(HackableData::create("Key", this->chest, &typeid((int)this->chest)));
	this->registerCode(HackableCode::create("Test", this->chest, 10));
}
