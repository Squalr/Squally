#include "OrcBomber.h"

const std::string OrcBomber::MapKeyEnemyOrcBomber = "orc_bomber";

OrcBomber* OrcBomber::deserialize(ValueMap* initProperties)
{
	OrcBomber* instance = new OrcBomber(initProperties);

	instance->autorelease();

	return instance;
}

OrcBomber::OrcBomber(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Environment_Forest_Enemies_OrcBomber_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(256.0f, 218.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

OrcBomber::~OrcBomber()
{
}
