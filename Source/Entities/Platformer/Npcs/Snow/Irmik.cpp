#include "Irmik.h"

const std::string Irmik::MapKeyNpcIrmik = "irmik";

Irmik* Irmik::deserialize(ValueMap* initProperties)
{
	Irmik* instance = new Irmik(initProperties);

	instance->autorelease();

	return instance;
}

Irmik::Irmik(ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Environment_Snow_Npcs_Irmik_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(472.0f, 780.0f),
	0.3f,
	Vec2(-24.0f, -390.0f))
{
}

Irmik::~Irmik()
{
}
