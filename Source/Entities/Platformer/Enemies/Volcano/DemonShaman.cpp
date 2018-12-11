#include "DemonShaman.h"

const std::string DemonShaman::MapKeyEnemyDemonShaman = "demon_shaman";

DemonShaman* DemonShaman::deserialize(ValueMap* initProperties)
{
	DemonShaman* instance = new DemonShaman(initProperties);

	instance->autorelease();

	return instance;
}

DemonShaman::DemonShaman(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Environment_Volcano_Enemies_DemonShaman_Animations,
	PlatformerCollisionType::Enemy,
	Size(212.0f, 280.0f),
	0.65f,
	Vec2(0.0f, 0.0f))
{
}

DemonShaman::~DemonShaman()
{
}
