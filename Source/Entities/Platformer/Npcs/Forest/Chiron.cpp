#include "Chiron.h"

const std::string Chiron::MapKeyNpcChiron = "chiron";

Chiron* Chiron::deserialize(ValueMap* initProperties)
{
	Chiron* instance = new Chiron(initProperties);

	instance->autorelease();

	return instance;
}

Chiron::Chiron(ValueMap* initProperties) : NpcBase(initProperties,
	Resources::Entities_Platformer_Environment_Forest_Npcs_Chiron_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(472.0f, 780.0f),
	0.3f,
	Vec2(-24.0f, -390.0f))
{
}

Chiron::~Chiron()
{
}
