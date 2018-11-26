#include "Nessie.h"

const std::string Nessie::MapKeyNpcNessie = "nessie";

Nessie* Nessie::deserialize(ValueMap* initProperties)
{
	Nessie* instance = new Nessie(initProperties);

	instance->autorelease();

	return instance;
}

Nessie::Nessie(ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Platformer_Environment_Snow_Npcs_Nessie_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(472.0f, 780.0f),
	0.3f,
	Vec2(-24.0f, -390.0f))
{
}

Nessie::~Nessie()
{
}
