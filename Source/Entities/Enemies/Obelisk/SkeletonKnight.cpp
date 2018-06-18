#include "SkeletonKnight.h"

const std::string SkeletonKnight::KeyEnemySkeletonKnight = "skeleton_knight";

SkeletonKnight* SkeletonKnight::deserialize(ValueMap* initProperties)
{
	SkeletonKnight* instance = new SkeletonKnight(initProperties);

	instance->autorelease();

	return instance;
}

SkeletonKnight::SkeletonKnight(ValueMap* initProperties) : Enemy(initProperties,
	Resources::Entities_Environment_Obelisk_SkeletonKnight_Animations,
	false,
	Size(212.0f, 280.0f),
	0.8f,
	Vec2(0.0f, 0.0f))
{
}

SkeletonKnight::~SkeletonKnight()
{
}
