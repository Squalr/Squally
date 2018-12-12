#include "Mabel.h"

const std::string Mabel::MapKeyNpcMabel = "mabel";

Mabel* Mabel::deserialize(ValueMap* initProperties)
{
	Mabel* instance = new Mabel(initProperties);

	instance->autorelease();

	return instance;
}

Mabel::Mabel(ValueMap* initProperties) : NpcBase(initProperties,
	EntityResources::Environment_Castle_Npcs_Mabel_Animations,
	PlatformerCollisionType::Enemy,
	Size(472.0f, 780.0f),
	0.3f,
	Vec2(-24.0f, -390.0f))
{
}

Mabel::~Mabel()
{
}
