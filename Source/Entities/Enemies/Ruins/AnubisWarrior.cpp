#include "AnubisWarrior.h"

AnubisWarrior* AnubisWarrior::create()
{
	AnubisWarrior* instance = new AnubisWarrior();

	instance->autorelease();

	return instance;
}

AnubisWarrior::AnubisWarrior() : Enemy::Enemy(
	Resources::Entities_Environment_Ruins_AnubisWarrior_Animations,
	false,
	Size(256.0f, 292.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

AnubisWarrior::~AnubisWarrior()
{
}
