#include "BossWitch.h"

const std::string BossWitch::KeyEnemyBossWitch = "boss_witch";

BossWitch* BossWitch::deserialize(ValueMap* initProperties)
{
	BossWitch* instance = new BossWitch(initProperties);

	instance->autorelease();

	return instance;
}

BossWitch::BossWitch(ValueMap* initProperties) : Enemy(initProperties,
	Resources::Entities_Platformer_Environment_Castle_BossWitch_Animations,
	false,
	Size(360.0f, 420.0f),
	0.9f,
	Vec2(0.0f, 0.0f))
{
}

BossWitch::~BossWitch()
{
}
