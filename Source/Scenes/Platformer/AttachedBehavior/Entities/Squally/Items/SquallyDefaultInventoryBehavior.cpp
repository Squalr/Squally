#include "SquallyDefaultInventoryBehavior.h"

#include "cocos/base/CCValue.h"

#include "Engine/DeveloperMode/DeveloperModeController.h"
#include "Engine/Inventory/CurrencyInventory.h"
#include "Engine/Inventory/Item.h"
#include "Engine/Inventory/Inventory.h"
#include "Engine/Save/SaveManager.h"
#include "Events/PlatformerEvents.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Items/EntityInventoryBehavior.h"
#include "Scenes/Platformer/Inventory/EquipmentInventory.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"
#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/EntityResources.h"

using namespace cocos2d;

const std::string SquallyDefaultInventoryBehavior::MapKey = "squally-equipment-visuals";
bool SquallyDefaultInventoryBehavior::GiveDeveloperItems = true;

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

void SquallyDefaultInventoryBehavior::onDisable()
{
	super::onDisable();
}

void SquallyDefaultInventoryBehavior::giveDefaultItems()
{
	if (SaveManager::getProfileDataOrDefault(SaveKeys::SaveKeyHasGivenDefaultItems, Value(false)).asBool())
	{
		return;
	}

	this->squally->watchForAttachedBehavior<EntityInventoryBehavior>([=](EntityInventoryBehavior* entityInventoryBehavior)
	{
		SaveManager::SoftSaveProfileData(SaveKeys::SaveKeyHasGivenDefaultItems, Value(true));

		// Because the save key was patched in later, we need this code here until.... let's say April 2020
		// Alternatively, we can add logic to detect exceeding the max unique on cards, as those are the only items given
		if (!entityInventoryBehavior->getInventory()->getItems().empty() || !entityInventoryBehavior->getEquipmentInventory()->getItems().empty())
		{
			return;
		}

		// It is safe to add items to the player's inventory here for testing purposes, without fear of accidentally shipping this code live
		if (DeveloperModeController::IsDeveloperBuild && SquallyDefaultInventoryBehavior::GiveDeveloperItems)
		{
			entityInventoryBehavior->getInventory()->forceInsert(SantaHat::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(WoodenClub::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(WoodenAxe::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(CrystalBow::create(), false);
			entityInventoryBehavior->getEquipmentInventory()->forceInsert(WoodenSword::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(WoodenWand::create(), false);

			for (int index = 0; index < 3; index++)
			{
				entityInventoryBehavior->getInventory()->forceInsert(HealthPotion::create(), false);
				entityInventoryBehavior->getInventory()->forceInsert(ManaPotion::create(), false);
			}
			
			for (int index = 0; index < 20; index++)
			{
				entityInventoryBehavior->getInventory()->forceInsert(Wood::create(), false);
				entityInventoryBehavior->getInventory()->forceInsert(Tin::create(), false);
				entityInventoryBehavior->getInventory()->forceInsert(Copper::create(), false);
				entityInventoryBehavior->getInventory()->forceInsert(Iron::create(), false);
				entityInventoryBehavior->getInventory()->forceInsert(Gold::create(), false);
				entityInventoryBehavior->getInventory()->forceInsert(Quartz::create(), false);
				entityInventoryBehavior->getInventory()->forceInsert(Emerald::create(), false);
				entityInventoryBehavior->getInventory()->forceInsert(Sapphire::create(), false);
				entityInventoryBehavior->getInventory()->forceInsert(Diamond::create(), false);
				entityInventoryBehavior->getInventory()->forceInsert(Ruby::create(), false);
				entityInventoryBehavior->getInventory()->forceInsert(Mithril::create(), false);
				entityInventoryBehavior->getInventory()->forceInsert(Sulfur::create(), false);
				entityInventoryBehavior->getInventory()->forceInsert(Obsidian::create(), false);
				entityInventoryBehavior->getInventory()->forceInsert(VoidCrystal::create(), false);
			}

			entityInventoryBehavior->getCurrencyInventory()->addCurrency(IOU::getIOUIdentifier(), 420);

			PlatformerEvents::TriggerEquippedItemsChanged();
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

		entityInventoryBehavior->getInventory()->save();
		entityInventoryBehavior->getEquipmentInventory()->save();
	});
}
