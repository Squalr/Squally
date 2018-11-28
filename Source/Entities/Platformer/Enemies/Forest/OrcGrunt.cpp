#include "OrcGrunt.h"

const std::string OrcGrunt::MapKeyEnemyOrcGrunt = "orc_grunt";

OrcGrunt* OrcGrunt::deserialize(ValueMap* initProperties)
{
	OrcGrunt* instance = new OrcGrunt(initProperties);

	instance->autorelease();

	return instance;
}

OrcGrunt::OrcGrunt(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Environment_Forest_Enemies_OrcGrunt_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(256.0f, 218.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

OrcGrunt::~OrcGrunt()
{
}
