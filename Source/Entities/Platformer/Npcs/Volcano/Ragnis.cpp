#include "Ragnis.h"

const std::string Ragnis::MapKeyNpcRagnis = "ragnis";

Ragnis* Ragnis::deserialize(ValueMap* initProperties)
{
	Ragnis* instance = new Ragnis(initProperties);

	instance->autorelease();

	return instance;
}

Ragnis::Ragnis(ValueMap* initProperties) : NpcBase(initProperties,
	Resources::Entities_Platformer_Environment_Volcano_Npcs_Ragnis_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(472.0f, 780.0f),
	0.3f,
	Vec2(-24.0f, -390.0f))
{
}

Ragnis::~Ragnis()
{
}
