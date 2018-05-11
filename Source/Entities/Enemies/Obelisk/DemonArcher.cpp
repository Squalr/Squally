#include "DemonArcher.h"

DemonArcher* DemonArcher::create()
{
	DemonArcher* instance = new DemonArcher();

	instance->autorelease();

	return instance;
}

DemonArcher::DemonArcher() : Enemy::Enemy(
	Resources::Entities_Environment_Obelisk_DemonArcher_Animations,
	false)
{
}

DemonArcher::~DemonArcher()
{
}
