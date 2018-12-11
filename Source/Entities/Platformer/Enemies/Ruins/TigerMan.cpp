#include "TigerMan.h"

const std::string TigerMan::MapKeyEnemyTigerMan = "tiger_man";

TigerMan* TigerMan::deserialize(ValueMap* initProperties)
{
	TigerMan* instance = new TigerMan(initProperties);

	instance->autorelease();

	return instance;
}

TigerMan::TigerMan(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Environment_Ruins_Enemies_TigerMan_Animations,
	PlatformerCollisionType::Enemy,
	Size(256.0f, 308.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

TigerMan::~TigerMan()
{
}
