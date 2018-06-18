#include "DemonRogue.h"

const std::string DemonRogue::KeyEnemyDemonRogue = "demon_rogue";

DemonRogue* DemonRogue::create()
{
	DemonRogue* instance = new DemonRogue();

	instance->autorelease();

	return instance;
}

DemonRogue::DemonRogue() : Enemy::Enemy(
	Resources::Entities_Environment_Volcano_DemonRogue_Animations,
	false,
	Size(212.0f, 268.0f),
	0.65f,
	Vec2(0.0f, 0.0f))
{
}

DemonRogue::~DemonRogue()
{
}
