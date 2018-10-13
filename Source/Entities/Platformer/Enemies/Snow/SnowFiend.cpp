#include "SnowFiend.h"

const std::string SnowFiend::MapKeyEnemySnowFiend = "snow_fiend";

SnowFiend* SnowFiend::deserialize(ValueMap* initProperties)
{
	SnowFiend* instance = new SnowFiend(initProperties);

	instance->autorelease();

	return instance;
}

SnowFiend::SnowFiend(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	Resources::Entities_Platformer_Environment_Snow_Enemies_SnowFiend_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(420.0f, 420.0f),
	0.7f,
	Vec2(0.0f, 0.0f))
{
}

SnowFiend::~SnowFiend()
{
}
