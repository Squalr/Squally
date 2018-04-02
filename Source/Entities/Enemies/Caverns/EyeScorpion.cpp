#include "EyeScorpion.h"

EyeScorpion* EyeScorpion::create()
{
	EyeScorpion* instance = new EyeScorpion();

	instance->autorelease();

	return instance;
}

EyeScorpion::EyeScorpion() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

EyeScorpion::~EyeScorpion()
{
}
