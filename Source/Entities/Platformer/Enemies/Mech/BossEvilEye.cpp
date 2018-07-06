#include "BossEvilEye.h"

const std::string BossEvilEye::KeyEnemyBossEvilEye = "boss_evil_eye";

BossEvilEye* BossEvilEye::deserialize(ValueMap* initProperties)
{
	BossEvilEye* instance = new BossEvilEye(initProperties);

	instance->autorelease();

	return instance;
}

BossEvilEye::BossEvilEye(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	Resources::Entities_Platformer_Environment_Mech_BossEvilEye_Animations,
	false,
	Size(720.0f, 840.0f),
	0.6f,
	Vec2(0.0f, 0.0f))
{
}

BossEvilEye::~BossEvilEye()
{
}
