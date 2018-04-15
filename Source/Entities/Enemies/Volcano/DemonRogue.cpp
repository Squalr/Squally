#include "DemonRogue.h"

DemonRogue* DemonRogue::create()
{
	DemonRogue* instance = new DemonRogue();

	instance->autorelease();

	return instance;
}

DemonRogue::DemonRogue() : Enemy::Enemy(
	Resources::Entities_Environment_Lava_BossDemonKing_Animations,
	"BossDemonKing",
	false)
{
}

DemonRogue::~DemonRogue()
{
}
