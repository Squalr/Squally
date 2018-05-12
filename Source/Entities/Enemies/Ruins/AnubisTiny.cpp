#include "AnubisTiny.h"

AnubisTiny* AnubisTiny::create()
{
	AnubisTiny* instance = new AnubisTiny();

	instance->autorelease();

	return instance;
}

AnubisTiny::AnubisTiny() : Enemy::Enemy(
	Resources::Entities_Environment_Ruins_AnubisTiny_Animations,
	false,
	Size(128.0f, 186.0f),
	0.8f,
	Vec2(0.0f, 0.0f))
{
}

AnubisTiny::~AnubisTiny()
{
}
