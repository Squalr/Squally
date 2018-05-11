#include "MechGuard.h"

MechGuard* MechGuard::create()
{
	MechGuard* instance = new MechGuard();

	instance->autorelease();

	return instance;
}

MechGuard::MechGuard() : Enemy::Enemy(
	Resources::Entities_Environment_Mech_MechGuard_Animations,
	false)
{
}

MechGuard::~MechGuard()
{
}
