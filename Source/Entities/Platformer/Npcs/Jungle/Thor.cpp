#include "Thor.h"

const std::string Thor::MapKeyNpcThor = "thor";

Thor* Thor::deserialize(ValueMap* initProperties)
{
	Thor* instance = new Thor(initProperties);

	instance->autorelease();

	return instance;
}

Thor::Thor(ValueMap* initProperties) : NpcBase(initProperties,
	Resources::Entities_Platformer_Environment_Jungle_Npcs_Thor_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(472.0f, 780.0f),
	0.3f,
	Vec2(-24.0f, -390.0f))
{
}

Thor::~Thor()
{
}
