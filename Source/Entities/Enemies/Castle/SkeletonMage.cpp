#include "SkeletonMage.h"

const std::string SkeletonMage::KeyEnemySkeletonMage = "skeleton_mage";

SkeletonMage* SkeletonMage::create()
{
	SkeletonMage* instance = new SkeletonMage();

	instance->autorelease();

	return instance;
}

SkeletonMage::SkeletonMage() : Enemy::Enemy(
	Resources::Entities_Environment_Castle_SkeletonMage_Animations,
	false,
	Size(142.0f, 400.0f),
	0.5f,
	Vec2(0.0f, 40.0f))
{
}

SkeletonMage::~SkeletonMage()
{
}
