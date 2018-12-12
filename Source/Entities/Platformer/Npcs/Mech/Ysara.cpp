#include "Ysara.h"

const std::string Ysara::MapKeyNpcYsara = "ysara";

Ysara* Ysara::deserialize(ValueMap* initProperties)
{
	Ysara* instance = new Ysara(initProperties);

	instance->autorelease();

	return instance;
}

Ysara::Ysara(ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Environment_Mech_Npcs_Ysara_Animations,
	PlatformerCollisionType::Enemy,
	Size(472.0f, 780.0f),
	0.3f,
	Vec2(-24.0f, -390.0f))
{
}

Ysara::~Ysara()
{
}
