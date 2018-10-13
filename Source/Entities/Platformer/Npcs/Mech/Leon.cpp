#include "Leon.h"

const std::string Leon::MapKeyNpcLeon = "leon";

Leon* Leon::deserialize(ValueMap* initProperties)
{
	Leon* instance = new Leon(initProperties);

	instance->autorelease();

	return instance;
}

Leon::Leon(ValueMap* initProperties) : NpcBase(initProperties,
	Resources::Entities_Platformer_Environment_Mech_Npcs_Leon_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(472.0f, 780.0f),
	0.3f,
	Vec2(-24.0f, -390.0f))
{
}

Leon::~Leon()
{
}
