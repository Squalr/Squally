#include "TigerMan.h"

const std::string TigerMan::KeyEnemyTigerMan = "tiger_man";

TigerMan* TigerMan::deserialize(ValueMap* initProperties)
{
	TigerMan* instance = new TigerMan(initProperties);

	instance->autorelease();

	return instance;
}

TigerMan::TigerMan(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	Resources::Entities_Platformer_Environment_Ruins_Enemies_TigerMan_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(256.0f, 308.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

TigerMan::~TigerMan()
{
}
