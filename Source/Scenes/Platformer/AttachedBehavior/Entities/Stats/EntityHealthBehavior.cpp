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
#include "Scenes/Platformer/AttachedBehavior/Entities/Items/EntityInventoryBehavior.h"
#include "Scenes/Platformer/Inventory/EquipmentInventory.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Equipable.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

EntityHealthBehavior* EntityHealthBehavior::create(GameObject* owner)
{
	EntityHealthBehavior* instance = new EntityHealthBehavior(owner);

	instance->autorelease();

	return instance;
}

EntityHealthBehavior::EntityHealthBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);
	this->equipmentInventory = nullptr;
	this->cachedMaxHealth = 0;

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
	else
	{
		this->entity->setState(StateKeys::MaxHealth, Value(this->getMaxHealth()), false);
		this->entity->setState(StateKeys::Health, Value(this->getMaxHealth()), false);
	}
}

EntityHealthBehavior::~EntityHealthBehavior()
{
}

void EntityHealthBehavior::onLoad()
{
	if (this->entity == nullptr)
	{
		return;
	}

	this->entity->getAttachedBehavior<EntityInventoryBehavior>([&](EntityInventoryBehavior* entityInventoryBehavior)
	{
		this->equipmentInventory = entityInventoryBehavior->getEquipmentInventory();
	});

	this->entity->listenForStateWrite(StateKeys::IsAlive, [=](Value value)
	{
		if (value.asBool())
		{
			this->revive();
		}
		else
		{
			this->kill(false);
		}
	});
}

void EntityHealthBehavior::onDisable()
{
	super::onDisable();
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
	if (this->entity == nullptr || (checkDeath && this->isDead()))
	{
		return;
	}

	bool wasAlive = this->isAlive();

	health = MathUtils::clamp(health, 0, this->getMaxHealth());
	this->entity->setState(StateKeys::Health, Value(health), false);

	if (!this->isAlive())
	{
		this->entity->getAnimations()->clearAnimationPriority();
		this->entity->getAnimations()->playAnimation("Death", SmartAnimationNode::AnimationPlayMode::PauseOnAnimationComplete, 1.0f);
	}

	if (this->isAlive() != wasAlive)
	{
		this->entity->setState(StateKeys::IsAlive, Value(this->isAlive()), true);
	}
}

int EntityHealthBehavior::getMaxHealth()
{
	int maxHealth = StatsTables::getBaseHealth(this->entity);

	if (equipmentInventory != nullptr)
	{
		for (auto equipment : this->equipmentInventory->getEquipment())
		{
			maxHealth += equipment->getItemStats().healthBonus;
		}
	}

	if (this->cachedMaxHealth != maxHealth)
	{
		this->cachedMaxHealth = maxHealth;
		this->entity->setState(StateKeys::MaxHealth, Value(maxHealth));
	}
	
	return maxHealth;
}

void EntityHealthBehavior::kill(bool playAnimation)
{
	if (this->entity == nullptr)
	{
		return;
	}

	this->setHealth(0, false);

	if (playAnimation)
	{
		this->entity->getAnimations()->clearAnimationPriority();
		this->entity->getAnimations()->playAnimation("Death", SmartAnimationNode::AnimationPlayMode::PauseOnAnimationComplete, 1.0f);
	}
	else
	{
		this->entity->getAnimations()->clearAnimationPriority();
		this->entity->getAnimations()->playAnimation("Dead", SmartAnimationNode::AnimationPlayMode::PauseOnAnimationComplete, 1.0f);
	}
}

void EntityHealthBehavior::revive()
{
	if (this->entity == nullptr)
	{
		return;
	}

	this->setHealth(this->getMaxHealth(), false);

	this->entity->getAnimations()->clearAnimationPriority();
	this->entity->getAnimations()->playAnimation();
}

bool EntityHealthBehavior::isAlive()
{
	return !this->isDead();
}

bool EntityHealthBehavior::isDead()
{
	return this->entity->getStateOrDefault(StateKeys::Health, Value(0)).asInt() <= 0;
}
