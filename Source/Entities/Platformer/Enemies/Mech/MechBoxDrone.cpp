#include "MechBoxDrone.h"

const std::string MechBoxDrone::KeyEnemyMechBoxDrone = "mech_box_drone";

MechBoxDrone* MechBoxDrone::deserialize(ValueMap* initProperties)
{
	MechBoxDrone* instance = new MechBoxDrone(initProperties);

	instance->autorelease();

	return instance;
}

MechBoxDrone::MechBoxDrone(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	Resources::Entities_Platformer_Environment_Mech_MechBoxDrone_Animations,
	false,
	Size(224.0f, 278.0f),
	0.7f,
	Vec2(0.0f, 0.0f))
{
}

MechBoxDrone::~MechBoxDrone()
{
}
