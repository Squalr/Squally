#include "SkeletalNecromancer.h"

const std::string SkeletalNecromancer::KeyEnemySkeletalNecromancer = "skeletal_necromancer";

SkeletalNecromancer* SkeletalNecromancer::deserialize(ValueMap* initProperties)
{
	SkeletalNecromancer* instance = new SkeletalNecromancer(initProperties);

	instance->autorelease();

	return instance;
}

SkeletalNecromancer::SkeletalNecromancer(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	Resources::Entities_Platformer_Environment_Caverns_Enemies_SkeletalNecromancer_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(128.0f, 228.0f),
	0.8f,
	Vec2(0.0f, 0.0f))
{
}

SkeletalNecromancer::~SkeletalNecromancer()
{
}
