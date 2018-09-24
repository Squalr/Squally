#include "BossRhinoman.h"

const std::string BossRhinoman::KeyEnemyBossRhinoman = "boss_rhinoman";

BossRhinoman* BossRhinoman::deserialize(ValueMap* initProperties)
{
	BossRhinoman* instance = new BossRhinoman(initProperties);

	instance->autorelease();

	return instance;
}

BossRhinoman::BossRhinoman(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	Resources::Entities_Platformer_Environment_Jungle_Enemies_BossRhinoman_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(592.0f, 592.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

BossRhinoman::~BossRhinoman()
{
}
