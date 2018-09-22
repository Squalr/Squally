#include "SkeletonKnight.h"

const std::string SkeletonKnight::KeyEnemySkeletonKnight = "skeleton_knight";

SkeletonKnight* SkeletonKnight::deserialize(ValueMap* initProperties)
{
	SkeletonKnight* instance = new SkeletonKnight(initProperties);

	instance->autorelease();

	return instance;
}

SkeletonKnight::SkeletonKnight(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	Resources::Entities_Platformer_Environment_Obelisk_Enemies_SkeletonKnight_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(212.0f, 280.0f),
	0.8f,
	Vec2(0.0f, 0.0f))
{
}

SkeletonKnight::~SkeletonKnight()
{
}
