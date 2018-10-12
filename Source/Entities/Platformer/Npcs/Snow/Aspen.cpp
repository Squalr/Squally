#include "Aspen.h"

const std::string Aspen::MapKeyNpcAspen = "Aspen";

Aspen* Aspen::deserialize(ValueMap* initProperties)
{
	Aspen* instance = new Aspen(initProperties);

	instance->autorelease();

	return instance;
}

Aspen::Aspen(ValueMap* initProperties) : NpcBase(initProperties,
	Resources::Entities_Platformer_Environment_Castle_Npcs_Guard_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(472.0f, 780.0f),
	0.3f,
	Vec2(-24.0f, -390.0f))
{
}

Aspen::~Aspen()
{
}
