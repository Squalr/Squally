#include "EntityInventoryBehavior.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Engine/Inventory/Item.h"
#include "Engine/Inventory/Inventory.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Scenes/Platformer/Inventory/EquipmentInventory.h"
#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string EntityInventoryBehavior::MapKey = "entity-inventory";

EntityInventoryBehavior* EntityInventoryBehavior::create(GameObject* owner)
{
	EntityInventoryBehavior* instance = new EntityInventoryBehavior(owner);

	instance->autorelease();

	return instance;
}

EntityInventoryBehavior::EntityInventoryBehavior(GameObject* owner) : super(owner)
{
	this->platformerEntity = dynamic_cast<PlatformerEntity*>(owner);

	if (this->platformerEntity == nullptr)
	{
		this->invalidate();
	}
	else
	{
		std::string inventorySaveKey = "";
		std::string equipmentSaveKey = "";
		std::string currencySaveKey = "";

		// A little bit of bad practice, but this is the only exception, so who gives a shit
		if (dynamic_cast<Squally*>(this->platformerEntity) != nullptr)
		{
			inventorySaveKey = SaveKeys::SaveKeySquallyInventory;
			equipmentSaveKey = SaveKeys::SaveKeySquallyEquipment;
			currencySaveKey = SaveKeys::SaveKeySquallyCurrencyInventory;
		}

		this->inventory = Inventory::create(inventorySaveKey);
		this->equipmentInventory = EquipmentInventory::create(equipmentSaveKey);
		this->currencyInventory = CurrencyInventory::create(currencySaveKey);

		this->addChild(this->inventory);
		this->addChild(this->equipmentInventory);
		this->addChild(this->currencyInventory);
	}
}

EntityInventoryBehavior::~EntityInventoryBehavior()
{
}

void EntityInventoryBehavior::onLoad()
{
}

void EntityInventoryBehavior::onDisable()
{
	super::onDisable();
}

std::vector<Inventory*> EntityInventoryBehavior::getAllInventories()
{
	return { this->inventory, this->equipmentInventory };
}

Inventory* EntityInventoryBehavior::getInventory()
{
	return this->inventory;
}

EquipmentInventory* EntityInventoryBehavior::getEquipmentInventory()
{
	return this->equipmentInventory;
}

CurrencyInventory* EntityInventoryBehavior::getCurrencyInventory()
{
	return this->currencyInventory;
}
