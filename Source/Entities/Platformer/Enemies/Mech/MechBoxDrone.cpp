#include "MechBoxDrone.h"

const std::string MechBoxDrone::MapKeyEnemyMechBoxDrone = "mech_box_drone";

MechBoxDrone* MechBoxDrone::deserialize(ValueMap* initProperties)
{
	MechBoxDrone* instance = new MechBoxDrone(initProperties);

	instance->autorelease();

	return instance;
}

MechBoxDrone::MechBoxDrone(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Platformer_Environment_Mech_Enemies_MechBoxDrone_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(224.0f, 278.0f),
	0.7f,
	Vec2(0.0f, 0.0f))
{
}

MechBoxDrone::~MechBoxDrone()
{
}
