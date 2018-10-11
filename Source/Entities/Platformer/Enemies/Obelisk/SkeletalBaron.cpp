#include "SkeletalBaron.h"

const std::string SkeletalBaron::KeyEnemySkeletalBaron = "skeletal_baron";

SkeletalBaron* SkeletalBaron::deserialize(ValueMap* initProperties)
{
	SkeletalBaron* instance = new SkeletalBaron(initProperties);

	instance->autorelease();

	return instance;
}

SkeletalBaron::SkeletalBaron(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	Resources::Entities_Platformer_Environment_Obelisk_Enemies_SkeletalBaron_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(472.0f, 368.0f),
	0.8f,
	Vec2(0.0f, 0.0f))
{
}

SkeletalBaron::~SkeletalBaron()
{
}
