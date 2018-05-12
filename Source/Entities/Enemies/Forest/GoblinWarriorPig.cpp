#include "GoblinWarriorPig.h"

GoblinWarriorPig* GoblinWarriorPig::create()
{
	GoblinWarriorPig* instance = new GoblinWarriorPig();

	instance->autorelease();

	return instance;
}

GoblinWarriorPig::GoblinWarriorPig() : Enemy::Enemy(
	Resources::Entities_Environment_Forest_GoblinWarriorPig_Animations,
	false,
	Size(128.0f, 296.0f),
	0.8f,
	Vec2(0.0f, 0.0f))
{
}

GoblinWarriorPig::~GoblinWarriorPig()
{
}
