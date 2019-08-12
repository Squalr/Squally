#include "EntityHealthBehavior.h"

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

EntityHealthBehavior* EntityHealthBehavior::create(GameObject* owner, std::string attachedBehaviorArgs)
{
	EntityHealthBehavior* instance = new EntityHealthBehavior(owner, attachedBehaviorArgs);

	instance->autorelease();

	return instance;
}

EntityHealthBehavior::EntityHealthBehavior(GameObject* owner, std::string attachedBehaviorArgs) : super(owner, attachedBehaviorArgs)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
	else
	{
		this->entity->setState(StateKeys::MaxHealth, Value(StatsTables::getBaseHealth(this->entity)), false);
		this->entity->setState(StateKeys::Health, Value(StatsTables::getBaseHealth(this->entity)), false);
	}
}

EntityHealthBehavior::~EntityHealthBehavior()
{
}

void EntityHealthBehavior::onLoad()
{
	this->listenForStateWrite(StateKeys::Health, [=](Value value)
	{
		this->setHealth(value.asInt());
	});

	this->listenForStateWrite(StateKeys::IsAlive, [=](Value value)
	{
		if (!value.asBool())
		{
			this->kill();
		}
		else
		{
			this->revive();
		}
	});

	this->listenForStateWrite(StateKeys::IsDead, [=](Value value)
	{
		if (value.asBool())
		{
			this->kill();
		}
		else
		{
			this->revive();
		}
	});
}

int EntityHealthBehavior::getHealth()
{
	return this->entity->getStateOrDefaultInt(StateKeys::Health, 0);
}

void EntityHealthBehavior::addHealth(int healthDelta)
{
	this->setHealth(this->getHealth() + healthDelta);
}

void EntityHealthBehavior::setHealth(int health, bool checkDeath)
{
	if (checkDeath && this->isDead())
	{
		return;
	}

	health = MathUtils::clamp(health, 0, this->entity->getStateOrDefaultInt(StateKeys::MaxHealth, 0));
	this->entity->setState(StateKeys::Health, Value(health), false);
	this->entity->setState(StateKeys::IsAlive, Value(this->isAlive()), false);
	this->entity->setState(StateKeys::IsDead, Value(this->isDead()), false);

	if (this->entity != nullptr && this->entity->getStateOrDefaultInt(StateKeys::Health, 0) <= 0)
	{
		this->entity->getAnimations()->playAnimation("Death", SmartAnimationNode::AnimationPlayMode::PauseOnAnimationComplete);
	}
}

int EntityHealthBehavior::getMaxHealth()
{
	return this->entity == nullptr ? 0 :this->entity->getStateOrDefaultInt(StateKeys::MaxHealth, 0);
}

void EntityHealthBehavior::kill(bool loadDeadAnim)
{
	this->setHealth(0, false);

	if (loadDeadAnim && this->entity != nullptr)
	{
		this->entity->getAnimations()->playAnimation("Dead", SmartAnimationNode::AnimationPlayMode::PauseOnAnimationComplete);
	}
}

void EntityHealthBehavior::revive()
{
	this->setHealth(this->getMaxHealth(), false);

	if (this->entity != nullptr)
	{
		this->entity->getAnimations()->playAnimation();
	}
}

bool EntityHealthBehavior::isAlive()
{
	return !this->isDead();
}

bool EntityHealthBehavior::isDead()
{
	return this->entity->getStateOrDefault(StateKeys::Health, Value(0)).asInt() <= 0;
}
