#include "Exterminator.h"

const std::string Exterminator::KeyEnemyExterminator = "exterminator";

Exterminator* Exterminator::deserialize(ValueMap* initProperties)
{
	Exterminator* instance = new Exterminator(initProperties);

	instance->autorelease();

	return instance;
}

Exterminator::Exterminator(ValueMap* initProperties) : Enemy(initProperties,
	Resources::Entities_Environment_Mech_Exterminator_Animations,
	false,
	Size(320.0f, 278.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Exterminator::~Exterminator()
{
}
