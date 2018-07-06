#include "VoidDemon.h"

const std::string VoidDemon::KeyEnemyVoidDemon = "void_demon";

VoidDemon* VoidDemon::deserialize(ValueMap* initProperties)
{
	VoidDemon* instance = new VoidDemon(initProperties);

	instance->autorelease();

	return instance;
}

VoidDemon::VoidDemon(ValueMap* initProperties) : Enemy(initProperties,
	Resources::Entities_Platformer_Environment_Obelisk_VoidDemon_Animations,
	false,
	Size(338.0f, 342.0f),
	0.7f,
	Vec2(0.0f, 0.0f))
{
}

VoidDemon::~VoidDemon()
{
}
