#include "Illia.h"

const std::string Illia::MapKeyNpcIllia = "illia";

Illia* Illia::deserialize(ValueMap* initProperties)
{
	Illia* instance = new Illia(initProperties);

	instance->autorelease();

	return instance;
}

Illia::Illia(ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Environment_Mech_Npcs_Illia_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(472.0f, 780.0f),
	0.3f,
	Vec2(-24.0f, -390.0f))
{
}

Illia::~Illia()
{
}
