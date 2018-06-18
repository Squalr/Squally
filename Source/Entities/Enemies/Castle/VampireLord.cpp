#include "VampireLord.h"

const std::string VampireLord::KeyEnemyVampireLord = "vampire_lord";

VampireLord* VampireLord::create()
{
	VampireLord* instance = new VampireLord();

	instance->autorelease();

	return instance;
}

VampireLord::VampireLord() : Enemy::Enemy(
	Resources::Entities_Environment_Castle_VampireLord_Animations,
	false,
	Size(240.0f, 312.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

VampireLord::~VampireLord()
{
}
