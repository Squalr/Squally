#include "YetiWarrior.h"

YetiWarrior* YetiWarrior::create()
{
	YetiWarrior* instance = new YetiWarrior();

	instance->autorelease();

	return instance;
}

YetiWarrior::YetiWarrior() : Enemy::Enemy(
	Resources::Entities_Environment_Snow_YetiWarrior_Animations,
	false)
{
}

YetiWarrior::~YetiWarrior()
{
}
