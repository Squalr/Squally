#include "Robin.h"

const std::string Robin::MapKeyNpcRobin = "robin";

Robin* Robin::deserialize(ValueMap* initProperties)
{
	Robin* instance = new Robin(initProperties);

	instance->autorelease();

	return instance;
}

Robin::Robin(ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Platformer_Environment_Forest_Npcs_Robin_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(472.0f, 780.0f),
	0.3f,
	Vec2(-24.0f, -390.0f))
{
}

Robin::~Robin()
{
}
