#include "Jasper.h"

const std::string Jasper::MapKeyNpcJasper = "jasper";

Jasper* Jasper::deserialize(ValueMap* initProperties)
{
	Jasper* instance = new Jasper(initProperties);

	instance->autorelease();

	return instance;
}

Jasper::Jasper(ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Environment_Caverns_Npcs_Jasper_Animations,
	PlatformerCollisionType::Enemy,
	Size(472.0f, 780.0f),
	0.3f,
	Vec2(-24.0f, -390.0f))
{
}

Jasper::~Jasper()
{
}
