#include "SkeletonArcher.h"

SkeletonArcher* SkeletonArcher::create()
{
	SkeletonArcher* instance = new SkeletonArcher();

	instance->autorelease();

	return instance;
}

SkeletonArcher::SkeletonArcher() : Enemy::Enemy(
	Resources::Entities_Environment_Volcano_BossDemonKing_Animations,
	false)
{
}

SkeletonArcher::~SkeletonArcher()
{
}
