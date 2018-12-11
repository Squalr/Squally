#include "Cooper.h"

const std::string Cooper::MapKeyNpcCooper = "cooper";

Cooper* Cooper::deserialize(ValueMap* initProperties)
{
	Cooper* instance = new Cooper(initProperties);

	instance->autorelease();

	return instance;
}

Cooper::Cooper(ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Environment_Forest_Npcs_Cooper_Animations,
	PlatformerCollisionType::Enemy,
	Size(472.0f, 780.0f),
	0.3f,
	Vec2(-24.0f, -390.0f))
{
}

Cooper::~Cooper()
{
}
