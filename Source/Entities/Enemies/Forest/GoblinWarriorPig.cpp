#include "GoblinWarriorPig.h"

GoblinWarriorPig* GoblinWarriorPig::create()
{
	GoblinWarriorPig* instance = new GoblinWarriorPig();

	instance->autorelease();

	return instance;
}

GoblinWarriorPig::GoblinWarriorPig() : Enemy::Enemy(
	Resources::Entities_Environment_Forest_GoblinWarriorPig_Animations,
	false)
{
}

GoblinWarriorPig::~GoblinWarriorPig()
{
}
