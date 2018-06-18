#include "Shaman.h"

const std::string Shaman::KeyEnemyShaman = "shaman";

Shaman* Shaman::deserialize(ValueMap* initProperties)
{
	Shaman* instance = new Shaman(initProperties);

	instance->autorelease();

	return instance;
}

Shaman::Shaman(ValueMap* initProperties) : Enemy(initProperties,
	Resources::Entities_Environment_Caverns_Shaman_Animations,
	false,
	Size(256.0f, 288.0f),
	0.75f,
	Vec2(0.0f, 0.0f))
{
}

Shaman::~Shaman()
{
}
