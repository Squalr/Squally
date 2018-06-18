#include "OrcGrunt.h"

const std::string OrcGrunt::KeyEnemyOrcGrunt = "orc_grunt";

OrcGrunt* OrcGrunt::deserialize(ValueMap* initProperties)
{
	OrcGrunt* instance = new OrcGrunt(initProperties);

	instance->autorelease();

	return instance;
}

OrcGrunt::OrcGrunt(ValueMap* initProperties) : Enemy(initProperties,
	Resources::Entities_Environment_Forest_OrcGrunt_Animations,
	false,
	Size(256.0f, 218.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

OrcGrunt::~OrcGrunt()
{
}
