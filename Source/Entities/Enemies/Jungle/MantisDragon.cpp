#include "MantisDragon.h"

MantisDragon* MantisDragon::create()
{
	MantisDragon* instance = new MantisDragon();

	instance->autorelease();

	return instance;
}

MantisDragon::MantisDragon() : Enemy::Enemy(
	Resources::Entities_Environment_Lava_BossDemonKing_Animations,
	"BossDemonKing",
	false)
{
}

MantisDragon::~MantisDragon()
{
}
