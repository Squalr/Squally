#include "Amelia.h"

const std::string Amelia::MapKeyNpcAmelia = "amelia";

Amelia* Amelia::deserialize(ValueMap* initProperties)
{
	Amelia* instance = new Amelia(initProperties);

	instance->autorelease();

	return instance;
}

Amelia::Amelia(ValueMap* initProperties) : NpcBase(initProperties,
	Resources::Entities_Platformer_Environment_Obelisk_Npcs_Amelia_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(472.0f, 780.0f),
	0.3f,
	Vec2(-24.0f, -390.0f))
{
}

Amelia::~Amelia()
{
}
