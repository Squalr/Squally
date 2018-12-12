#include "Jingles.h"

const std::string Jingles::MapKeyNpcJingles = "jingles";

Jingles* Jingles::deserialize(ValueMap* initProperties)
{
	Jingles* instance = new Jingles(initProperties);

	instance->autorelease();

	return instance;
}

Jingles::Jingles(ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Environment_Snow_Npcs_Jingles_Animations,
	PlatformerCollisionType::Enemy,
	Size(472.0f, 780.0f),
	0.3f,
	Vec2(-24.0f, -390.0f))
{
}

Jingles::~Jingles()
{
}
