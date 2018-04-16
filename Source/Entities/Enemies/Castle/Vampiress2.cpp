#include "Vampiress2.h"

Vampiress2* Vampiress2::create()
{
	Vampiress2* instance = new Vampiress2();

	instance->autorelease();

	return instance;
}

Vampiress2::Vampiress2() : Enemy::Enemy(
	Resources::Entities_Environment_Volcano_BossDemonKing_Animations,
	"BossDemonKing",
	false)
{
}

Vampiress2::~Vampiress2()
{
}
