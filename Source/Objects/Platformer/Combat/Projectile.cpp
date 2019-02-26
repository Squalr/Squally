#include "Projectile.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/CombatEvents.h"

using namespace cocos2d;

Projectile::Projectile(std::function<void(PlatformerEntity* target)> onTargetHit, float radius, float noCollideDuration) : ProximityObject(radius)
{
	this->onTargetHit = onTargetHit;
	this->hasCollided = false;
	this->noCollideDuration = noCollideDuration;
	this->elapsedDuration = 0.0f;
}

Projectile::~Projectile()
{
}

void Projectile::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void Projectile::initializePositions()
{
	super::initializePositions();
}

void Projectile::update(float dt)
{
	super::update(dt);

	this->elapsedDuration += dt;

	if (this->onTargetHit != nullptr && !this->hasCollided && this->elapsedDuration > this->noCollideDuration)
	{
		auto entities = this->getProximityObjects<PlatformerEntity>();

		if (!entities.empty())
		{
			PlatformerEntity* target = entities.at(0);

			onTargetHit(target);

			this->hasCollided = true;
		}
	}
}
