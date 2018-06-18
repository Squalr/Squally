#include "SkeletonPriestess.h"

const std::string SkeletonPriestess::KeyEnemySkeletonPriestess = "skeleton_priestess";

SkeletonPriestess* SkeletonPriestess::create()
{
	SkeletonPriestess* instance = new SkeletonPriestess();

	instance->autorelease();

	return instance;
}

SkeletonPriestess::SkeletonPriestess() : Enemy::Enemy(
	Resources::Entities_Environment_Obelisk_SkeletonPriestess_Animations,
	false,
	Size(196.0f, 312.0f),
	0.8f,
	Vec2(0.0f, 0.0f))
{
}

SkeletonPriestess::~SkeletonPriestess()
{
}
