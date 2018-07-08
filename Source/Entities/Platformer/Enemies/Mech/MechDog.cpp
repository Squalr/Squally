#include "MechDog.h"

const std::string MechDog::KeyEnemyMechDog = "mech_dog";

MechDog* MechDog::deserialize(ValueMap* initProperties)
{
	MechDog* instance = new MechDog(initProperties);

	instance->autorelease();

	return instance;
}

MechDog::MechDog(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	Resources::Entities_Platformer_Environment_Mech_MechDog_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(540.0f, 340.0f),
	0.7f,
	Vec2(-64.0f, 32.0f))
{
}

MechDog::~MechDog()
{
}
