#include "Manticore.h"

const std::string Manticore::MapKeyNpcManticore = "manticore";

Manticore* Manticore::deserialize(ValueMap* initProperties)
{
	Manticore* instance = new Manticore(initProperties);

	instance->autorelease();

	return instance;
}

Manticore::Manticore(ValueMap* initProperties) : NpcBase(initProperties,
	Resources::Entities_Platformer_Environment_Ruins_Npcs_Manticore_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(472.0f, 780.0f),
	0.3f,
	Vec2(-24.0f, -390.0f))
{
}

Manticore::~Manticore()
{
}
