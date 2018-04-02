#include "RedWyvern1.h"

RedWyvern1* RedWyvern1::create()
{
	RedWyvern1* instance = new RedWyvern1();

	instance->autorelease();

	return instance;
}

RedWyvern1::RedWyvern1() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

RedWyvern1::~RedWyvern1()
{
}
