#include "PurpleDino.h"

PurpleDino* PurpleDino::create()
{
	PurpleDino* instance = new PurpleDino();

	instance->autorelease();

	return instance;
}

PurpleDino::PurpleDino() : Enemy::Enemy(
	Resources::Entities_Environment_Volcano_BossDemonKing_Animations,
	false)
{
}

PurpleDino::~PurpleDino()
{
}
