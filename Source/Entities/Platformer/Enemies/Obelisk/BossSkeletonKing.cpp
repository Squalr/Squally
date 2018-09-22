#include "BossSkeletonKing.h"

const std::string BossSkeletonKing::KeyEnemyBossSkeletonKing = "boss_skeleton_king";

BossSkeletonKing* BossSkeletonKing::deserialize(ValueMap* initProperties)
{
	BossSkeletonKing* instance = new BossSkeletonKing(initProperties);

	instance->autorelease();

	return instance;
}

BossSkeletonKing::BossSkeletonKing(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	Resources::Entities_Platformer_Environment_Obelisk_Enemies_BossSkeletonKing_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(196.0f, 320.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

BossSkeletonKing::~BossSkeletonKing()
{
}
