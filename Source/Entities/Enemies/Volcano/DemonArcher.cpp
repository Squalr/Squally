#include "DemonArcher.h"

DemonArcher* DemonArcher::create()
{
	DemonArcher* instance = new DemonArcher();

	instance->autorelease();

	return instance;
}

DemonArcher::DemonArcher() : Enemy::Enemy(
	Resources::Entities_Environment_Volcano_BossDemonKing_Animations,
	"BossDemonKing",
	false)
{
}

DemonArcher::~DemonArcher()
{
}
