#include "MummyPharoh.h"

MummyPharoh* MummyPharoh::create()
{
	MummyPharoh* instance = new MummyPharoh();

	instance->autorelease();

	return instance;
}

MummyPharoh::MummyPharoh() : Enemy::Enemy(
	Resources::Entities_Environment_Lava_BossDemonKing_Animations,
	"BossDemonKing",
	false)
{
}

MummyPharoh::~MummyPharoh()
{
}
