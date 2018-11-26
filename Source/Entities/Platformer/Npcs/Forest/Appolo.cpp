#include "Appolo.h"

const std::string Appolo::MapKeyNpcAppolo = "appolo";

Appolo* Appolo::deserialize(ValueMap* initProperties)
{
	Appolo* instance = new Appolo(initProperties);

	instance->autorelease();

	return instance;
}

Appolo::Appolo(ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Platformer_Environment_Forest_Npcs_Appolo_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(472.0f, 780.0f),
	0.3f,
	Vec2(-24.0f, -390.0f))
{
}

Appolo::~Appolo()
{
}
