#include "EntityManaBehavior.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/SaveEvents.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/Utils/MathUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/StatsTables/StatsTables.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Inventory/EntityInventoryBehavior.h"
#include "Scenes/Platformer/Inventory/EquipmentInventory.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Equipable.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

EntityManaBehavior* EntityManaBehavior::create(GameObject* owner)
{
	EntityManaBehavior* instance = new EntityManaBehavior(owner);

	instance->autorelease();

	return instance;
}

EntityManaBehavior::EntityManaBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);
	this->equipmentInventory = nullptr;
	this->cachedMaxMana = 0;

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
	else
	{
		this->entity->setState(StateKeys::MaxMana, Value(this->getMaxMana()), false);
		this->entity->setState(StateKeys::Mana, Value(this->getMaxMana()), false);
	}
}

EntityManaBehavior::~EntityManaBehavior()
{
}

void EntityManaBehavior::onLoad()
{
	if (this->entity == nullptr)
	{
		return;
	}

	this->addEventListenerIgnorePause(EventListenerCustom::create(PlatformerEvents::EventEquippedItemsChanged, [=](EventCustom* eventCustom)
	{
		// Refresh max mana
		this->getMaxMana();
	}));

	this->entity->getAttachedBehavior<EntityInventoryBehavior>([&](EntityInventoryBehavior* entityInventoryBehavior)
	{
		this->equipmentInventory = entityInventoryBehavior->getEquipmentInventory();

		// Refresh max mana
		this->getMaxMana();
	});

	this->entity->listenForStateWrite(StateKeys::IsAlive, [=](Value value)
	{
		if (value.asBool())
		{
			this->onRevive();
		}
	});
}

void EntityManaBehavior::onDisable()
{
	super::onDisable();
}

int EntityManaBehavior::getMana()
{
	return this->entity->getStateOrDefaultInt(StateKeys::Mana, 0);
}

void EntityManaBehavior::addMana(int manaDelta)
{
	this->setMana(this->getMana() + manaDelta);
}

void EntityManaBehavior::setMana(int mana)
{
	mana = MathUtils::clamp(mana, 0, this->getMaxMana());
	this->entity->setState(StateKeys::Mana, Value(mana), true);
}

int EntityManaBehavior::getMaxMana()
{
	int maxMana = StatsTables::getBaseMana(this->entity);

	if (this->equipmentInventory != nullptr)
	{
		for (auto equipment : this->equipmentInventory->getEquipment())
		{
			maxMana += equipment->getItemStats().manaBonus;
		}
	}

	if (this->cachedMaxMana != maxMana)
	{
		this->cachedMaxMana = maxMana;
		this->entity->setState(StateKeys::MaxMana, Value(maxMana));
	}
	
	return maxMana;
}

void EntityManaBehavior::onRevive()
{
	this->setMana(this->getMaxMana());
}
