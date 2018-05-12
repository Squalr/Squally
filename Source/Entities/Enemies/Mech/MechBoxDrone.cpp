#include "MechBoxDrone.h"

MechBoxDrone* MechBoxDrone::create()
{
	MechBoxDrone* instance = new MechBoxDrone();

	instance->autorelease();

	return instance;
}

MechBoxDrone::MechBoxDrone() : Enemy::Enemy(
	Resources::Entities_Environment_Mech_MechBoxDrone_Animations,
	false)
{
}

MechBoxDrone::~MechBoxDrone()
{
}
