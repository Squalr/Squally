#include "Alder.h"

const std::string Alder::MapKeyNpcAlder = "alder";

Alder* Alder::deserialize(ValueMap* initProperties)
{
	Alder* instance = new Alder(initProperties);

	instance->autorelease();

	return instance;
}

Alder::Alder(ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Environment_Caverns_Npcs_Alder_Animations,
	PlatformerCollisionType::Enemy,
	Size(472.0f, 780.0f),
	0.3f,
	Vec2(-24.0f, -390.0f))
{
}

Alder::~Alder()
{
}
