#include "Xenon.h"

const std::string Xenon::MapKeyNpcXenon = "xenon";

Xenon* Xenon::deserialize(ValueMap* initProperties)
{
	Xenon* instance = new Xenon(initProperties);

	instance->autorelease();

	return instance;
}

Xenon::Xenon(ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Environment_Mech_Npcs_Xenon_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(472.0f, 780.0f),
	0.3f,
	Vec2(-24.0f, -390.0f))
{
}

Xenon::~Xenon()
{
}
