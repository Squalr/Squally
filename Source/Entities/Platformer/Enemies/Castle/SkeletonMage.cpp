#include "SkeletonMage.h"

const std::string SkeletonMage::KeyEnemySkeletonMage = "skeleton_mage";

SkeletonMage* SkeletonMage::deserialize(ValueMap* initProperties)
{
	SkeletonMage* instance = new SkeletonMage(initProperties);

	instance->autorelease();

	return instance;
}

SkeletonMage::SkeletonMage(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	Resources::Entities_Platformer_Environment_Castle_SkeletonMage_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(142.0f, 400.0f),
	0.5f,
	Vec2(0.0f, 40.0f))
{
}

SkeletonMage::~SkeletonMage()
{
}
