#include "GoblinShaman.h"

const std::string GoblinShaman::KeyEnemyGoblinShaman = "goblin_shaman";

GoblinShaman* GoblinShaman::deserialize(ValueMap* initProperties)
{
	GoblinShaman* instance = new GoblinShaman(initProperties);

	instance->autorelease();

	return instance;
}

GoblinShaman::GoblinShaman(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	Resources::Entities_Platformer_Environment_Jungle_Enemies_GoblinShaman_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(96.0f, 204.0f),
	0.8f,
	Vec2(0.0f, 0.0f))
{
}

GoblinShaman::~GoblinShaman()
{
}
