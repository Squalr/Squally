#include "BossSkeletonKing.h"

BossSkeletonKing* BossSkeletonKing::create()
{
	BossSkeletonKing* instance = new BossSkeletonKing();

	instance->autorelease();

	return instance;
}

BossSkeletonKing::BossSkeletonKing() : Enemy::Enemy(
	Resources::Entities_Environment_Obelisk_BossSkeletonKing_Animations,
	false)
{
}

BossSkeletonKing::~BossSkeletonKing()
{
}
