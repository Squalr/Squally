#include "BatDemon.h"

const std::string BatDemon::KeyEnemyBatDemon = "bat_demon";

BatDemon* BatDemon::deserialize(ValueMap* initProperties)
{
	BatDemon* instance = new BatDemon(initProperties);

	instance->autorelease();

	return instance;
}

BatDemon::BatDemon(ValueMap* initProperties) : Enemy(initProperties,
	Resources::Entities_Environment_Obelisk_BatDemon_Animations,
	false,
	Size(726.0f, 1024.0f),
	0.23f,
	Vec2(-32.0f, -512.0f))
{
}

BatDemon::~BatDemon()
{
}
