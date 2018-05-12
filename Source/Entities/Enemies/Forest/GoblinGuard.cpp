#include "GoblinGuard.h"

GoblinGuard* GoblinGuard::create()
{
	GoblinGuard* instance = new GoblinGuard();

	instance->autorelease();

	return instance;
}

GoblinGuard::GoblinGuard() : Enemy::Enemy(
	Resources::Entities_Environment_Forest_GoblinGuard_Animations,
	false,
	Size(472.0f, 768.0f),
	0.3f,
	Vec2(-24.0f, -368.0f))
{
}

GoblinGuard::~GoblinGuard()
{
}
