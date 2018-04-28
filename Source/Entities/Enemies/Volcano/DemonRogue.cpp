#include "DemonRogue.h"

DemonRogue* DemonRogue::create()
{
	DemonRogue* instance = new DemonRogue();

	instance->autorelease();

	return instance;
}

DemonRogue::DemonRogue() : Enemy::Enemy(
	Resources::Entities_Environment_Volcano_BossDemonKing_Animations,
	false)
{
}

DemonRogue::~DemonRogue()
{
}
