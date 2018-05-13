#include "BossSkeletonKing.h"

BossSkeletonKing* BossSkeletonKing::create()
{
	BossSkeletonKing* instance = new BossSkeletonKing();

	instance->autorelease();

	return instance;
}

BossSkeletonKing::BossSkeletonKing() : Enemy::Enemy(
	Resources::Entities_Environment_Obelisk_BossSkeletonKing_Animations,
	false,
	Size(196.0f, 320.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

BossSkeletonKing::~BossSkeletonKing()
{
}
