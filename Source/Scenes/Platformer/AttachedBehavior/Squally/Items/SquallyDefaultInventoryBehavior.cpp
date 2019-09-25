#include "SquallyDefaultInventoryBehavior.h"

#include "Engine/Inventory/Item.h"
#include "Engine/Inventory/Inventory.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Scenes/Platformer/Inventory/EquipmentInventory.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"
#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/EntityResources.h"

using namespace cocos2d;

const std::string SquallyDefaultInventoryBehavior::MapKeyAttachedBehavior = "squally-equipment-visuals";

SquallyDefaultInventoryBehavior* SquallyDefaultInventoryBehavior::create(GameObject* owner)
{
	SquallyDefaultInventoryBehavior* instance = new SquallyDefaultInventoryBehavior(owner);

	instance->autorelease();

	return instance;
}

SquallyDefaultInventoryBehavior::SquallyDefaultInventoryBehavior(GameObject* owner) : super(owner)
{
	this->squally = dynamic_cast<Squally*>(owner);

	if (this->squally == nullptr)
	{
		this->invalidate();
	}
}

SquallyDefaultInventoryBehavior::~SquallyDefaultInventoryBehavior()
{
}

void SquallyDefaultInventoryBehavior::onLoad()
{
	this->giveDefaultItems();
}

void SquallyDefaultInventoryBehavior::giveDefaultItems()
{
	if (!this->squally->getInventory()->getItems().empty() || !this->squally->getEquipmentInventory()->getItems().empty())
	{
		return;
	}
	
	this->squally->getEquipmentInventory()->forceInsert(Binary0::create(), false);
	this->squally->getEquipmentInventory()->forceInsert(Binary0::create(), false);
	this->squally->getEquipmentInventory()->forceInsert(Binary1::create(), false);
	this->squally->getEquipmentInventory()->forceInsert(Binary1::create(), false);
	this->squally->getEquipmentInventory()->forceInsert(Binary2::create(), false);
	this->squally->getEquipmentInventory()->forceInsert(Binary2::create(), false);
	this->squally->getEquipmentInventory()->forceInsert(Binary3::create(), false);
	this->squally->getEquipmentInventory()->forceInsert(Binary3::create(), false);
	this->squally->getEquipmentInventory()->forceInsert(Decimal0::create(), false);
	this->squally->getEquipmentInventory()->forceInsert(Decimal0::create(), false);
	this->squally->getEquipmentInventory()->forceInsert(Decimal1::create(), false);
	this->squally->getEquipmentInventory()->forceInsert(Decimal1::create(), false);
	this->squally->getEquipmentInventory()->forceInsert(Decimal2::create(), false);
	this->squally->getEquipmentInventory()->forceInsert(Decimal2::create(), false);
	this->squally->getEquipmentInventory()->forceInsert(Decimal3::create(), false);
	this->squally->getEquipmentInventory()->forceInsert(Decimal3::create(), false);
	this->squally->getEquipmentInventory()->forceInsert(Hex0::create(), false);
	this->squally->getEquipmentInventory()->forceInsert(Hex0::create(), false);
	this->squally->getEquipmentInventory()->forceInsert(Hex1::create(), false);
	this->squally->getEquipmentInventory()->forceInsert(Hex1::create(), false);
	this->squally->getEquipmentInventory()->forceInsert(Hex2::create(), false);
	this->squally->getEquipmentInventory()->forceInsert(Hex2::create(), false);
	this->squally->getEquipmentInventory()->forceInsert(Hex3::create(), false);
	this->squally->getEquipmentInventory()->forceInsert(Hex3::create(), false);

	this->squally->getInventory()->save();
	this->squally->getEquipmentInventory()->save();
}
