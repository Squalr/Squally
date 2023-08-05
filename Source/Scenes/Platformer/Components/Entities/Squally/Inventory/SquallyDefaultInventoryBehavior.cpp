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
#include "Scenes/Platformer/Components/Entities/Inventory/EntityInventoryBehavior.h"
#include "Scenes/Platformer/Inventory/EquipmentInventory.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"
#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/EntityResources.h"

using namespace cocos2d;

const std::string SquallyDefaultInventoryBehavior::MapKey = "squally-default-inventory-behavior";

// DeveloperModeController::IsDeveloperBuild must also be true for this to take effect
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
	if (SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyHasGivenDefaultItems, Value(false)).asBool())
	{
		return;
	}

	this->squally->watchForComponent<EntityInventoryBehavior>([=](EntityInventoryBehavior* entityInventoryBehavior)
	{
		SaveManager::SoftSaveProfileData(SaveKeys::SaveKeyHasGivenDefaultItems, Value(true));

		// It is safe to add items to the player's inventory here for testing purposes, without fear of accidentally shipping this code live
		if (DeveloperModeController::IsDeveloperBuild && SquallyDefaultInventoryBehavior::GiveDeveloperItems)
		{
			entityInventoryBehavior->getInventory()->forceInsert(CryptKey::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(BucketHelm::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(SantaHat::create(), false);
			
			entityInventoryBehavior->getInventory()->forceInsert(BoneAxe::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(CopperAxe::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(CrystalAxe::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(DemonicAxe::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(FrostAxe::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(GoldenAxe::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(MithrilAxe::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(Scythe::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(SteelAxe::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(VoidAxe::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(WoodenAxe::create(), false);
			
			entityInventoryBehavior->getInventory()->forceInsert(BoneBow::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(CrystalBow::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(DemonicBow::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(GoldenBow::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(HuntersBow::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(IvyBow::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(SteelBow::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(VoidBow::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(WoodenBow::create(), false);

			entityInventoryBehavior->getInventory()->forceInsert(Bludgeon::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(BoneHammer::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(CopperMallet::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(CrystalMace::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(DemonicMace::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(GoldenMace::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(MithrilMace::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(SteelMace::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(VoidMace::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(WitchingMace::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(WoodenClub::create(), false);
			
			entityInventoryBehavior->getInventory()->forceInsert(AshenBlade::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(BoneSword::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(CandySword::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(CopperSword::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(CrystalSword::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(DemonicSword::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(Dreadmourn::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(FireSword::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(Frostbane::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(GoldenSword::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(MithrilSword::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(SteelSword::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(TheButcher::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(VoidSword::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(WoodenSword::create(), false);

			entityInventoryBehavior->getInventory()->forceInsert(BoneWand::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(ChieftainsWand::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(CrystalWand::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(DemonicWand::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(EmeraldWand::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(QuartzWand::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(SapphireWand::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(SerpentWand::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(SilverWand::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(TaserRod::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(VoidWand::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(WitchesWand::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(WoodenWand::create(), false);

			entityInventoryBehavior->getInventory()->forceInsert(AcolytesCap::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(ArchersHat::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(BarbedHelm::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(BrocksHelm::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(BucketHelm::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(ConchHelm::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(CopperHelm::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(CowboyHat::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(GoldenDungHelm::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(JoustingHelmet::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(LeatherCap::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(MithrilHelm::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(NecrobatHelm::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(OldShoe::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(PriestHat::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(SantaHat::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(SnailShellSpiked::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(VikingHelmet::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(WizardsHatWater::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(WizardsHatEarth::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(WizardsHat::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(WizardsHatShadow::create(), false);

			entityInventoryBehavior->getInventory()->forceInsert(PirateHat::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(TheGoldenEagle::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(TigersBane::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(WarlocksHeaddress::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(RoyalCrown::create(), false);

			entityInventoryBehavior->getInventory()->forceInsert(MagesGuildPrisonKey::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(HeartOfFire::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(HeartOfShadow::create(), false);

			entityInventoryBehavior->getInventory()->forceInsert(SuperiorManaFlask::create(), false);
			entityInventoryBehavior->getInventory()->forceInsert(IncrementManaFlask::create(), false);

			// Quest testing
			entityInventoryBehavior->getInventory()->forceInsert(HeliumBomb::create(), false);

			for (int index = 0; index < 7; index++)
			{
				entityInventoryBehavior->getInventory()->forceInsert(HealthPotion::create(), false);
				entityInventoryBehavior->getInventory()->forceInsert(ManaPotion::create(), false);
			}

			for (int index = 0; index < 3; index++)
			{
				entityInventoryBehavior->getInventory()->forceInsert(SmallBomb::create(), false);
			}
			
			for (int index = 0; index < 20; index++)
			{
				entityInventoryBehavior->getInventory()->forceInsert(Wood::create(), false);
				entityInventoryBehavior->getInventory()->forceInsert(Crystal::create(), false);
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

			entityInventoryBehavior->getCurrencyInventory()->addCurrency(IOU::getIOUIdentifier(), 78);

			this->defer([=]()
			{
				PlatformerEvents::TriggerEquippedItemsChanged();
			});
		}

		// Starting hexus deck
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
