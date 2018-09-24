#include "BossSanta.h"

const std::string BossSanta::KeyEnemyBossSanta = "boss_santa";

BossSanta* BossSanta::deserialize(ValueMap* initProperties)
{
	BossSanta* instance = new BossSanta(initProperties);

	instance->autorelease();

	return instance;
}

BossSanta::BossSanta(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	Resources::Entities_Platformer_Environment_Snow_Enemies_BossSanta_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(420.0f, 452.0f),
	0.7f,
	Vec2(0.0f, 0.0f))
{
}

BossSanta::~BossSanta()
{
}
