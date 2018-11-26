#include "Brine.h"

const std::string Brine::MapKeyNpcBrine = "brine";

Brine* Brine::deserialize(ValueMap* initProperties)
{
	Brine* instance = new Brine(initProperties);

	instance->autorelease();

	return instance;
}

Brine::Brine(ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Platformer_Environment_Volcano_Npcs_Brine_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(472.0f, 780.0f),
	0.3f,
	Vec2(-24.0f, -390.0f))
{
}

Brine::~Brine()
{
}
