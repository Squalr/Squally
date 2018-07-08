#include "SkeletonPriestess.h"

const std::string SkeletonPriestess::KeyEnemySkeletonPriestess = "skeleton_priestess";

SkeletonPriestess* SkeletonPriestess::deserialize(ValueMap* initProperties)
{
	SkeletonPriestess* instance = new SkeletonPriestess(initProperties);

	instance->autorelease();

	return instance;
}

SkeletonPriestess::SkeletonPriestess(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	Resources::Entities_Platformer_Environment_Obelisk_SkeletonPriestess_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(196.0f, 312.0f),
	0.8f,
	Vec2(0.0f, 0.0f))
{
}

SkeletonPriestess::~SkeletonPriestess()
{
}
