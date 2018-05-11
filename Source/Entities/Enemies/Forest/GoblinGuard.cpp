#include "GoblinGuard.h"

GoblinGuard* GoblinGuard::create()
{
	GoblinGuard* instance = new GoblinGuard();

	instance->autorelease();

	return instance;
}

GoblinGuard::GoblinGuard() : Enemy::Enemy(
	Resources::Entities_Environment_Forest_GoblinGuard_Animations,
	false)
{
}

GoblinGuard::~GoblinGuard()
{
}
