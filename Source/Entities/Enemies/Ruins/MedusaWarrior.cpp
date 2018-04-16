#include "MedusaWarrior.h"

MedusaWarrior* MedusaWarrior::create()
{
	MedusaWarrior* instance = new MedusaWarrior();

	instance->autorelease();

	return instance;
}

MedusaWarrior::MedusaWarrior() : Enemy::Enemy(
	Resources::Entities_Environment_Volcano_BossDemonKing_Animations,
	"BossDemonKing",
	false)
{
}

MedusaWarrior::~MedusaWarrior()
{
}
