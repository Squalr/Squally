#include "MechBoxDrone.h"

MechBoxDrone* MechBoxDrone::create()
{
	MechBoxDrone* instance = new MechBoxDrone();

	instance->autorelease();

	return instance;
}

MechBoxDrone::MechBoxDrone() : Enemy::Enemy(
	Resources::Entities_Environment_Mech_MechBoxDrone_Animations,
	false,
	Size(224.0f, 278.0f),
	0.7f,
	Vec2(0.0f, 0.0f))
{
}

MechBoxDrone::~MechBoxDrone()
{
}
