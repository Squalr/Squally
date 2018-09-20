#include "BossJack.h"

const std::string BossJack::KeyEnemyBossJack = "jack";

BossJack* BossJack::deserialize(ValueMap* initProperties)
{
	BossJack* instance = new BossJack(initProperties);

	instance->autorelease();

	return instance;
}

BossJack::BossJack(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	Resources::Entities_Platformer_Environment_Castle_BossJack_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(432.0f, 768.0f),
	0.25f,
	Vec2(0.0f, 0.0f))
{
}

BossJack::~BossJack()
{
}
