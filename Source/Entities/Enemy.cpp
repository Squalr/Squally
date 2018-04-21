#include "Enemy.h"

Enemy::Enemy(std::string scmlResource, std::string entityName, bool isFlying, Size size, float scale, Vec2 collisionOffset) 
	: Entity::Entity(scmlResource, entityName, isFlying, size, scale, collisionOffset)
{
	CategoryGroup categoryGroup = isFlying ? CategoryGroup::G_EnemyFlying : CategoryGroup::G_Enemy;

	this->init(PhysicsBody::createBox(size * scale), categoryGroup, true, false);
}

Enemy::~Enemy()
{
}