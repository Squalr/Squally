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

EntityInventoryBehavior::EntityInventoryBehavior(GameObject* owner, std::string inventorySaveKey, std::string equipmentSaveKey, std::string currencySaveKey) : super(owner)
{
	this->platformerEntity = dynamic_cast<PlatformerEntity*>(owner);

	if (this->platformerEntity == nullptr)
	{
		this->invalidate();
	}
	else
	{
		this->inventory = Inventory::create(inventorySaveKey);
		this->equipmentInventory = EquipmentInventory::create(equipmentSaveKey);
		this->currencyInventory = CurrencyInventory::create(currencySaveKey);

		this->buildAllInventories();

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

const std::vector<Inventory*>& EntityInventoryBehavior::getAllInventories()
{
	return allInventories;
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

void EntityInventoryBehavior::redirectInventoryTo(Inventory* inventory)
{
	// This is devil magic to allow helpers in combat to share an inventory. Their inventories are simply redirected to point to the players.
	this->inventory = inventory;
	this->buildAllInventories();
}

void EntityInventoryBehavior::buildAllInventories()
{
	this->allInventories.clear();
	this->allInventories.push_back(this->inventory);
	this->allInventories.push_back(this->equipmentInventory);
}
