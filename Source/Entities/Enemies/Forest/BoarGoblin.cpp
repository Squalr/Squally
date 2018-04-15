#include "BoarGoblin.h"

BoarGoblin* BoarGoblin::create()
{
	BoarGoblin* instance = new BoarGoblin();

	instance->autorelease();

	return instance;
}

BoarGoblin::BoarGoblin() : Enemy::Enemy(
	Resources::Entities_Environment_Lava_BossDemonKing_Animations,
	"BossDemonKing",
	false)
{
}

BoarGoblin::~BoarGoblin()
{
}
