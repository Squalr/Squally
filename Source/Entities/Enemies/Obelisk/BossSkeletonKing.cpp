#include "BossSkeletonKing.h"

BossSkeletonKing* BossSkeletonKing::create()
{
	BossSkeletonKing* instance = new BossSkeletonKing();

	instance->autorelease();

	return instance;
}

BossSkeletonKing::BossSkeletonKing() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

BossSkeletonKing::~BossSkeletonKing()
{
}
