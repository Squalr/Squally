#include "YetiWarrior.h"

YetiWarrior* YetiWarrior::create()
{
	YetiWarrior* instance = new YetiWarrior();

	instance->autorelease();

	return instance;
}

YetiWarrior::YetiWarrior() : Enemy::Enemy(
	Resources::Entities_Environment_Snow_YetiWarrior_Animations,
	false,
	Size(380.0f, 572.0f),
	0.4f,
	Vec2(24.0f, -280.0f))
{
}

YetiWarrior::~YetiWarrior()
{
}
