#include "EntityInventoryBehavior.h"

#include "Engine/Inventory/CurrencyInventory.h"
#include "Engine/Inventory/Item.h"
#include "Engine/Inventory/Inventory.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/Inventory/EquipmentInventory.h"

#include "Strings/Platformer/Notifications/ItemFound.h"

using namespace cocos2d;

const std::string EntityInventoryBehavior::MapKeyAttachedBehavior = "entity-inventory";

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
}

EntityInventoryBehavior::~EntityInventoryBehavior()
{
}

void EntityInventoryBehavior::onLoad()
{
	std::string inventorySaveKey = "";
	std::string equipmentSaveKey = "";
	std::string currencySaveKey = "";

	this->inventory = Inventory::create(inventorySaveKey);
	this->equipmentInventory = EquipmentInventory::create(equipmentSaveKey);
	this->currencyInventory = CurrencyInventory::create(currencySaveKey);

	this->addChild(this->inventory);
	this->addChild(this->equipmentInventory);
	this->addChild(this->currencyInventory);
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
