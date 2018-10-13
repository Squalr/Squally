#include "Rupert.h"

const std::string Rupert::MapKeyNpcRupert = "rupert";

Rupert* Rupert::deserialize(ValueMap* initProperties)
{
	Rupert* instance = new Rupert(initProperties);

	instance->autorelease();

	return instance;
}

Rupert::Rupert(ValueMap* initProperties) : NpcBase(initProperties,
	Resources::Entities_Platformer_Environment_Forest_Npcs_Rupert_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(472.0f, 780.0f),
	0.3f,
	Vec2(-24.0f, -390.0f))
{
}

Rupert::~Rupert()
{
}
