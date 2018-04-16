#include "BossSkeletonKing.h"

BossSkeletonKing* BossSkeletonKing::create()
{
	BossSkeletonKing* instance = new BossSkeletonKing();

	instance->autorelease();

	return instance;
}

BossSkeletonKing::BossSkeletonKing() : Enemy::Enemy(
	Resources::Entities_Environment_Volcano_BossDemonKing_Animations,
	"BossDemonKing",
	false)
{
}

BossSkeletonKing::~BossSkeletonKing()
{
}
