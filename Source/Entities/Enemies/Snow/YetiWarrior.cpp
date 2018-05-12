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
	Size(256.0f, 512.0f),
	0.6f,
	Vec2(0.0f, -256.0f))
{
}

YetiWarrior::~YetiWarrior()
{
}
