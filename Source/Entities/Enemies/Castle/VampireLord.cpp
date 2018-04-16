#include "VampireLord.h"

VampireLord* VampireLord::create()
{
	VampireLord* instance = new VampireLord();

	instance->autorelease();

	return instance;
}

VampireLord::VampireLord() : Enemy::Enemy(
	Resources::Entities_Environment_Volcano_BossDemonKing_Animations,
	"BossDemonKing",
	false)
{
}

VampireLord::~VampireLord()
{
}
