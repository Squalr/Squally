#include "EntityHealthBehaviorBase.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Events/SaveEvents.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/Utils/MathUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/StatsTables/StatsTables.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

EntityHealthBehaviorBase::EntityHealthBehaviorBase(GameObject* owner, std::string attachedBehaviorArgs) : super(owner, attachedBehaviorArgs)
{
	this->entity = static_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->maxHealth = 0;
		this->health = 0;
		this->invalidate();
	}
	else
	{
		this->maxHealth = StatsTables::getBaseHealth(this->entity);
		this->health = this->maxHealth;
	}
}

EntityHealthBehaviorBase::~EntityHealthBehaviorBase()
{
}

void EntityHealthBehaviorBase::onLoad()
{
}

int EntityHealthBehaviorBase::getHealth()
{
	return this->health;
}

void EntityHealthBehaviorBase::addHealth(int healthDelta)
{
	this->setHealth(this->getHealth() + healthDelta);
}

void EntityHealthBehaviorBase::setHealth(int health)
{
	if (this->isDead())
	{
		return;
	}

	this->health = MathUtils::clamp(health, 0, this->maxHealth);

	if (this->health <= 0 && this->entity != nullptr)
	{
		this->entity->getAnimations()->playAnimation("Death", SmartAnimationNode::AnimationPlayMode::PauseOnAnimationComplete);
	}
}

int EntityHealthBehaviorBase::getMaxHealth()
{
	return this->maxHealth;
}

void EntityHealthBehaviorBase::kill(bool loadDeadAnim)
{
	this->setHealth(0);

	if (loadDeadAnim && this->entity != nullptr)
	{
		this->entity->getAnimations()->playAnimation("Dead", SmartAnimationNode::AnimationPlayMode::PauseOnAnimationComplete);
	}
}

void EntityHealthBehaviorBase::killAndRespawn()
{
	this->kill();

	this->runAction(Sequence::create(
		DelayTime::create(1.5f),
		CallFunc::create([=]()
		{
			this->entity->setPosition(this->entity->spawnCoords);

			this->revive();
		}),
		nullptr
	));
}

void EntityHealthBehaviorBase::revive()
{
	this->health = this->getMaxHealth();

	if (this->entity != nullptr)
	{
		this->entity->getAnimations()->playAnimation();
	}
}

bool EntityHealthBehaviorBase::isAlive()
{
	return !this->isDead();
}

bool EntityHealthBehaviorBase::isDead()
{
	return this->health <= 0;
}

/*
void revive()
{
	this->health = this->getMaxHealth();
}*/
