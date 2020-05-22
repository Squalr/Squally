#include "PlatformerItemDeserializer.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/GlobalDirector.h"
#include "Engine/Inventory/Item.h"
#include "Engine/Utils/LogUtils.h"

#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

PlatformerItemDeserializer* PlatformerItemDeserializer::instance = nullptr;

PlatformerItemDeserializer* PlatformerItemDeserializer::getInstance()
{
	if (PlatformerItemDeserializer::instance == nullptr)
	{
		PlatformerItemDeserializer::instance = new PlatformerItemDeserializer();

		instance->autorelease();
	}

	return PlatformerItemDeserializer::instance;
}

void PlatformerItemDeserializer::registerGlobalNode()
{
	// Register this class globally so that it can always listen for events
	GlobalDirector::getInstance()->registerGlobalNode(PlatformerItemDeserializer::getInstance());
}

PlatformerItemDeserializer::PlatformerItemDeserializer()
{
	this->deserializers = std::map<std::string, std::function<Item*()>>();

	// Hexus Cards
	this->deserializers[Binary0::SaveKey] = [=]() { return (Item*)Binary0::create(); };
	this->deserializers[Binary1::SaveKey] = [=]() { return (Item*)Binary1::create(); };
	this->deserializers[Binary2::SaveKey] = [=]() { return (Item*)Binary2::create(); };
	this->deserializers[Binary3::SaveKey] = [=]() { return (Item*)Binary3::create(); };
	this->deserializers[Binary4::SaveKey] = [=]() { return (Item*)Binary4::create(); };
	this->deserializers[Binary5::SaveKey] = [=]() { return (Item*)Binary5::create(); };
	this->deserializers[Binary6::SaveKey] = [=]() { return (Item*)Binary6::create(); };
	this->deserializers[Binary7::SaveKey] = [=]() { return (Item*)Binary7::create(); };
	this->deserializers[Binary8::SaveKey] = [=]() { return (Item*)Binary8::create(); };
	this->deserializers[Binary9::SaveKey] = [=]() { return (Item*)Binary9::create(); };
	this->deserializers[Binary10::SaveKey] = [=]() { return (Item*)Binary10::create(); };
	this->deserializers[Binary11::SaveKey] = [=]() { return (Item*)Binary11::create(); };
	this->deserializers[Binary12::SaveKey] = [=]() { return (Item*)Binary12::create(); };
	this->deserializers[Binary13::SaveKey] = [=]() { return (Item*)Binary13::create(); };
	this->deserializers[Binary14::SaveKey] = [=]() { return (Item*)Binary15::create(); };
	this->deserializers[Binary15::SaveKey] = [=]() { return (Item*)Binary15::create(); };

	this->deserializers[Decimal0::SaveKey] = [=]() { return (Item*)Decimal0::create(); };
	this->deserializers[Decimal1::SaveKey] = [=]() { return (Item*)Decimal1::create(); };
	this->deserializers[Decimal2::SaveKey] = [=]() { return (Item*)Decimal2::create(); };
	this->deserializers[Decimal3::SaveKey] = [=]() { return (Item*)Decimal3::create(); };
	this->deserializers[Decimal4::SaveKey] = [=]() { return (Item*)Decimal4::create(); };
	this->deserializers[Decimal5::SaveKey] = [=]() { return (Item*)Decimal5::create(); };
	this->deserializers[Decimal6::SaveKey] = [=]() { return (Item*)Decimal6::create(); };
	this->deserializers[Decimal7::SaveKey] = [=]() { return (Item*)Decimal7::create(); };
	this->deserializers[Decimal8::SaveKey] = [=]() { return (Item*)Decimal8::create(); };
	this->deserializers[Decimal9::SaveKey] = [=]() { return (Item*)Decimal9::create(); };
	this->deserializers[Decimal10::SaveKey] = [=]() { return (Item*)Decimal10::create(); };
	this->deserializers[Decimal11::SaveKey] = [=]() { return (Item*)Decimal11::create(); };
	this->deserializers[Decimal12::SaveKey] = [=]() { return (Item*)Decimal12::create(); };
	this->deserializers[Decimal13::SaveKey] = [=]() { return (Item*)Decimal13::create(); };
	this->deserializers[Decimal14::SaveKey] = [=]() { return (Item*)Decimal15::create(); };
	this->deserializers[Decimal15::SaveKey] = [=]() { return (Item*)Decimal15::create(); };
	
	this->deserializers[Hex0::SaveKey] = [=]() { return (Item*)Hex0::create(); };
	this->deserializers[Hex1::SaveKey] = [=]() { return (Item*)Hex1::create(); };
	this->deserializers[Hex2::SaveKey] = [=]() { return (Item*)Hex2::create(); };
	this->deserializers[Hex3::SaveKey] = [=]() { return (Item*)Hex3::create(); };
	this->deserializers[Hex4::SaveKey] = [=]() { return (Item*)Hex4::create(); };
	this->deserializers[Hex5::SaveKey] = [=]() { return (Item*)Hex5::create(); };
	this->deserializers[Hex6::SaveKey] = [=]() { return (Item*)Hex6::create(); };
	this->deserializers[Hex7::SaveKey] = [=]() { return (Item*)Hex7::create(); };
	this->deserializers[Hex8::SaveKey] = [=]() { return (Item*)Hex8::create(); };
	this->deserializers[Hex9::SaveKey] = [=]() { return (Item*)Hex9::create(); };
	this->deserializers[Hex10::SaveKey] = [=]() { return (Item*)Hex10::create(); };
	this->deserializers[Hex11::SaveKey] = [=]() { return (Item*)Hex11::create(); };
	this->deserializers[Hex12::SaveKey] = [=]() { return (Item*)Hex12::create(); };
	this->deserializers[Hex13::SaveKey] = [=]() { return (Item*)Hex13::create(); };
	this->deserializers[Hex14::SaveKey] = [=]() { return (Item*)Hex15::create(); };
	this->deserializers[Hex15::SaveKey] = [=]() { return (Item*)Hex15::create(); };

	this->deserializers[SpecialAbsorb::SaveKey] = [=]() { return (Item*)SpecialAbsorb::create(); };
	this->deserializers[SpecialAdd::SaveKey] = [=]() { return (Item*)SpecialAdd::create(); };
	this->deserializers[SpecialAnd::SaveKey] = [=]() { return (Item*)SpecialAnd::create(); };
	this->deserializers[SpecialFlip1::SaveKey] = [=]() { return (Item*)SpecialFlip1::create(); };
	this->deserializers[SpecialFlip2::SaveKey] = [=]() { return (Item*)SpecialFlip2::create(); };
	this->deserializers[SpecialFlip3::SaveKey] = [=]() { return (Item*)SpecialFlip3::create(); };
	this->deserializers[SpecialFlip4::SaveKey] = [=]() { return (Item*)SpecialFlip4::create(); };

	this->deserializers[SpecialGreed::SaveKey] = [=]() { return (Item*)SpecialGreed::create(); };
	this->deserializers[SpecialInv::SaveKey] = [=]() { return (Item*)SpecialInv::create(); };
	this->deserializers[SpecialMov::SaveKey] = [=]() { return (Item*)SpecialMov::create(); };
	this->deserializers[SpecialOr::SaveKey] = [=]() { return (Item*)SpecialOr::create(); };
	this->deserializers[SpecialPeek::SaveKey] = [=]() { return (Item*)SpecialPeek::create(); };
	this->deserializers[SpecialShl::SaveKey] = [=]() { return (Item*)SpecialShl::create(); };
	this->deserializers[SpecialShlCircular::SaveKey] = [=]() { return (Item*)SpecialShlCircular::create(); };
	this->deserializers[SpecialShr::SaveKey] = [=]() { return (Item*)SpecialShr::create(); };
	this->deserializers[SpecialShrCircular::SaveKey] = [=]() { return (Item*)SpecialShrCircular::create(); };
	this->deserializers[SpecialSteal::SaveKey] = [=]() { return (Item*)SpecialSteal::create(); };
	this->deserializers[SpecialSub::SaveKey] = [=]() { return (Item*)SpecialSub::create(); };
	this->deserializers[SpecialXor::SaveKey] = [=]() { return (Item*)SpecialXor::create(); };

	// Crafting
	this->deserializers[Bone::SaveKey] = [=]() { return (Item*)Bone::create(); };
	this->deserializers[Coal::SaveKey] = [=]() { return (Item*)Coal::create(); };
	this->deserializers[Copper::SaveKey] = [=]() { return (Item*)Copper::create(); };
	this->deserializers[Diamond::SaveKey] = [=]() { return (Item*)Diamond::create(); };
	this->deserializers[Emerald::SaveKey] = [=]() { return (Item*)Emerald::create(); };
	this->deserializers[Gold::SaveKey] = [=]() { return (Item*)Gold::create(); };
	this->deserializers[Iron::SaveKey] = [=]() { return (Item*)Iron::create(); };
	this->deserializers[Mithril::SaveKey] = [=]() { return (Item*)Mithril::create(); };
	this->deserializers[Obsidian::SaveKey] = [=]() { return (Item*)Obsidian::create(); };
	this->deserializers[Quartz::SaveKey] = [=]() { return (Item*)Quartz::create(); };
	this->deserializers[Ruby::SaveKey] = [=]() { return (Item*)Ruby::create(); };
	this->deserializers[Sapphire::SaveKey] = [=]() { return (Item*)Sapphire::create(); };
	this->deserializers[Sulfur::SaveKey] = [=]() { return (Item*)Sulfur::create(); };
	this->deserializers[Tin::SaveKey] = [=]() { return (Item*)Tin::create(); };
	this->deserializers[VoidCrystal::SaveKey] = [=]() { return (Item*)VoidCrystal::create(); };
	
	this->deserializers[DarkWood::SaveKey] = [=]() { return (Item*)DarkWood::create(); };
	this->deserializers[LightWood::SaveKey] = [=]() { return (Item*)LightWood::create(); };
	this->deserializers[Wood::SaveKey] = [=]() { return (Item*)Wood::create(); };

	this->deserializers[Clover::SaveKey] = [=]() { return (Item*)Clover::create(); };
	this->deserializers[DarkSeed::SaveKey] = [=]() { return (Item*)DarkSeed::create(); };
	this->deserializers[DemonRoot::SaveKey] = [=]() { return (Item*)DemonRoot::create(); };
	this->deserializers[FrostBerries::SaveKey] = [=]() { return (Item*)FrostBerries::create(); };
	this->deserializers[GoldWeed::SaveKey] = [=]() { return (Item*)GoldWeed::create(); };
	this->deserializers[Mandrake::SaveKey] = [=]() { return (Item*)Mandrake::create(); };
	this->deserializers[PoisonMushroom::SaveKey] = [=]() { return (Item*)PoisonMushroom::create(); };
	this->deserializers[SandRoot::SaveKey] = [=]() { return (Item*)SandRoot::create(); };
	this->deserializers[VoidFlower::SaveKey] = [=]() { return (Item*)VoidFlower::create(); };

	this->deserializers[BlackBlood::SaveKey] = [=]() { return (Item*)BlackBlood::create(); };
	this->deserializers[DemonSkull::SaveKey] = [=]() { return (Item*)DemonSkull::create(); };
	this->deserializers[Egg::SaveKey] = [=]() { return (Item*)Egg::create(); };
	this->deserializers[Eggplant::SaveKey] = [=]() { return (Item*)Eggplant::create(); };
	this->deserializers[Feather::SaveKey] = [=]() { return (Item*)Feather::create(); };
	this->deserializers[Honey::SaveKey] = [=]() { return (Item*)Honey::create(); };
	this->deserializers[PhoenixFeather::SaveKey] = [=]() { return (Item*)PhoenixFeather::create(); };
	this->deserializers[Snowball::SaveKey] = [=]() { return (Item*)Snowball::create(); };

	// Consumables
	this->deserializers[HealthPotion::SaveKey] = [=]() { return (Item*)HealthPotion::create(); };
	this->deserializers[IncrementHealthFlask::SaveKey] = [=]() { return (Item*)IncrementHealthFlask::create(); };
	this->deserializers[ManaPotion::SaveKey] = [=]() { return (Item*)ManaPotion::create(); };

	// Axes
	this->deserializers[BoneAxe::SaveKey] = [=]() { return (Item*)BoneAxe::create(); };
	this->deserializers[CopperAxe::SaveKey] = [=]() { return (Item*)CopperAxe::create(); };
	this->deserializers[CrystalAxe::SaveKey] = [=]() { return (Item*)CrystalAxe::create(); };
	this->deserializers[DemonicAxe::SaveKey] = [=]() { return (Item*)DemonicAxe::create(); };
	this->deserializers[FrostAxe::SaveKey] = [=]() { return (Item*)FrostAxe::create(); };
	this->deserializers[GoldenAxe::SaveKey] = [=]() { return (Item*)GoldenAxe::create(); };
	this->deserializers[MithrilAxe::SaveKey] = [=]() { return (Item*)MithrilAxe::create(); };
	this->deserializers[Scythe::SaveKey] = [=]() { return (Item*)Scythe::create(); };
	this->deserializers[SteelAxe::SaveKey] = [=]() { return (Item*)SteelAxe::create(); };
	this->deserializers[Scythe::SaveKey] = [=]() { return (Item*)Scythe::create(); };
	this->deserializers[VoidAxe::SaveKey] = [=]() { return (Item*)VoidAxe::create(); };
	this->deserializers[WoodenAxe::SaveKey] = [=]() { return (Item*)WoodenAxe::create(); };

	// Bows
	this->deserializers[BoneBow::SaveKey] = [=]() { return (Item*)BoneBow::create(); };
	this->deserializers[CrystalBow::SaveKey] = [=]() { return (Item*)CrystalBow::create(); };
	this->deserializers[DemonicBow::SaveKey] = [=]() { return (Item*)DemonicBow::create(); };
	this->deserializers[GoldenBow::SaveKey] = [=]() { return (Item*)GoldenBow::create(); };
	this->deserializers[HuntersBow::SaveKey] = [=]() { return (Item*)HuntersBow::create(); };
	this->deserializers[IvyBow::SaveKey] = [=]() { return (Item*)IvyBow::create(); };
	this->deserializers[SteelBow::SaveKey] = [=]() { return (Item*)SteelBow::create(); };
	this->deserializers[VoidBow::SaveKey] = [=]() { return (Item*)VoidBow::create(); };
	this->deserializers[WoodenBow::SaveKey] = [=]() { return (Item*)WoodenBow::create(); };

	// Maces
	this->deserializers[Bludgeon::SaveKey] = [=]() { return (Item*)Bludgeon::create(); };
	this->deserializers[BoneHammer::SaveKey] = [=]() { return (Item*)BoneHammer::create(); };
	this->deserializers[CopperMallet::SaveKey] = [=]() { return (Item*)CopperMallet::create(); };
	this->deserializers[CrystalMace::SaveKey] = [=]() { return (Item*)CrystalMace::create(); };
	this->deserializers[CopperMallet::SaveKey] = [=]() { return (Item*)CopperMallet::create(); };
	this->deserializers[DemonicMace::SaveKey] = [=]() { return (Item*)DemonicMace::create(); };
	this->deserializers[GoldenMace::SaveKey] = [=]() { return (Item*)GoldenMace::create(); };
	this->deserializers[MithrilMace::SaveKey] = [=]() { return (Item*)MithrilMace::create(); };
	this->deserializers[SteelMace::SaveKey] = [=]() { return (Item*)SteelMace::create(); };
	this->deserializers[Timmy::SaveKey] = [=]() { return (Item*)Timmy::create(); };
	this->deserializers[VoidMace::SaveKey] = [=]() { return (Item*)VoidMace::create(); };
	this->deserializers[WitchingMace::SaveKey] = [=]() { return (Item*)WitchingMace::create(); };
	this->deserializers[WoodenClub::SaveKey] = [=]() { return (Item*)WoodenClub::create(); };

	// Swords
	this->deserializers[AshenBlade::SaveKey] = [=]() { return (Item*)AshenBlade::create(); };
	this->deserializers[BoneSword::SaveKey] = [=]() { return (Item*)BoneSword::create(); };
	this->deserializers[CandySword::SaveKey] = [=]() { return (Item*)CandySword::create(); };
	this->deserializers[CopperSword::SaveKey] = [=]() { return (Item*)CopperSword::create(); };
	this->deserializers[CrystalSword::SaveKey] = [=]() { return (Item*)CrystalSword::create(); };
	this->deserializers[DemonicSword::SaveKey] = [=]() { return (Item*)DemonicSword::create(); };
	this->deserializers[Dreadmourn::SaveKey] = [=]() { return (Item*)Dreadmourn::create(); };
	this->deserializers[FireSword::SaveKey] = [=]() { return (Item*)FireSword::create(); };
	this->deserializers[Frostbane::SaveKey] = [=]() { return (Item*)Frostbane::create(); };
	this->deserializers[GoldenSword::SaveKey] = [=]() { return (Item*)GoldenSword::create(); };
	this->deserializers[MithrilSword::SaveKey] = [=]() { return (Item*)MithrilSword::create(); };
	this->deserializers[SteelSword::SaveKey] = [=]() { return (Item*)SteelSword::create(); };
	this->deserializers[TheButcher::SaveKey] = [=]() { return (Item*)TheButcher::create(); };
	this->deserializers[VoidSword::SaveKey] = [=]() { return (Item*)VoidSword::create(); };
	this->deserializers[WoodenSword::SaveKey] = [=]() { return (Item*)WoodenSword::create(); };

	// Wands
	this->deserializers[BoneWand::SaveKey] = [=]() { return (Item*)BoneWand::create(); };
	this->deserializers[ChieftainsWand::SaveKey] = [=]() { return (Item*)ChieftainsWand::create(); };
	this->deserializers[CrystalWand::SaveKey] = [=]() { return (Item*)CrystalWand::create(); };
	this->deserializers[DemonicWand::SaveKey] = [=]() { return (Item*)DemonicWand::create(); };
	this->deserializers[EmeraldWand::SaveKey] = [=]() { return (Item*)EmeraldWand::create(); };
	this->deserializers[GoldenWand::SaveKey] = [=]() { return (Item*)GoldenWand::create(); };
	this->deserializers[QuartzWand::SaveKey] = [=]() { return (Item*)QuartzWand::create(); };
	this->deserializers[SapphireWand::SaveKey] = [=]() { return (Item*)SapphireWand::create(); };
	this->deserializers[SerpentWand::SaveKey] = [=]() { return (Item*)SerpentWand::create(); };
	this->deserializers[TaserRod::SaveKey] = [=]() { return (Item*)TaserRod::create(); };
	this->deserializers[VoidWand::SaveKey] = [=]() { return (Item*)VoidWand::create(); };
	this->deserializers[WitchesWand::SaveKey] = [=]() { return (Item*)WitchesWand::create(); };
	this->deserializers[WoodenWand::SaveKey] = [=]() { return (Item*)WoodenWand::create(); };

	// Hats
	this->deserializers[AcolytesCap::SaveKey] = [=]() { return (Item*)AcolytesCap::create(); };
	this->deserializers[ArchersHat::SaveKey] = [=]() { return (Item*)ArchersHat::create(); };
	this->deserializers[BarbedHelm::SaveKey] = [=]() { return (Item*)BarbedHelm::create(); };
	this->deserializers[BrocksHelm::SaveKey] = [=]() { return (Item*)BrocksHelm::create(); };
	this->deserializers[BucketHelm::SaveKey] = [=]() { return (Item*)BucketHelm::create(); };
	this->deserializers[ConchHelm::SaveKey] = [=]() { return (Item*)ConchHelm::create(); };
	this->deserializers[CopperHelm::SaveKey] = [=]() { return (Item*)CopperHelm::create(); };
	this->deserializers[CowboyHat::SaveKey] = [=]() { return (Item*)CowboyHat::create(); };
	this->deserializers[DemonShell::SaveKey] = [=]() { return (Item*)DemonShell::create(); };
	this->deserializers[DepressingWig::SaveKey] = [=]() { return (Item*)DepressingWig::create(); };
	this->deserializers[DraksHelm::SaveKey] = [=]() { return (Item*)DraksHelm::create(); };
	this->deserializers[GardenersHat::SaveKey] = [=]() { return (Item*)GardenersHat::create(); };
	this->deserializers[GoldenDungHelm::SaveKey] = [=]() { return (Item*)GoldenDungHelm::create(); };
	this->deserializers[GrandpasLuckyHat::SaveKey] = [=]() { return (Item*)GrandpasLuckyHat::create(); };
	this->deserializers[GuardsHelmet::SaveKey] = [=]() { return (Item*)GuardsHelmet::create(); };
	this->deserializers[GunnersHat::SaveKey] = [=]() { return (Item*)GunnersHat::create(); };
	this->deserializers[JesterHat::SaveKey] = [=]() { return (Item*)JesterHat::create(); };
	this->deserializers[JoustingHelmet::SaveKey] = [=]() { return (Item*)JoustingHelmet::create(); };
	this->deserializers[LeatherCap::SaveKey] = [=]() { return (Item*)LeatherCap::create(); };
	this->deserializers[MagesHatBlue::SaveKey] = [=]() { return (Item*)MagesHatBlue::create(); };
	this->deserializers[MagesHatRed::SaveKey] = [=]() { return (Item*)MagesHatRed::create(); };
	this->deserializers[Monocle::SaveKey] = [=]() { return (Item*)Monocle::create(); };
	this->deserializers[NecrobatHelm::SaveKey] = [=]() { return (Item*)NecrobatHelm::create(); };
	this->deserializers[OldShoe::SaveKey] = [=]() { return (Item*)OldShoe::create(); };
	this->deserializers[OrnateHat::SaveKey] = [=]() { return (Item*)OrnateHat::create(); };
	this->deserializers[PirateHat::SaveKey] = [=]() { return (Item*)PirateHat::create(); };
	this->deserializers[PriestHat::SaveKey] = [=]() { return (Item*)PriestHat::create(); };
	this->deserializers[ReindeerHat::SaveKey] = [=]() { return (Item*)ReindeerHat::create(); };
	this->deserializers[RoyalCrown::SaveKey] = [=]() { return (Item*)RoyalCrown::create(); };
	this->deserializers[SamuraiHat::SaveKey] = [=]() { return (Item*)SamuraiHat::create(); };
	this->deserializers[SantaHat::SaveKey] = [=]() { return (Item*)SantaHat::create(); };
	this->deserializers[ShamanTiara::SaveKey] = [=]() { return (Item*)ShamanTiara::create(); };
	this->deserializers[SnailShell::SaveKey] = [=]() { return (Item*)SnailShell::create(); };
	this->deserializers[SnailShellSpiked::SaveKey] = [=]() { return (Item*)SnailShellSpiked::create(); };
	this->deserializers[SteelHelm::SaveKey] = [=]() { return (Item*)SteelHelm::create(); };
	this->deserializers[TheGoldenEagle::SaveKey] = [=]() { return (Item*)TheGoldenEagle::create(); };
	this->deserializers[TheldarsHelm::SaveKey] = [=]() { return (Item*)TheldarsHelm::create(); };
	this->deserializers[Tiara::SaveKey] = [=]() { return (Item*)Tiara::create(); };
	this->deserializers[TigersBane::SaveKey] = [=]() { return (Item*)TigersBane::create(); };
	this->deserializers[TopHat::SaveKey] = [=]() { return (Item*)TopHat::create(); };
	this->deserializers[ToySoldierHat::SaveKey] = [=]() { return (Item*)ToySoldierHat::create(); };
	this->deserializers[Turban::SaveKey] = [=]() { return (Item*)Turban::create(); };
	this->deserializers[VikingHelmet::SaveKey] = [=]() { return (Item*)VikingHelmet::create(); };
	this->deserializers[WarlocksHeaddress::SaveKey] = [=]() { return (Item*)WarlocksHeaddress::create(); };
	this->deserializers[WitchesHat::SaveKey] = [=]() { return (Item*)WitchesHat::create(); };
	this->deserializers[WizardsHat::SaveKey] = [=]() { return (Item*)WizardsHat::create(); };
	this->deserializers[WizardsHatArcane::SaveKey] = [=]() { return (Item*)WizardsHatArcane::create(); };
	this->deserializers[WizardsHatEarth::SaveKey] = [=]() { return (Item*)WizardsHatEarth::create(); };
	this->deserializers[WizardsHatShadow::SaveKey] = [=]() { return (Item*)WizardsHatShadow::create(); };
	this->deserializers[WizardsHatWater::SaveKey] = [=]() { return (Item*)WizardsHatWater::create(); };
	this->deserializers[WolfHat::SaveKey] = [=]() { return (Item*)WolfHat::create(); };
	this->deserializers[WolfHatWhite::SaveKey] = [=]() { return (Item*)WolfHatWhite::create(); };
	this->deserializers[WoodenPikeHelm::SaveKey] = [=]() { return (Item*)WoodenPikeHelm::create(); };

	// Offhands
	this->deserializers[WoodenShield::SaveKey] = [=]() { return (Item*)WoodenShield::create(); };

	// Necklaces
	this->deserializers[GlowingPendant::SaveKey] = [=]() { return (Item*)GlowingPendant::create(); };

	// Rings
	this->deserializers[SapphireBand::SaveKey] = [=]() { return (Item*)SapphireBand::create(); };

	// Earrings
	this->deserializers[SapphireEarrings::SaveKey] = [=]() { return (Item*)SapphireEarrings::create(); };

	// Keys
	this->deserializers[FountainRoomKey::SaveKey] = [=]() { return (Item*)FountainRoomKey::create(); };
	this->deserializers[MagesGuildPrisonKey::SaveKey] = [=]() { return (Item*)MagesGuildPrisonKey::create(); };
	this->deserializers[MayanGemBlueItem::SaveKey] = [=]() { return (Item*)MayanGemBlueItem::create(); };
	this->deserializers[MayanGemPurpleItem::SaveKey] = [=]() { return (Item*)MayanGemPurpleItem::create(); };
	this->deserializers[MayanGemRedItem::SaveKey] = [=]() { return (Item*)MayanGemRedItem::create(); };
	this->deserializers[MedusaMirror::SaveKey] = [=]() { return (Item*)MedusaMirror::create(); };
	this->deserializers[RamWheel::SaveKey] = [=]() { return (Item*)RamWheel::create(); };
	this->deserializers[TownKey::SaveKey] = [=]() { return (Item*)TownKey::create(); };
}

