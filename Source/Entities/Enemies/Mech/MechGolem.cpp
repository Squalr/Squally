#include "MechGolem.h"

MechGolem* MechGolem::create()
{
	MechGolem* instance = new MechGolem();

	instance->autorelease();

	return instance;
}

MechGolem::MechGolem() : Enemy::Enemy(
	Resources::Entities_Environment_Mech_MechGolem_Animations,
	false,
	Size(640.0f, 720.0f),
	0.7f,
	Vec2(-48.0f, 0.0f))
{
}

MechGolem::~MechGolem()
{
}
