#include "RedWyvern2.h"

RedWyvern2* RedWyvern2::create()
{
	RedWyvern2* instance = new RedWyvern2();

	instance->autorelease();

	return instance;
}

RedWyvern2::RedWyvern2() : Enemy::Enemy(
	Resources::Entities_Environment_Volcano_BossDemonKing_Animations,
	false)
{
}

RedWyvern2::~RedWyvern2()
{
}
