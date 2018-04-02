#include "RedWyvern2.h"

RedWyvern2* RedWyvern2::create()
{
	RedWyvern2* instance = new RedWyvern2();

	instance->autorelease();

	return instance;
}

RedWyvern2::RedWyvern2() : Enemy::Enemy()
{
	this->initializeEnemy(
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		Resources::Entities_Environment_Castle_Harpy_Walk_0001,
		0.1f,
		true
	);
}

RedWyvern2::~RedWyvern2()
{
}
