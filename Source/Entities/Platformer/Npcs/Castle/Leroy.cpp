#include "Leroy.h"

const std::string Leroy::MapKeyNpcLeroy = "leroy";

Leroy* Leroy::deserialize(ValueMap* initProperties)
{
	Leroy* instance = new Leroy(initProperties);

	instance->autorelease();

	return instance;
}

Leroy::Leroy(ValueMap* initProperties) : NpcBase(initProperties,
	Resources::Entities_Platformer_Environment_Castle_Npcs_Leroy_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(472.0f, 780.0f),
	0.3f,
	Vec2(-24.0f, -390.0f))
{
}

Leroy::~Leroy()
{
}
