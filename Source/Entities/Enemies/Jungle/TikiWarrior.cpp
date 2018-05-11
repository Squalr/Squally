#include "TikiWarrior.h"

TikiWarrior* TikiWarrior::create()
{
	TikiWarrior* instance = new TikiWarrior();

	instance->autorelease();

	return instance;
}

TikiWarrior::TikiWarrior() : Enemy::Enemy(
	Resources::Entities_Environment_Jungle_TikiWarrior_Animations,
	false)
{
}

TikiWarrior::~TikiWarrior()
{
}
