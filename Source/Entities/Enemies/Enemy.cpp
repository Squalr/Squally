#include "Enemy.h"

Enemy* Enemy::create()
{
	Enemy* enemy = new Enemy();

	enemy->autorelease();

	return enemy;
}


Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}
