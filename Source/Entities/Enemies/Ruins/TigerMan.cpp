#include "TigerMan.h"

TigerMan* TigerMan::create()
{
	TigerMan* instance = new TigerMan();

	instance->autorelease();

	return instance;
}

TigerMan::TigerMan() : Enemy::Enemy(
	Resources::Entities_Environment_Ruins_TigerMan_Animations,
	false)
{
}

TigerMan::~TigerMan()
{
}
