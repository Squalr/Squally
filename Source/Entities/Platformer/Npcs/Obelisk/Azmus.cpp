#include "Azmus.h"

const std::string Azmus::MapKeyNpcAzmus = "azmus";

Azmus* Azmus::deserialize(ValueMap* initProperties)
{
	Azmus* instance = new Azmus(initProperties);

	instance->autorelease();

	return instance;
}

Azmus::Azmus(ValueMap* initProperties) : NpcBase(initProperties,
	Resources::Entities_Platformer_Environment_Obelisk_Npcs_Azmus_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(472.0f, 780.0f),
	0.3f,
	Vec2(-24.0f, -390.0f))
{
}

Azmus::~Azmus()
{
}
