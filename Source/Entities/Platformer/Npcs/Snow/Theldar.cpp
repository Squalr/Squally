#include "Theldar.h"

const std::string Theldar::MapKeyNpcTheldar = "theldar";

Theldar* Theldar::deserialize(ValueMap* initProperties)
{
	Theldar* instance = new Theldar(initProperties);

	instance->autorelease();

	return instance;
}

Theldar::Theldar(ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Environment_Snow_Npcs_Theldar_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(472.0f, 780.0f),
	0.3f,
	Vec2(-24.0f, -390.0f))
{
}

Theldar::~Theldar()
{
}
