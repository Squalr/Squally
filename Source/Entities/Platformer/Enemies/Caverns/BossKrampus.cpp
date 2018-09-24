#include "BossKrampus.h"

const std::string BossKrampus::KeyEnemyBossKrampus = "boss_krampus";

BossKrampus* BossKrampus::deserialize(ValueMap* initProperties)
{
	BossKrampus* instance = new BossKrampus(initProperties);

	instance->autorelease();

	return instance;
}

BossKrampus::BossKrampus(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	Resources::Entities_Platformer_Environment_Caverns_Enemies_BossKrampus_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(396.0f, 412.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

BossKrampus::~BossKrampus()
{
}
