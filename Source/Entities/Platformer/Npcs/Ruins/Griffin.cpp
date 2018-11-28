#include "Griffin.h"

const std::string Griffin::MapKeyNpcGriffin = "griffin";

Griffin* Griffin::deserialize(ValueMap* initProperties)
{
	Griffin* instance = new Griffin(initProperties);

	instance->autorelease();

	return instance;
}

Griffin::Griffin(ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Environment_Ruins_Npcs_Griffin_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(472.0f, 780.0f),
	0.3f,
	Vec2(-24.0f, -390.0f))
{
}

Griffin::~Griffin()
{
}
