#include "Yeti3.h"

Yeti3* Yeti3::create()
{
	Yeti3* instance = new Yeti3();

	instance->autorelease();

	return instance;
}

Yeti3::Yeti3() : Enemy::Enemy(
	Resources::Entities_Environment_Volcano_BossDemonKing_Animations,
	"BossDemonKing",
	false)
{
}

Yeti3::~Yeti3()
{
}
