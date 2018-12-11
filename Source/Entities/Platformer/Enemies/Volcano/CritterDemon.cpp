#include "CritterDemon.h"

const std::string CritterDemon::MapKeyEnemyCritterDemon = "critter_demon";

CritterDemon* CritterDemon::deserialize(ValueMap* initProperties)
{
	CritterDemon* instance = new CritterDemon(initProperties);

	instance->autorelease();

	return instance;
}

CritterDemon::CritterDemon(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Environment_Volcano_Enemies_CritterDemon_Animations,
	PlatformerCollisionType::Enemy,
	Size(188.0f, 160.0f),
	0.7f,
	Vec2(0.0f, 0.0f))
{
}

CritterDemon::~CritterDemon()
{
}
