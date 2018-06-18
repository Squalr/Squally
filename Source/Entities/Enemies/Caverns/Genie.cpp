#include "Genie.h"

const std::string Genie::KeyEnemyGenie = "genie";

Genie* Genie::deserialize(ValueMap* initProperties)
{
	Genie* instance = new Genie(initProperties);

	instance->autorelease();

	return instance;
}

Genie::Genie(ValueMap* initProperties) : Enemy(initProperties,
	Resources::Entities_Environment_Caverns_Genie_Animations,
	false,
	Size(512.0f, 1126.0f),
	0.20f,
	Vec2(0.0f, -356.0f))
{
}

Genie::~Genie()
{
}
