#include "SquallyDefaultInventoryBehavior.h"

#include "cocos/base/CCValue.h"

#include "Engine/DeveloperMode/DeveloperModeController.h"
#include "Engine/Inventory/CurrencyInventory.h"
#include "Engine/Inventory/Item.h"
#include "Engine/Inventory/Inventory.h"
#include "Engine/Save/SaveManager.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"
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
		if (DeveloperModeController::IsDeveloperBuild)
		{
			entityInventoryBehavior->getEquipmentInventory()->forceInsert(SantaHat::create(), false);
			entityInventoryBehavior->getEquipmentInventory()->forceInsert(SteelSword::create(), false);

			entityInventoryBehavior->getInventory()->forceInsert(BattleAxePlans::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(AcolytesCap::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(ArchersHat::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(BarbedHelm::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(BrocksHelm::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(BucketHelm::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(ConchHelm::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(CopperHelm::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(CowboyHat::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(DemonShell::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(DepressingWig::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(DraksHelm::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(GardenersHat::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(GoldenDungHelm::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(GrandpasLuckyHat::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(GuardsHelmet::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(GunnersHat::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(JoustingHelmet::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(JesterHat::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(LeatherCap::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(MagesHatBlue::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(MagesHatRed::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(Monocle::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(NecrobatHelm::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(OldShoe::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(OrnateHat::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(PirateHat::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(PriestHat::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(ReindeerHat::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(RoyalCrown::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(SamuraiHat::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(SantaHat::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(ShamanTiara::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(SnailShell::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(SnailShellSpiked::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(SteelHelm::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(TheGoldenEagle::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(TheldarsHelm::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(Tiara::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(TigersBane::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(TopHat::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(ToySoldierHat::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(Turban::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(VikingHelmet::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(WarlocksHeaddress::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(WitchesHat::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(WizardsHat::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(WizardsHatArcane::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(WizardsHatEarth::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(WizardsHatShadow::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(WizardsHatWater::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(WolfHat::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(WolfHatWhite::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(WoodenPikeHelm::create(), false);

			for (int index = 0; index < 3; index++)
			{
				entityInventoryBehavior->getInventory()->forceInsert(HealthPotion::create(), false);
				entityInventoryBehavior->getInventory()->forceInsert(ManaPotion::create(), false);
			}
			
			for (int index = 0; index < 20; index++)
			{
				entityInventoryBehavior->getInventory()->forceInsert(Wood::create(), false);
				entityInventoryBehavior->getInventory()->forceInsert(LightWood::create(), false);
				entityInventoryBehavior->getInventory()->forceInsert(Iron::create(), false);
			}

			entityInventoryBehavior->getCurrencyInventory()->addCurrency(IOU::getIOUIdentifier(), 420);
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
