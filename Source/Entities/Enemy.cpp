#include "Enemy.h"

Enemy::Enemy(std::string scmlResource, bool isFlying, Size size, float scale, Vec2 collisionOffset) 
	: Entity::Entity(scmlResource, isFlying, size, scale, collisionOffset)
{
	CategoryGroup categoryGroup = isFlying ? CategoryGroup::G_EnemyFlying : CategoryGroup::G_Enemy;

	this->init(PhysicsBody::createBox(size * scale, PhysicsMaterial(0.0f, 0.0f, 0.0f)), categoryGroup, true, false);
}

Enemy::~Enemy()
{
}