#include "ProjectilePool.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Objects/Platformer/Projectiles/Projectile.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const int ProjectilePool::DefaultPoolCapacity = 16;

ProjectilePool* ProjectilePool::create(std::function<Projectile*()> projectileFactory, int projectilePoolCapacity)
{
	ProjectilePool* instance = new ProjectilePool(projectileFactory, projectilePoolCapacity);

	instance->autorelease();

	return instance;
}

ProjectilePool::ProjectilePool(std::function<Projectile*()> projectileFactory, int projectilePoolCapacity) : super()
{
	this->projectileFactory = projectileFactory;
	this->projectiles = std::vector<Projectile*>();
	this->dartIndex = -1;
	this->projectilePoolCapacity = projectilePoolCapacity;
}

ProjectilePool::~ProjectilePool()
{
}

Projectile* ProjectilePool::getNextProjectile()
{
	if (int(this->projectiles.size()) < this->projectilePoolCapacity)
	{
		if (projectileFactory != nullptr)
		{
			Projectile* newProjectile = projectileFactory();

			if (newProjectile != nullptr)
			{
				newProjectile->disable(false);

				this->projectiles.push_back(newProjectile);
				this->addChild(newProjectile);
			}
		}
	}

	this->dartIndex = MathUtils::wrappingNormalize(this->dartIndex + 1, 0, this->projectiles.size() - 1);

	this->projectiles[dartIndex]->enable(true);
	GameUtils::setWorldCoords3D(this->projectiles[dartIndex], GameUtils::getWorldCoords3D(this));
	this->projectiles[dartIndex]->runSpawnFX();

	return this->projectiles[dartIndex];
}
