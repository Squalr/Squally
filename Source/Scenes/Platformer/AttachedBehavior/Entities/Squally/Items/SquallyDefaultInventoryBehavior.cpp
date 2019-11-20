#include "SquallyDefaultInventoryBehavior.h"

#include "Engine/Inventory/Item.h"
#include "Engine/Inventory/Inventory.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Items/EntityInventoryBehavior.h"
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
	this->squally->getAttachedBehavior<EntityInventoryBehavior>([=](EntityInventoryBehavior* entityInventoryBehavior)
	{
		if (!entityInventoryBehavior->getInventory()->getItems().empty() || !entityInventoryBehavior->getEquipmentInventory()->getItems().empty())
		{
			return;
		}
		
		entityInventoryBehavior->getEquipmentInventory()->forceInsert(Binary0::create(), false);
		entityInventoryBehavior->getInventory()->forceInsert(Binary0::create(), false);
		entityInventoryBehavior->getEquipmentInventory()->forceInsert(Binary1::create(), false);
		entityInventoryBehavior->getInventory()->forceInsert(Binary1::create(), false);
		entityInventoryBehavior->getEquipmentInventory()->forceInsert(Binary2::create(), false);
		entityInventoryBehavior->getEquipmentInventory()->forceInsert(Binary2::create(), false);
		entityInventoryBehavior->getEquipmentInventory()->forceInsert(Binary3::create(), false);
		entityInventoryBehavior->getEquipmentInventory()->forceInsert(Binary3::create(), false);
		entityInventoryBehavior->getEquipmentInventory()->forceInsert(Binary4::create(), false);
		entityInventoryBehavior->getEquipmentInventory()->forceInsert(Decimal0::create(), false);
		entityInventoryBehavior->getEquipmentInventory()->forceInsert(Decimal0::create(), false);
		entityInventoryBehavior->getEquipmentInventory()->forceInsert(Decimal1::create(), false);
		entityInventoryBehavior->getInventory()->forceInsert(Decimal1::create(), false);
		entityInventoryBehavior->getEquipmentInventory()->forceInsert(Decimal2::create(), false);
		entityInventoryBehavior->getEquipmentInventory()->forceInsert(Decimal2::create(), false);
		entityInventoryBehavior->getEquipmentInventory()->forceInsert(Decimal3::create(), false);
		entityInventoryBehavior->getEquipmentInventory()->forceInsert(Decimal3::create(), false);
		entityInventoryBehavior->getEquipmentInventory()->forceInsert(Decimal4::create(), false);
		entityInventoryBehavior->getEquipmentInventory()->forceInsert(Hex0::create(), false);
		entityInventoryBehavior->getEquipmentInventory()->forceInsert(Hex0::create(), false);
		entityInventoryBehavior->getEquipmentInventory()->forceInsert(Hex1::create(), false);
		entityInventoryBehavior->getEquipmentInventory()->forceInsert(Hex1::create(), false);
		entityInventoryBehavior->getEquipmentInventory()->forceInsert(Hex1::create(), false);
		entityInventoryBehavior->getInventory()->forceInsert(Hex2::create(), false);
		entityInventoryBehavior->getEquipmentInventory()->forceInsert(Hex2::create(), false);
		entityInventoryBehavior->getEquipmentInventory()->forceInsert(Hex3::create(), false);
		entityInventoryBehavior->getEquipmentInventory()->forceInsert(Hex3::create(), false);
		entityInventoryBehavior->getEquipmentInventory()->forceInsert(Hex4::create(), false);
		entityInventoryBehavior->getEquipmentInventory()->forceInsert(SpecialMov::create(), false);
		entityInventoryBehavior->getEquipmentInventory()->forceInsert(SpecialMov::create(), false);
		entityInventoryBehavior->getEquipmentInventory()->forceInsert(SpecialAdd::create(), false);
		entityInventoryBehavior->getEquipmentInventory()->forceInsert(SpecialAdd::create(), false);
		entityInventoryBehavior->getEquipmentInventory()->forceInsert(SpecialShl::create(), false);
		entityInventoryBehavior->getEquipmentInventory()->forceInsert(SpecialShr::create(), false);

		entityInventoryBehavior->getInventory()->save();
		entityInventoryBehavior->getEquipmentInventory()->save();
	});
}
