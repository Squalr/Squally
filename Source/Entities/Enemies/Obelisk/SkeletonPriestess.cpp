#include "SkeletonPriestess.h"

SkeletonPriestess* SkeletonPriestess::create()
{
	SkeletonPriestess* instance = new SkeletonPriestess();

	instance->autorelease();

	return instance;
}

SkeletonPriestess::SkeletonPriestess() : Enemy::Enemy(
	Resources::Entities_Environment_Volcano_BossDemonKing_Animations,
	false)
{
}

SkeletonPriestess::~SkeletonPriestess()
{
}
