#include "SkeletonMage.h"

SkeletonMage* SkeletonMage::create()
{
	SkeletonMage* instance = new SkeletonMage();

	instance->autorelease();

	return instance;
}

SkeletonMage::SkeletonMage() : Enemy::Enemy(
	Resources::Entities_Environment_Castle_SkeletonMage_Animations,
	false)
{
}

SkeletonMage::~SkeletonMage()
{
}
