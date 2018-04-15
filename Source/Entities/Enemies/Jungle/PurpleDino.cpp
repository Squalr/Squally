#include "PurpleDino.h"

PurpleDino* PurpleDino::create()
{
	PurpleDino* instance = new PurpleDino();

	instance->autorelease();

	return instance;
}

PurpleDino::PurpleDino() : Enemy::Enemy(
	Resources::Entities_Environment_Lava_BossDemonKing_Animations,
	"BossDemonKing",
	false)
{
}

PurpleDino::~PurpleDino()
{
}
