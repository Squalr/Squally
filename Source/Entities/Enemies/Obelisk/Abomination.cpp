#include "Abomination.h"

Abomination* Abomination::create()
{
	Abomination* instance = new Abomination();

	instance->autorelease();

	return instance;
}

Abomination::Abomination() : Enemy::Enemy(
	Resources::Entities_Environment_Obelisk_Abomination_Animations,
	false)
{
}

Abomination::~Abomination()
{
}
