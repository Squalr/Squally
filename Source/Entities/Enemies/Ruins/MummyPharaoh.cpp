#include "MummyPharaoh.h"

MummyPharaoh* MummyPharaoh::create()
{
	MummyPharaoh* instance = new MummyPharaoh();

	instance->autorelease();

	return instance;
}

MummyPharaoh::MummyPharaoh() : Enemy::Enemy(
	Resources::Entities_Environment_Ruins_MummyPharaoh_Animations,
	false,
	Size(324.0f, 316.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
}

MummyPharaoh::~MummyPharaoh()
{
}
