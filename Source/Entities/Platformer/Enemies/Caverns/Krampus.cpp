#include "Krampus.h"

const std::string Krampus::MapKeyEnemyKrampus = "krampus";

Krampus* Krampus::deserialize(ValueMap* initProperties)
{
	Krampus* instance = new Krampus(initProperties);

	instance->autorelease();

	return instance;
}

Krampus::Krampus(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Environment_Caverns_Enemies_Krampus_Animations,
	PlatformerCollisionType::Enemy,
	Size(396.0f, 412.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Krampus::~Krampus()
{
}
