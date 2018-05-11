#include "MechDog.h"

MechDog* MechDog::create()
{
	MechDog* instance = new MechDog();

	instance->autorelease();

	return instance;
}

MechDog::MechDog() : Enemy::Enemy(
	Resources::Entities_Environment_Mech_MechDog_Animations,
	false)
{
}

MechDog::~MechDog()
{
}
