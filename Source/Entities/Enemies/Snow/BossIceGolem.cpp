#include "BossIceGolem.h"

const std::string BossIceGolem::KeyEnemyBossIceGolem = "boss_ice_golem";

BossIceGolem* BossIceGolem::deserialize(ValueMap* initProperties)
{
	BossIceGolem* instance = new BossIceGolem(initProperties);

	instance->autorelease();

	return instance;
}

BossIceGolem::BossIceGolem(ValueMap* initProperties) : Enemy(initProperties,
	Resources::Entities_Platformer_Environment_Snow_BossIceGolem_Animations,
	false,
	Size(420.0f, 420.0f),
	0.7f,
	Vec2(0.0f, 0.0f))
{
}

BossIceGolem::~BossIceGolem()
{
}
