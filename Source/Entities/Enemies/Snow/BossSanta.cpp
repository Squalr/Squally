#include "BossSanta.h"

const std::string BossSanta::KeyEnemyBossSanta = "boss_santa";

BossSanta* BossSanta::deserialize(ValueMap* initProperties)
{
	BossSanta* instance = new BossSanta(initProperties);

	instance->autorelease();

	return instance;
}

BossSanta::BossSanta(ValueMap* initProperties) : Enemy(initProperties,
	Resources::Entities_Environment_Snow_BossSanta_Animations,
	false,
	Size(420.0f, 452.0f),
	0.7f,
	Vec2(0.0f, 0.0f))
{
}

BossSanta::~BossSanta()
{
}
