#include "Celeste.h"

const std::string Celeste::MapKeyNpcCeleste = "celeste";

Celeste* Celeste::deserialize(ValueMap* initProperties)
{
	Celeste* instance = new Celeste(initProperties);

	instance->autorelease();

	return instance;
}

Celeste::Celeste(ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Environment_Volcano_Npcs_Celeste_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(472.0f, 780.0f),
	0.3f,
	Vec2(-24.0f, -390.0f))
{
}

Celeste::~Celeste()
{
}
