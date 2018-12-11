#include "GoblinShaman.h"

const std::string GoblinShaman::MapKeyEnemyGoblinShaman = "goblin_shaman";

GoblinShaman* GoblinShaman::deserialize(ValueMap* initProperties)
{
	GoblinShaman* instance = new GoblinShaman(initProperties);

	instance->autorelease();

	return instance;
}

GoblinShaman::GoblinShaman(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Environment_Jungle_Enemies_GoblinShaman_Animations,
	PlatformerCollisionType::Enemy,
	Size(96.0f, 204.0f),
	0.8f,
	Vec2(0.0f, 0.0f))
{
}

GoblinShaman::~GoblinShaman()
{
}
