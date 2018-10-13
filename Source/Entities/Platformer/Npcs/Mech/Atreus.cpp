#include "Atreus.h"

const std::string Atreus::MapKeyNpcAtreus = "atreus";

Atreus* Atreus::deserialize(ValueMap* initProperties)
{
	Atreus* instance = new Atreus(initProperties);

	instance->autorelease();

	return instance;
}

Atreus::Atreus(ValueMap* initProperties) : NpcBase(initProperties,
	Resources::Entities_Platformer_Environment_Mech_Npcs_Atreus_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(472.0f, 780.0f),
	0.3f,
	Vec2(-24.0f, -390.0f))
{
}

Atreus::~Atreus()
{
}
