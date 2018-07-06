#include "Undead.h"

const std::string Undead::KeyEnemyUndead = "undead";

Undead* Undead::deserialize(ValueMap* initProperties)
{
	Undead* instance = new Undead(initProperties);

	instance->autorelease();

	return instance;
}

Undead::Undead(ValueMap* initProperties) : Enemy(initProperties,
	Resources::Entities_Platformer_Environment_Obelisk_Undead_Animations,
	false,
	Size(146.0f, 248.0f),
	0.8f,
	Vec2(0.0f, 0.0f))
{
}

Undead::~Undead()
{
}
