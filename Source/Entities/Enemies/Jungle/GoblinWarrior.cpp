#include "GoblinWarrior.h"

GoblinWarrior* GoblinWarrior::create()
{
	GoblinWarrior* instance = new GoblinWarrior();

	instance->autorelease();

	return instance;
}

GoblinWarrior::GoblinWarrior() : Enemy::Enemy(
	Resources::Entities_Environment_Jungle_GoblinWarrior_Animations,
	false,
	Size(312.0f, 512.0f),
	0.35f,
	Vec2(0.0f, -224.0f))
{
}

GoblinWarrior::~GoblinWarrior()
{
}
