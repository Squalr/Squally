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

const int ProjectilePool::PoolCapacity = 16;

ProjectilePool* ProjectilePool::create(std::function<Projectile*()> projectileFactory)
{
	ProjectilePool* instance = new ProjectilePool(projectileFactory);

	instance->autorelease();

	return instance;
}

ProjectilePool::ProjectilePool(std::function<Projectile*()> projectileFactory) : super()
{
	this->projectileFactory = projectileFactory;
	this->projectiles = std::vector<Projectile*>();
	this->dartIndex = -1;
}

ProjectilePool::~ProjectilePool()
{
}

Projectile* ProjectilePool::getNextProjectile()
{
	if (this->projectiles.size() < ProjectilePool::PoolCapacity)
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
	this->projectiles[dartIndex]->reset();
	this->projectiles[dartIndex]->runSpawnFX();

	return this->projectiles[dartIndex];
}
