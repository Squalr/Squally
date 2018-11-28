#include "Tyracius.h"

const std::string Tyracius::MapKeyNpcTyracius = "tyracius";

Tyracius* Tyracius::deserialize(ValueMap* initProperties)
{
	Tyracius* instance = new Tyracius(initProperties);

	instance->autorelease();

	return instance;
}

Tyracius::Tyracius(ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Environment_Castle_Npcs_Tyracius_Animations,
	PlatformerCollisionMapping::KeyCollisionTypeEnemy,
	Size(472.0f, 780.0f),
	0.3f,
	Vec2(-24.0f, -390.0f))
{
}

Tyracius::~Tyracius()
{
}
