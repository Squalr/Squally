#include "DemonArcher.h"

DemonArcher* DemonArcher::create()
{
	DemonArcher* instance = new DemonArcher();

	instance->autorelease();

	return instance;
}

DemonArcher::DemonArcher() : Enemy::Enemy(
	Resources::Entities_Environment_Obelisk_DemonArcher_Animations,
	false,
	Size(196.0f, 348.0f),
	0.65f,
	Vec2(0.0f, 0.0f))
{
}

DemonArcher::~DemonArcher()
{
}
