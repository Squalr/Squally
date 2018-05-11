#include "VampireLord.h"

VampireLord* VampireLord::create()
{
	VampireLord* instance = new VampireLord();

	instance->autorelease();

	return instance;
}

VampireLord::VampireLord() : Enemy::Enemy(
	Resources::Entities_Environment_Castle_VampireLord_Animations,
	false)
{
}

VampireLord::~VampireLord()
{
}
