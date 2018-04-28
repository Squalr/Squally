#include "MummyPharaoh.h"

MummyPharaoh* MummyPharaoh::create()
{
	MummyPharaoh* instance = new MummyPharaoh();

	instance->autorelease();

	return instance;
}

MummyPharaoh::MummyPharaoh() : Enemy::Enemy(
	Resources::Entities_Environment_Volcano_BossDemonKing_Animations,
	false)
{
}

MummyPharaoh::~MummyPharaoh()
{
}
