#include "Magnus.h"

const std::string Magnus::MapKeyNpcMagnus = "magnus";

Magnus* Magnus::deserialize(ValueMap* initProperties)
{
	Magnus* instance = new Magnus(initProperties);

	instance->autorelease();

	return instance;
}

Magnus::Magnus(ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Platformer_Environment_Volcano_Npcs_Magnus_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(472.0f, 780.0f),
	0.3f,
	Vec2(-24.0f, -390.0f))
{
}

Magnus::~Magnus()
{
}
