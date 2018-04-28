#include "RedWyvern1.h"

RedWyvern1* RedWyvern1::create()
{
	RedWyvern1* instance = new RedWyvern1();

	instance->autorelease();

	return instance;
}

RedWyvern1::RedWyvern1() : Enemy::Enemy(
	Resources::Entities_Environment_Volcano_BossDemonKing_Animations,
	false)
{
}

RedWyvern1::~RedWyvern1()
{
}
