#include "GoblinWarrior.h"

GoblinWarrior* GoblinWarrior::create()
{
	GoblinWarrior* instance = new GoblinWarrior();

	instance->autorelease();

	return instance;
}

GoblinWarrior::GoblinWarrior() : Enemy::Enemy(
	Resources::Entities_Environment_Jungle_GoblinWarrior_Animations,
	false)
{
}

GoblinWarrior::~GoblinWarrior()
{
}
