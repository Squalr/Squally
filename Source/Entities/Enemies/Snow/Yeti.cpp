#include "Yeti.h"

Yeti* Yeti::create()
{
	Yeti* instance = new Yeti();

	instance->autorelease();

	return instance;
}

Yeti::Yeti() : Enemy::Enemy(
	Resources::Entities_Environment_Snow_Yeti_Animations,
	false)
{
}

Yeti::~Yeti()
{
}
