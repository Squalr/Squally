#include "BossEgyptianGoddess.h"

const std::string BossEgyptianGoddess::KeyEnemyBossEgyptianGoddess = "boss_egyptian_goddess";

BossEgyptianGoddess* BossEgyptianGoddess::deserialize(ValueMap* initProperties)
{
	BossEgyptianGoddess* instance = new BossEgyptianGoddess(initProperties);

	instance->autorelease();

	return instance;
}

BossEgyptianGoddess::BossEgyptianGoddess(ValueMap* initProperties) : Enemy(initProperties,
	Resources::Entities_Environment_Ruins_BossEgyptianGoddess_Animations,
	false,
	Size(128.0f, 272.0f),
	0.8f,
	Vec2(0.0f, 0.0f))
{
}

BossEgyptianGoddess::~BossEgyptianGoddess()
{
}
