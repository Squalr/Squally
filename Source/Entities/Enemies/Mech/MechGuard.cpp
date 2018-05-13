#include "MechGuard.h"

MechGuard* MechGuard::create()
{
	MechGuard* instance = new MechGuard();

	instance->autorelease();

	return instance;
}

MechGuard::MechGuard() : Enemy::Enemy(
	Resources::Entities_Environment_Mech_MechGuard_Animations,
	false,
	Size(472.0f, 596.0f),
	0.3f,
	Vec2(-24.0f, -298.0f))
{
}

MechGuard::~MechGuard()
{
}
