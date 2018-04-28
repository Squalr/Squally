#include "Vampiress1.h"

Vampiress1* Vampiress1::create()
{
	Vampiress1* instance = new Vampiress1();

	instance->autorelease();

	return instance;
}

Vampiress1::Vampiress1() : Enemy::Enemy(
	Resources::Entities_Environment_Volcano_BossDemonKing_Animations,
	false)
{
}

Vampiress1::~Vampiress1()
{
}
