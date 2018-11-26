#include "SkeletalKnight.h"

const std::string SkeletalKnight::MapKeyEnemySkeletalKnight = "skeletal_knight";

SkeletalKnight* SkeletalKnight::deserialize(ValueMap* initProperties)
{
	SkeletalKnight* instance = new SkeletalKnight(initProperties);

	instance->autorelease();

	return instance;
}

SkeletalKnight::SkeletalKnight(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Platformer_Environment_Obelisk_Enemies_SkeletalKnight_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(212.0f, 280.0f),
	0.8f,
	Vec2(0.0f, 0.0f))
{
}

SkeletalKnight::~SkeletalKnight()
{
}
