#include "Cyclops.h"

const std::string Cyclops::KeyEnemyCyclops = "cyclops";

Cyclops* Cyclops::deserialize(ValueMap* initProperties)
{
	Cyclops* instance = new Cyclops(initProperties);

	instance->autorelease();

	return instance;
}

Cyclops::Cyclops(ValueMap* initProperties) : Enemy(initProperties,
	Resources::Entities_Environment_Forest_Cyclops_Animations,
	false,
	Size(296.0f, 256.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

Cyclops::~Cyclops()
{
}
