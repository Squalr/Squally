#include "Cindra.h"

const std::string Cindra::MapKeyNpcCindra = "cindra";

Cindra* Cindra::deserialize(ValueMap* initProperties)
{
	Cindra* instance = new Cindra(initProperties);

	instance->autorelease();

	return instance;
}

Cindra::Cindra(ValueMap* initProperties) : NpcBase(initProperties,
	Resources::Entities_Platformer_Environment_Volcano_Npcs_Cindra_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(472.0f, 780.0f),
	0.3f,
	Vec2(-24.0f, -390.0f))
{
}

Cindra::~Cindra()
{
}
