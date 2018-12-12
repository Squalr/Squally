#include "SkeletalNecromancer.h"

const std::string SkeletalNecromancer::MapKeyEnemySkeletalNecromancer = "skeletal_necromancer";

SkeletalNecromancer* SkeletalNecromancer::deserialize(ValueMap* initProperties)
{
	SkeletalNecromancer* instance = new SkeletalNecromancer(initProperties);

	instance->autorelease();

	return instance;
}

SkeletalNecromancer::SkeletalNecromancer(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Environment_Caverns_Enemies_SkeletalNecromancer_Animations,
	PlatformerCollisionType::Enemy,
	Size(128.0f, 228.0f),
	0.8f,
	Vec2(0.0f, 0.0f))
{
}

SkeletalNecromancer::~SkeletalNecromancer()
{
}
