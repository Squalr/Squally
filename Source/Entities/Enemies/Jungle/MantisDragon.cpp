#include "MantisDragon.h"

MantisDragon* MantisDragon::create()
{
	MantisDragon* instance = new MantisDragon();

	instance->autorelease();

	return instance;
}

MantisDragon::MantisDragon() : Enemy::Enemy(
	Resources::Entities_Environment_Volcano_BossDemonKing_Animations,
	false)
{
}

MantisDragon::~MantisDragon()
{
}
