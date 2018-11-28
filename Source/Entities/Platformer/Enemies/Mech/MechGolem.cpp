#include "MechGolem.h"

const std::string MechGolem::MapKeyEnemyMechGolem = "mech_golem";

MechGolem* MechGolem::deserialize(ValueMap* initProperties)
{
	MechGolem* instance = new MechGolem(initProperties);

	instance->autorelease();

	return instance;
}

MechGolem::MechGolem(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Environment_Mech_Enemies_MechGolem_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(640.0f, 720.0f),
	0.7f,
	Vec2(-48.0f, 0.0f))
{
}

MechGolem::~MechGolem()
{
}
