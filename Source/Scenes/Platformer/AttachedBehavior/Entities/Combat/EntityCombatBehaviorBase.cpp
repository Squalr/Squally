#include "EntityCombatBehaviorBase.h"

#include "Engine/Inventory/Inventory.h"
#include "Engine/Inventory/Item.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/StatsTables/StatsTables.h"
#include "Events/CombatEvents.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Inventory/EntityInventoryBehavior.h"
#include "Scenes/Platformer/Inventory/EquipmentInventory.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Equipable.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Health/IncrementHealthFlask/IncrementHealthFlask.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Resources/UIResources.h"

#include "Events/CombatEvents.h"

using namespace cocos2d;

EntityCombatBehaviorBase::EntityCombatBehaviorBase(GameObject* owner, std::vector<AttachedBehavior*> attachedBehavior) : super(owner, attachedBehavior)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);
	this->timelineSpeed = 1.0f;
	this->bonusArmor = 0;
	this->bonusAttack = 0;
	this->bonusMagicAttack = 0;
	this->bonusSpeed = 0.0f;

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
}

EntityCombatBehaviorBase::~EntityCombatBehaviorBase()
{
}

void EntityCombatBehaviorBase::setTimelineSpeedBase(float timelineSpeed)
{
	this->timelineSpeed = timelineSpeed;
}

float EntityCombatBehaviorBase::getTimelineSpeedBase()
{
	return this->timelineSpeed;
}

float EntityCombatBehaviorBase::getTimelineSpeed()
{
	return this->timelineSpeed + this->bonusSpeed;
}

void EntityCombatBehaviorBase::onLoad()
{
	this->entity->watchForAttachedBehavior<EntityInventoryBehavior>([=](EntityInventoryBehavior* inventoryBehavior)
	{
		for (auto next : inventoryBehavior->getEquipmentInventory()->getEquipment())
		{
			this->bonusArmor += next->getItemStats().armorBonus;
			this->bonusAttack += next->getItemStats().attackBonus;
			this->bonusMagicAttack += next->getItemStats().magicAttackBonus;
			this->bonusSpeed += next->getItemStats().speedBonus;
		}
	});
	
	StatsTables::Stats bonusStats = StatsTables::getBonusStats(this->entity);

	this->bonusArmor += bonusStats.armor;
	this->bonusAttack += bonusStats.attack;
	this->bonusMagicAttack += bonusStats.magicAttack;
	this->bonusSpeed += bonusStats.speed;
	
	this->addEventListener(EventListenerCustom::create(CombatEvents::EventStatsModifyDamageDealt, [=](EventCustom* eventCustom)
	{
		CombatEvents::ModifiableDamageOrHealingArgs* args = static_cast<CombatEvents::ModifiableDamageOrHealingArgs*>(eventCustom->getUserData());

		if (args != nullptr && args->caster == this->entity && !args->isHandled())
		{
			this->onBeforeDamageDealt(args);
		}
	}));
	
	this->addEventListener(EventListenerCustom::create(CombatEvents::EventStatsModifyDamageTaken, [=](EventCustom* eventCustom)
	{
		CombatEvents::ModifiableDamageOrHealingArgs* args = static_cast<CombatEvents::ModifiableDamageOrHealingArgs*>(eventCustom->getUserData());

		if (args != nullptr && args->caster == this->entity && !args->isHandled())
		{
			this->onBeforeDamageTaken(args);
		}
	}));
}

void EntityCombatBehaviorBase::onDisable()
{
	super::onDisable();
}

void EntityCombatBehaviorBase::onBeforeDamageTaken(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing)
{
	if (damageOrHealing->damageOrHealingValue <= 0)
	{
		return;
	}

	*(damageOrHealing->damageOrHealing) = std::max(0, damageOrHealing->damageOrHealingValue - this->bonusArmor);
}

void EntityCombatBehaviorBase::onBeforeDamageDealt(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing)
{
	if (damageOrHealing->damageOrHealingValue <= 0)
	{
		return;
	}
	
	switch(damageOrHealing->abilityType)
	{
		case AbilityType::Physical:
		{
			(*damageOrHealing->damageOrHealing) += this->bonusAttack;
			break;
		}
		default:
		{
			(*damageOrHealing->damageOrHealing) += this->bonusMagicAttack;
			break;
		}
	}
}
