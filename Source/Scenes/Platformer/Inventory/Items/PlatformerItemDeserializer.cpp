#include "PlatformerItemDeserializer.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/GlobalDirector.h"
#include "Engine/Inventory/Item.h"
#include "Engine/Utils/LogUtils.h"

#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

PlatformerItemDeserializer* PlatformerItemDeserializer::Instance = nullptr;

PlatformerItemDeserializer* PlatformerItemDeserializer::getInstance()
{
	if (PlatformerItemDeserializer::Instance == nullptr)
	{
		PlatformerItemDeserializer::Instance = new PlatformerItemDeserializer();

		Instance->autorelease();
	}

	return PlatformerItemDeserializer::Instance;
}

void PlatformerItemDeserializer::RegisterGlobalNode()
{
	// Register this class globally so that it can always listen for events
	GlobalDirector::getInstance()->RegisterGlobalNode(PlatformerItemDeserializer::getInstance());
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
	this->deserializers[Crystal::SaveKey] = [=]() { return (Item*)Crystal::create(); };
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
	this->deserializers[VoidCrystal::SaveKey] = [=]() { return (Item*)VoidCrystal::create(); };
	
	this->deserializers[DarkWood::SaveKey] = [=]() { return (Item*)DarkWood::create(); };
	this->deserializers[LightWood::SaveKey] = [=]() { return (Item*)LightWood::create(); };
	this->deserializers[Wood::SaveKey] = [=]() { return (Item*)Wood::create(); };

	this->deserializers[Acorn::SaveKey] = [=]() { return (Item*)Acorn::create(); };
	this->deserializers[BlackBlood::SaveKey] = [=]() { return (Item*)BlackBlood::create(); };
	this->deserializers[BlackMushroom::SaveKey] = [=]() { return (Item*)BlackMushroom::create(); };
	this->deserializers[Clover::SaveKey] = [=]() { return (Item*)Clover::create(); };
	this->deserializers[DarkSeed::SaveKey] = [=]() { return (Item*)DarkSeed::create(); };
	this->deserializers[DemonRoot::SaveKey] = [=]() { return (Item*)DemonRoot::create(); };
	this->deserializers[Feather::SaveKey] = [=]() { return (Item*)Feather::create(); };
	this->deserializers[FrostBerries::SaveKey] = [=]() { return (Item*)FrostBerries::create(); };
	this->deserializers[GoldWeed::SaveKey] = [=]() { return (Item*)GoldWeed::create(); };
	this->deserializers[Honey::SaveKey] = [=]() { return (Item*)Honey::create(); };
	this->deserializers[Mandrake::SaveKey] = [=]() { return (Item*)Mandrake::create(); };
	this->deserializers[RatTail::SaveKey] = [=]() { return (Item*)RatTail::create(); };
	this->deserializers[SandRoot::SaveKey] = [=]() { return (Item*)SandRoot::create(); };
	this->deserializers[Snowball::SaveKey] = [=]() { return (Item*)Snowball::create(); };
	this->deserializers[VoidFlower::SaveKey] = [=]() { return (Item*)VoidFlower::create(); };

	this->deserializers[Bamboo::SaveKey] = [=]() { return (Item*)Bamboo::create(); };
	this->deserializers[Meteorite::SaveKey] = [=]() { return (Item*)Meteorite::create(); };
	this->deserializers[Pepper::SaveKey] = [=]() { return (Item*)Pepper::create(); };
	this->deserializers[PhoenixFeather::SaveKey] = [=]() { return (Item*)PhoenixFeather::create(); };
	this->deserializers[Stinger::SaveKey] = [=]() { return (Item*)Stinger::create(); };
	this->deserializers[StrongChitin::SaveKey] = [=]() { return (Item*)StrongChitin::create(); };
	this->deserializers[WeakChitin::SaveKey] = [=]() { return (Item*)WeakChitin::create(); };

	this->deserializers[GunpowderT1::SaveKey] = [=]() { return (Item*)GunpowderT1::create(); };
	this->deserializers[GunpowderT2::SaveKey] = [=]() { return (Item*)GunpowderT2::create(); };
	this->deserializers[GunpowderT3::SaveKey] = [=]() { return (Item*)GunpowderT3::create(); };
	this->deserializers[GunpowderT4::SaveKey] = [=]() { return (Item*)GunpowderT4::create(); };
	this->deserializers[GunpowderT5::SaveKey] = [=]() { return (Item*)GunpowderT5::create(); };
	this->deserializers[GunpowderT6::SaveKey] = [=]() { return (Item*)GunpowderT6::create(); };
	this->deserializers[GunpowderT7::SaveKey] = [=]() { return (Item*)GunpowderT7::create(); };

	this->deserializers[HeartOfFire::SaveKey] = [=]() { return (Item*)HeartOfFire::create(); };
	this->deserializers[HeartOfShadow::SaveKey] = [=]() { return (Item*)HeartOfShadow::create(); };

	// Health Consumables
	this->deserializers[HealthPotion::SaveKey] = [=]() { return (Item*)HealthPotion::create(); };
	this->deserializers[GreaterHealthPotion::SaveKey] = [=]() { return (Item*)GreaterHealthPotion::create(); };
	this->deserializers[SuperiorHealthFlask::SaveKey] = [=]() { return (Item*)SuperiorHealthFlask::create(); };
	this->deserializers[IncrementHealthFlask::SaveKey] = [=]() { return (Item*)IncrementHealthFlask::create(); };

	// Mana Consumables
	this->deserializers[ManaPotion::SaveKey] = [=]() { return (Item*)ManaPotion::create(); };
	this->deserializers[GreaterManaPotion::SaveKey] = [=]() { return (Item*)GreaterManaPotion::create(); };
	this->deserializers[SuperiorManaFlask::SaveKey] = [=]() { return (Item*)SuperiorManaFlask::create(); };
	this->deserializers[IncrementManaFlask::SaveKey] = [=]() { return (Item*)IncrementManaFlask::create(); };

	// Special Consumables
	this->deserializers[DualElixir::SaveKey] = [=]() { return (Item*)DualElixir::create(); };

	// Combat Consumables
	this->deserializers[FragGrenade::SaveKey] = [=]() { return (Item*)FragGrenade::create(); };
	this->deserializers[LargeBomb::SaveKey] = [=]() { return (Item*)LargeBomb::create(); };
	this->deserializers[PepperBomb::SaveKey] = [=]() { return (Item*)PepperBomb::create(); };
	this->deserializers[MeteoriteBomb::SaveKey] = [=]() { return (Item*)MeteoriteBomb::create(); };
	this->deserializers[SmallBomb::SaveKey] = [=]() { return (Item*)SmallBomb::create(); };
	this->deserializers[SpikedBomb::SaveKey] = [=]() { return (Item*)SpikedBomb::create(); };
	this->deserializers[SteelBomb::SaveKey] = [=]() { return (Item*)SteelBomb::create(); };

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
	this->deserializers[QuartzWand::SaveKey] = [=]() { return (Item*)QuartzWand::create(); };
	this->deserializers[SapphireWand::SaveKey] = [=]() { return (Item*)SapphireWand::create(); };
	this->deserializers[SerpentWand::SaveKey] = [=]() { return (Item*)SerpentWand::create(); };
	this->deserializers[SilverWand::SaveKey] = [=]() { return (Item*)SilverWand::create(); };
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
	this->deserializers[MithrilHelm::SaveKey] = [=]() { return (Item*)MithrilHelm::create(); };
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
	this->deserializers[AmethystNecklace::SaveKey] = [=]() { return (Item*)AmethystNecklace::create(); };
	this->deserializers[AquaMarineNecklace::SaveKey] = [=]() { return (Item*)AquaMarineNecklace::create(); };
	this->deserializers[EmeraldPendant::SaveKey] = [=]() { return (Item*)EmeraldPendant::create(); };
	this->deserializers[GlowingPendant::SaveKey] = [=]() { return (Item*)GlowingPendant::create(); };
	this->deserializers[HolyNecklace::SaveKey] = [=]() { return (Item*)HolyNecklace::create(); };
	this->deserializers[MarineNecklace::SaveKey] = [=]() { return (Item*)MarineNecklace::create(); };
	this->deserializers[RubyNecklace::SaveKey] = [=]() { return (Item*)RubyNecklace::create(); };
	this->deserializers[SapphireNecklace::SaveKey] = [=]() { return (Item*)SapphireNecklace::create(); };
	this->deserializers[TopazPendant::SaveKey] = [=]() { return (Item*)TopazPendant::create(); };

	// Rings
	this->deserializers[BronzeRing::SaveKey] = [=]() { return (Item*)BronzeRing::create(); };
	this->deserializers[DarkHeartBand::SaveKey] = [=]() { return (Item*)DarkHeartBand::create(); };
	this->deserializers[EmeraldBand::SaveKey] = [=]() { return (Item*)EmeraldBand::create(); };
	this->deserializers[GarnetBand::SaveKey] = [=]() { return (Item*)GarnetBand::create(); };
	this->deserializers[GoldenRing::SaveKey] = [=]() { return (Item*)GoldenRing::create(); };
	this->deserializers[HeartBand::SaveKey] = [=]() { return (Item*)HeartBand::create(); };
	this->deserializers[MarineBand::SaveKey] = [=]() { return (Item*)MarineBand::create(); };
	this->deserializers[SapphireBand::SaveKey] = [=]() { return (Item*)SapphireBand::create(); };
	this->deserializers[ShellBand::SaveKey] = [=]() { return (Item*)ShellBand::create(); };
	this->deserializers[SilverRing::SaveKey] = [=]() { return (Item*)SilverRing::create(); };
	this->deserializers[SkullBand::SaveKey] = [=]() { return (Item*)SkullBand::create(); };
	this->deserializers[SoulBand::SaveKey] = [=]() { return (Item*)SoulBand::create(); };

	// Earrings
	this->deserializers[AquaMarineEarrings::SaveKey] = [=]() { return (Item*)AquaMarineEarrings::create(); };
	this->deserializers[CrystalEarrings::SaveKey] = [=]() { return (Item*)CrystalEarrings::create(); };
	this->deserializers[EmeraldEarrings::SaveKey] = [=]() { return (Item*)EmeraldEarrings::create(); };
	this->deserializers[HeartEarrings::SaveKey] = [=]() { return (Item*)HeartEarrings::create(); };
	this->deserializers[RoseEarrings::SaveKey] = [=]() { return (Item*)RoseEarrings::create(); };
	this->deserializers[SapphireEarrings::SaveKey] = [=]() { return (Item*)SapphireEarrings::create(); };

	// Keys EF
	this->deserializers[MagesGuildPrisonKey::SaveKey] = [=]() { return (Item*)MagesGuildPrisonKey::create(); };
	this->deserializers[RamWheel::SaveKey] = [=]() { return (Item*)RamWheel::create(); };
	this->deserializers[TownKey::SaveKey] = [=]() { return (Item*)TownKey::create(); };

	// Keys UR
	this->deserializers[FountainRoomKey::SaveKey] = [=]() { return (Item*)FountainRoomKey::create(); };
	this->deserializers[MedusaMirror::SaveKey] = [=]() { return (Item*)MedusaMirror::create(); };;

	// Keys DM
	this->deserializers[LetterForThePrincess::SaveKey] = [=]() { return (Item*)LetterForThePrincess::create(); };
	this->deserializers[MinesKey::SaveKey] = [=]() { return (Item*)MinesKey::create(); };
	this->deserializers[TrainTicket::SaveKey] = [=]() { return (Item*)TrainTicket::create(); };

	// Keys CV
	this->deserializers[CryptKey::SaveKey] = [=]() { return (Item*)CryptKey::create(); };

	// Keys LC
	this->deserializers[AncientKey::SaveKey] = [=]() { return (Item*)AncientKey::create(); };
	this->deserializers[RustyKey::SaveKey] = [=]() { return (Item*)RustyKey::create(); };

	// Keys BP
	this->deserializers[IceKey::SaveKey] = [=]() { return (Item*)IceKey::create(); };
	this->deserializers[FrostKey::SaveKey] = [=]() { return (Item*)FrostKey::create(); };
	this->deserializers[FrozenKey::SaveKey] = [=]() { return (Item*)FrozenKey::create(); };

	// Keys FF
	this->deserializers[DemonKey::SaveKey] = [=]() { return (Item*)DemonKey::create(); };
	this->deserializers[DemonHeart::SaveKey] = [=]() { return (Item*)DemonHeart::create(); };
	this->deserializers[HeliumBomb::SaveKey] = [=]() { return (Item*)HeliumBomb::create(); };
	this->deserializers[HellKey::SaveKey] = [=]() { return (Item*)HellKey::create(); };
	this->deserializers[UnstableConcoction::SaveKey] = [=]() { return (Item*)UnstableConcoction::create(); };
	this->deserializers[UnstableElement::SaveKey] = [=]() { return (Item*)UnstableElement::create(); };

	// Keys VS
	this->deserializers[MayanGemBlueItem::SaveKey] = [=]() { return (Item*)MayanGemBlueItem::create(); };
	this->deserializers[MayanGemPurpleItem::SaveKey] = [=]() { return (Item*)MayanGemPurpleItem::create(); };
	this->deserializers[MayanGemRedItem::SaveKey] = [=]() { return (Item*)MayanGemRedItem::create(); };

	// Maps
	this->deserializers[TempleMap::SaveKey] = [=]() { return (Item*)TempleMap::create(); };

	// Health Potion Recipes
	this->deserializers[HealthPotionRecipe::SaveKey] = [=]() { return (Item*)HealthPotionRecipe::create(); };
	this->deserializers[GreaterHealthPotionRecipe::SaveKey] = [=]() { return (Item*)GreaterHealthPotionRecipe::create(); };
	this->deserializers[SuperiorHealthFlaskRecipe::SaveKey] = [=]() { return (Item*)SuperiorHealthFlaskRecipe::create(); };
	this->deserializers[IncrementHealthFlaskRecipe::SaveKey] = [=]() { return (Item*)IncrementHealthFlaskRecipe::create(); };

	// Mana Potion Recipes
	this->deserializers[ManaPotionRecipe::SaveKey] = [=]() { return (Item*)ManaPotionRecipe::create(); };
	this->deserializers[GreaterManaPotionRecipe::SaveKey] = [=]() { return (Item*)GreaterManaPotionRecipe::create(); };
	this->deserializers[SuperiorManaFlaskRecipe::SaveKey] = [=]() { return (Item*)SuperiorManaFlaskRecipe::create(); };
	this->deserializers[IncrementManaFlaskRecipe::SaveKey] = [=]() { return (Item*)IncrementManaFlaskRecipe::create(); };

	// Special Potion Recipes
	this->deserializers[DualElixirRecipe::SaveKey] = [=]() { return (Item*)DualElixirRecipe::create(); };

	// Combat Consumable Recipes
	this->deserializers[FragGrenadeRecipe::SaveKey] = [=]() { return (Item*)FragGrenadeRecipe::create(); };
	this->deserializers[LargeBombRecipe::SaveKey] = [=]() { return (Item*)LargeBombRecipe::create(); };
	this->deserializers[MeteoriteBombRecipe::SaveKey] = [=]() { return (Item*)MeteoriteBombRecipe::create(); };
	this->deserializers[PepperBombRecipe::SaveKey] = [=]() { return (Item*)PepperBombRecipe::create(); };
	this->deserializers[SmallBombRecipe::SaveKey] = [=]() { return (Item*)SmallBombRecipe::create(); };
	this->deserializers[SpikedBombRecipe::SaveKey] = [=]() { return (Item*)SpikedBombRecipe::create(); };
	this->deserializers[SteelBombRecipe::SaveKey] = [=]() { return (Item*)SteelBombRecipe::create(); };

	// Transmute Recipes
	this->deserializers[TransmuteCopperToIron::SaveKey] = [=]() { return (Item*)TransmuteCopperToIron::create(); };
	this->deserializers[TransmuteCopperToQuartzRecipe::SaveKey] = [=]() { return (Item*)TransmuteCopperToQuartzRecipe::create(); };
	this->deserializers[TransmuteQuartzToEmerald::SaveKey] = [=]() { return (Item*)TransmuteQuartzToEmerald::create(); };
	this->deserializers[TransmuteWoodToCoalRecipe::SaveKey] = [=]() { return (Item*)TransmuteWoodToCoalRecipe::create(); };
	
	// Weapon Recipes
	this->deserializers[BoneAxePlans::SaveKey] = [=]() { return (Item*)BoneAxePlans::create(); };
	this->deserializers[CopperAxePlans::SaveKey] = [=]() { return (Item*)CopperAxePlans::create(); };
	this->deserializers[CrystalAxePlans::SaveKey] = [=]() { return (Item*)CrystalAxePlans::create(); };
	this->deserializers[DemonicAxePlans::SaveKey] = [=]() { return (Item*)DemonicAxePlans::create(); };
	this->deserializers[FrostAxePlans::SaveKey] = [=]() { return (Item*)FrostAxePlans::create(); };
	this->deserializers[GoldenAxePlans::SaveKey] = [=]() { return (Item*)GoldenAxePlans::create(); };
	this->deserializers[MithrilAxePlans::SaveKey] = [=]() { return (Item*)MithrilAxePlans::create(); };
	this->deserializers[ScythePlans::SaveKey] = [=]() { return (Item*)ScythePlans::create(); };
	this->deserializers[SteelAxePlans::SaveKey] = [=]() { return (Item*)SteelAxePlans::create(); };
	this->deserializers[VoidAxePlans::SaveKey] = [=]() { return (Item*)VoidAxePlans::create(); };
	this->deserializers[WoodenAxePlans::SaveKey] = [=]() { return (Item*)WoodenAxePlans::create(); };
	this->deserializers[BoneBowPlans::SaveKey] = [=]() { return (Item*)BoneBowPlans::create(); };
	this->deserializers[CrystalBowPlans::SaveKey] = [=]() { return (Item*)CrystalBowPlans::create(); };
	this->deserializers[DemonicBowPlans::SaveKey] = [=]() { return (Item*)DemonicBowPlans::create(); };
	this->deserializers[GoldenBowPlans::SaveKey] = [=]() { return (Item*)GoldenBowPlans::create(); };
	this->deserializers[HuntersBowPlans::SaveKey] = [=]() { return (Item*)HuntersBowPlans::create(); };
	this->deserializers[IvyBowPlans::SaveKey] = [=]() { return (Item*)IvyBowPlans::create(); };
	this->deserializers[SteelBowPlans::SaveKey] = [=]() { return (Item*)SteelBowPlans::create(); };
	this->deserializers[VoidBowPlans::SaveKey] = [=]() { return (Item*)VoidBowPlans::create(); };
	this->deserializers[WoodenBowPlans::SaveKey] = [=]() { return (Item*)WoodenBowPlans::create(); };
	this->deserializers[BludgeonPlans::SaveKey] = [=]() { return (Item*)BludgeonPlans::create(); };
	this->deserializers[BoneHammerPlans::SaveKey] = [=]() { return (Item*)BoneHammerPlans::create(); };
	this->deserializers[CopperMalletPlans::SaveKey] = [=]() { return (Item*)CopperMalletPlans::create(); };
	this->deserializers[CrystalMacePlans::SaveKey] = [=]() { return (Item*)CrystalMacePlans::create(); };
	this->deserializers[DemonicMacePlans::SaveKey] = [=]() { return (Item*)DemonicMacePlans::create(); };
	this->deserializers[GoldenMacePlans::SaveKey] = [=]() { return (Item*)GoldenMacePlans::create(); };
	this->deserializers[MithrilMacePlans::SaveKey] = [=]() { return (Item*)MithrilMacePlans::create(); };
	this->deserializers[SteelMacePlans::SaveKey] = [=]() { return (Item*)SteelMacePlans::create(); };
	this->deserializers[VoidMacePlans::SaveKey] = [=]() { return (Item*)VoidMacePlans::create(); };
	this->deserializers[WitchingMacePlans::SaveKey] = [=]() { return (Item*)WitchingMacePlans::create(); };
	this->deserializers[WoodenClubPlans::SaveKey] = [=]() { return (Item*)WoodenClubPlans::create(); };
	this->deserializers[AshenBladePlans::SaveKey] = [=]() { return (Item*)AshenBladePlans::create(); };
	this->deserializers[BoneSwordPlans::SaveKey] = [=]() { return (Item*)BoneSwordPlans::create(); };
	this->deserializers[CandySwordPlans::SaveKey] = [=]() { return (Item*)CandySwordPlans::create(); };
	this->deserializers[CopperSwordPlans::SaveKey] = [=]() { return (Item*)CopperSwordPlans::create(); };
	this->deserializers[CrystalSwordPlans::SaveKey] = [=]() { return (Item*)CrystalSwordPlans::create(); };
	this->deserializers[DemonicSwordPlans::SaveKey] = [=]() { return (Item*)DemonicSwordPlans::create(); };
	this->deserializers[DreadmournPlans::SaveKey] = [=]() { return (Item*)DreadmournPlans::create(); };
	this->deserializers[FireSwordPlans::SaveKey] = [=]() { return (Item*)FireSwordPlans::create(); };
	this->deserializers[FrostbanePlans::SaveKey] = [=]() { return (Item*)FrostbanePlans::create(); };
	this->deserializers[GoldenSwordPlans::SaveKey] = [=]() { return (Item*)GoldenSwordPlans::create(); };
	this->deserializers[MithrilSwordPlans::SaveKey] = [=]() { return (Item*)MithrilSwordPlans::create(); };
	this->deserializers[SteelSwordPlans::SaveKey] = [=]() { return (Item*)SteelSwordPlans::create(); };
	this->deserializers[TheButcherPlans::SaveKey] = [=]() { return (Item*)TheButcherPlans::create(); };
	this->deserializers[TimmyPlans::SaveKey] = [=]() { return (Item*)TimmyPlans::create(); };
	this->deserializers[VoidSwordPlans::SaveKey] = [=]() { return (Item*)VoidSwordPlans::create(); };
	this->deserializers[WoodenSwordPlans::SaveKey] = [=]() { return (Item*)WoodenSwordPlans::create(); };
	this->deserializers[BoneWandPlans::SaveKey] = [=]() { return (Item*)BoneWandPlans::create(); };
	this->deserializers[ChieftainsWandPlans::SaveKey] = [=]() { return (Item*)ChieftainsWandPlans::create(); };
	this->deserializers[CrystalWandPlans::SaveKey] = [=]() { return (Item*)CrystalWandPlans::create(); };
	this->deserializers[DemonicWandPlans::SaveKey] = [=]() { return (Item*)DemonicWandPlans::create(); };
	this->deserializers[EmeraldWandPlans::SaveKey] = [=]() { return (Item*)EmeraldWandPlans::create(); };
	this->deserializers[QuartzWandPlans::SaveKey] = [=]() { return (Item*)QuartzWandPlans::create(); };
	this->deserializers[SapphireWandPlans::SaveKey] = [=]() { return (Item*)SapphireWandPlans::create(); };
	this->deserializers[SerpentWandPlans::SaveKey] = [=]() { return (Item*)SerpentWandPlans::create(); };
	this->deserializers[SilverWandPlans::SaveKey] = [=]() { return (Item*)SilverWandPlans::create(); };
	this->deserializers[TaserRodPlans::SaveKey] = [=]() { return (Item*)TaserRodPlans::create(); };
	this->deserializers[VoidWandPlans::SaveKey] = [=]() { return (Item*)VoidWandPlans::create(); };
	this->deserializers[WoodenWandPlans::SaveKey] = [=]() { return (Item*)WoodenWandPlans::create(); };
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
			InventoryEvents::RequestItemDeserializationArgs* args = static_cast<InventoryEvents::RequestItemDeserializationArgs*>(eventCustom->getData());
			
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
