#include "TigerMan.h"

TigerMan* TigerMan::create()
{
	TigerMan* instance = new TigerMan();

	instance->autorelease();

	return instance;
}

TigerMan::TigerMan() : Enemy::Enemy(
	Resources::Entities_Environment_Ruins_TigerMan_Animations,
	false,
	Size(256.0f, 308.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

TigerMan::~TigerMan()
{
}
