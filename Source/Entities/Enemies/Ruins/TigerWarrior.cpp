#include "TigerWarrior.h"

TigerWarrior* TigerWarrior::create()
{
	TigerWarrior* instance = new TigerWarrior();

	instance->autorelease();

	return instance;
}

TigerWarrior::TigerWarrior() : Enemy::Enemy(
	Resources::Entities_Environment_Volcano_BossDemonKing_Animations,
	"BossDemonKing",
	false)
{
}

TigerWarrior::~TigerWarrior()
{
}
