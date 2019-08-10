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
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

EntityHealthBehaviorBase::EntityHealthBehaviorBase(GameObject* owner, std::string attachedBehaviorArgs) : super(owner, attachedBehaviorArgs)
{
	this->entity = static_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
	else
	{
		this->entity->setState(StateKeys::MaxHealth, Value(StatsTables::getBaseHealth(this->entity)));
		this->entity->setState(StateKeys::Health, Value(StatsTables::getBaseHealth(this->entity)));
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
	return this->entity->getStateOrDefault(StateKeys::Health, Value(0)).asInt();
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

	health = MathUtils::clamp(health, 0, this->entity->getStateOrDefault(StateKeys::MaxHealth, Value(0)).asInt());
	this->entity->setState(StateKeys::Health, Value(health));
	this->entity->setState(StateKeys::IsAlive, Value(this->isAlive()));
	this->entity->setState(StateKeys::IsDead, Value(this->isDead()));

	if (this->entity != nullptr && this->entity->getStateOrDefault(StateKeys::Health, Value(0)).asInt() <= 0)
	{
		this->entity->getAnimations()->playAnimation("Death", SmartAnimationNode::AnimationPlayMode::PauseOnAnimationComplete);
	}
}

int EntityHealthBehaviorBase::getMaxHealth()
{
	return this->entity == nullptr ? 0 :this->entity->getStateOrDefault(StateKeys::MaxHealth, Value(0)).asInt();
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
	this->setHealth(this->getMaxHealth());

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
	return this->entity->getStateOrDefault(StateKeys::Health, Value(0)).asInt() <= 0;
}

/*
void revive()
{
	this->health = this->getMaxHealth();
}*/