PlatformerItemDeserializer::~PlatformerItemDeserializer()
{
}

void PlatformerItemDeserializer::initializeListeners()
{
	super::initializeListeners();

	EventListenerCustom* deserializationRequestListener = EventListenerCustom::create(
		InventoryEvents::EventRequestItemDeserialization,
		[=](EventCustom* eventCustom)
		{
			InventoryEvents::RequestItemDeserializationArgs* args = static_cast<InventoryEvents::RequestItemDeserializationArgs*>(eventCustom->getUserData());
			
			if (args != nullptr)
			{
				PlatformerItemDeserializer::deserialize(*args); 
			}
		}
	);

	this->addGlobalEventListener(deserializationRequestListener);
}

void PlatformerItemDeserializer::deserialize(InventoryEvents::RequestItemDeserializationArgs args)
{
	std::string serializationKey = args.itemSerializationKey;

	if (args.onItemDeserializedCallback != nullptr && this->deserializers.find(serializationKey) != this->deserializers.end())
	{
		args.onItemDeserializedCallback(this->deserializers[serializationKey]());
	}
	else
	{
		LogUtils::logError("Unknown item encountered: " + serializationKey);
	}
}

void PlatformerItemDeserializer::registerItem(const std::string& key, const std::function<Item*()>& item)
{
}
