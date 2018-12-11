#include "MechDog.h"

const std::string MechDog::MapKeyEnemyMechDog = "mech_dog";

MechDog* MechDog::deserialize(ValueMap* initProperties)
{
	MechDog* instance = new MechDog(initProperties);

	instance->autorelease();

	return instance;
}

MechDog::MechDog(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Environment_Mech_Enemies_MechDog_Animations,
	PlatformerCollisionType::Enemy,
	Size(540.0f, 340.0f),
	0.7f,
	Vec2(-64.0f, 32.0f))
{
}

MechDog::~MechDog()
{
}
