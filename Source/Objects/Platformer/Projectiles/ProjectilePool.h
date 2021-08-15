#pragma once

#include "Engine/SmartNode.h"

class Projectile;

class ProjectilePool : public SmartNode
{
public:
	static ProjectilePool* create(std::function<Projectile*()> projectileFactory, int projectilePoolCapacity = ProjectilePool::DefaultPoolCapacity);

	Projectile* getNextProjectile();

	static const int DefaultPoolCapacity;

protected:
	ProjectilePool(std::function<Projectile*()> projectileFactory, int projectilePoolCapacity);
	virtual ~ProjectilePool();

private:
	typedef SmartNode super;

	std::vector<Projectile*> projectiles;
	std::function<Projectile*()> projectileFactory = nullptr;

	int dartIndex = 0;
	int projectilePoolCapacity = -1;
};
