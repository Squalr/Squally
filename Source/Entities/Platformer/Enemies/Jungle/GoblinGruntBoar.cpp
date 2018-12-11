#include "GoblinGruntBoar.h"

const std::string GoblinGruntBoar::MapKeyEnemyGoblinGruntBoar = "goblin_grunt_boar";

GoblinGruntBoar* GoblinGruntBoar::deserialize(ValueMap* initProperties)
{
	GoblinGruntBoar* instance = new GoblinGruntBoar(initProperties);

	instance->autorelease();

	return instance;
}

GoblinGruntBoar::GoblinGruntBoar(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Environment_Jungle_Enemies_GoblinGruntBoar_Animations,
	PlatformerCollisionType::Enemy,
	Size(128.0f, 296.0f),
	0.8f,
	Vec2(0.0f, 0.0f))
{
}

GoblinGruntBoar::~GoblinGruntBoar()
{
}
