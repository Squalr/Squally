#include "BossSkeletonKing.h"

const std::string BossSkeletonKing::KeyEnemyBossSkeletonKing = "boss_skeleton_king";

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
