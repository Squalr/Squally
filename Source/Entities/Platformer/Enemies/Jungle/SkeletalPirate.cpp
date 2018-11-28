#include "SkeletalPirate.h"

const std::string SkeletalPirate::MapKeyEnemySkeletalPirate = "skeletal_pirate";

SkeletalPirate* SkeletalPirate::deserialize(ValueMap* initProperties)
{
	SkeletalPirate* instance = new SkeletalPirate(initProperties);

	instance->autorelease();

	return instance;
}

SkeletalPirate::SkeletalPirate(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Environment_Jungle_Enemies_SkeletalPirate_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(284.0f, 256.0f),
	1.0f,
	Vec2(0.0f, -112.0f))
{
}

SkeletalPirate::~SkeletalPirate()
{
}
