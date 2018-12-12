#include "Vampiress.h"

const std::string Vampiress::MapKeyEnemyVampiress = "vampiress";

Vampiress* Vampiress::deserialize(ValueMap* initProperties)
{
	Vampiress* instance = new Vampiress(initProperties);

	instance->autorelease();

	return instance;
}

Vampiress::Vampiress(ValueMap* initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Environment_Castle_Enemies_Vampiress_Animations,
	PlatformerCollisionType::Enemy,
	Size(96.0f, 236.0f),
	0.9f,
	Vec2(0.0f, 0.0f))
{
}

Vampiress::~Vampiress()
{
}
