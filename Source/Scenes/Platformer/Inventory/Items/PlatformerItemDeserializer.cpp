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
	this->deserializers[Binary0::SaveKeyBinary0] = [=]() { return (Item*)Binary0::create(); };
	this->deserializers[Binary1::SaveKeyBinary1] = [=]() { return (Item*)Binary1::create(); };
	this->deserializers[Binary2::SaveKeyBinary2] = [=]() { return (Item*)Binary2::create(); };
	this->deserializers[Binary3::SaveKeyBinary3] = [=]() { return (Item*)Binary3::create(); };
	this->deserializers[Binary4::SaveKeyBinary4] = [=]() { return (Item*)Binary4::create(); };
	this->deserializers[Binary5::SaveKeyBinary5] = [=]() { return (Item*)Binary5::create(); };
	this->deserializers[Binary6::SaveKeyBinary6] = [=]() { return (Item*)Binary6::create(); };
	this->deserializers[Binary7::SaveKeyBinary7] = [=]() { return (Item*)Binary7::create(); };
	this->deserializers[Binary8::SaveKeyBinary8] = [=]() { return (Item*)Binary8::create(); };
	this->deserializers[Binary9::SaveKeyBinary9] = [=]() { return (Item*)Binary9::create(); };
	this->deserializers[Binary10::SaveKeyBinary10] = [=]() { return (Item*)Binary10::create(); };
	this->deserializers[Binary11::SaveKeyBinary11] = [=]() { return (Item*)Binary11::create(); };
	this->deserializers[Binary12::SaveKeyBinary12] = [=]() { return (Item*)Binary12::create(); };
	this->deserializers[Binary13::SaveKeyBinary13] = [=]() { return (Item*)Binary13::create(); };
	this->deserializers[Binary14::SaveKeyBinary14] = [=]() { return (Item*)Binary15::create(); };
	this->deserializers[Binary15::SaveKeyBinary15] = [=]() { return (Item*)Binary15::create(); };

	this->deserializers[Decimal0::SaveKeyDecimal0] = [=]() { return (Item*)Decimal0::create(); };
	this->deserializers[Decimal1::SaveKeyDecimal1] = [=]() { return (Item*)Decimal1::create(); };
	this->deserializers[Decimal2::SaveKeyDecimal2] = [=]() { return (Item*)Decimal2::create(); };
	this->deserializers[Decimal3::SaveKeyDecimal3] = [=]() { return (Item*)Decimal3::create(); };
	this->deserializers[Decimal4::SaveKeyDecimal4] = [=]() { return (Item*)Decimal4::create(); };
	this->deserializers[Decimal5::SaveKeyDecimal5] = [=]() { return (Item*)Decimal5::create(); };
	this->deserializers[Decimal6::SaveKeyDecimal6] = [=]() { return (Item*)Decimal6::create(); };
	this->deserializers[Decimal7::SaveKeyDecimal7] = [=]() { return (Item*)Decimal7::create(); };
	this->deserializers[Decimal8::SaveKeyDecimal8] = [=]() { return (Item*)Decimal8::create(); };
	this->deserializers[Decimal9::SaveKeyDecimal9] = [=]() { return (Item*)Decimal9::create(); };
	this->deserializers[Decimal10::SaveKeyDecimal10] = [=]() { return (Item*)Decimal10::create(); };
	this->deserializers[Decimal11::SaveKeyDecimal11] = [=]() { return (Item*)Decimal11::create(); };
	this->deserializers[Decimal12::SaveKeyDecimal12] = [=]() { return (Item*)Decimal12::create(); };
	this->deserializers[Decimal13::SaveKeyDecimal13] = [=]() { return (Item*)Decimal13::create(); };
	this->deserializers[Decimal14::SaveKeyDecimal14] = [=]() { return (Item*)Decimal15::create(); };
	this->deserializers[Decimal15::SaveKeyDecimal15] = [=]() { return (Item*)Decimal15::create(); };
	
	this->deserializers[Hex0::SaveKeyHex0] = [=]() { return (Item*)Hex0::create(); };
	this->deserializers[Hex1::SaveKeyHex1] = [=]() { return (Item*)Hex1::create(); };
	this->deserializers[Hex2::SaveKeyHex2] = [=]() { return (Item*)Hex2::create(); };
	this->deserializers[Hex3::SaveKeyHex3] = [=]() { return (Item*)Hex3::create(); };
	this->deserializers[Hex4::SaveKeyHex4] = [=]() { return (Item*)Hex4::create(); };
	this->deserializers[Hex5::SaveKeyHex5] = [=]() { return (Item*)Hex5::create(); };
	this->deserializers[Hex6::SaveKeyHex6] = [=]() { return (Item*)Hex6::create(); };
	this->deserializers[Hex7::SaveKeyHex7] = [=]() { return (Item*)Hex7::create(); };
	this->deserializers[Hex8::SaveKeyHex8] = [=]() { return (Item*)Hex8::create(); };
	this->deserializers[Hex9::SaveKeyHex9] = [=]() { return (Item*)Hex9::create(); };
	this->deserializers[Hex10::SaveKeyHex10] = [=]() { return (Item*)Hex10::create(); };
	this->deserializers[Hex11::SaveKeyHex11] = [=]() { return (Item*)Hex11::create(); };
	this->deserializers[Hex12::SaveKeyHex12] = [=]() { return (Item*)Hex12::create(); };
	this->deserializers[Hex13::SaveKeyHex13] = [=]() { return (Item*)Hex13::create(); };
	this->deserializers[Hex14::SaveKeyHex14] = [=]() { return (Item*)Hex15::create(); };
	this->deserializers[Hex15::SaveKeyHex15] = [=]() { return (Item*)Hex15::create(); };

	this->deserializers[SpecialAbsorb::SaveKeySpecialAbsorb] = [=]() { return (Item*)SpecialAbsorb::create(); };
	this->deserializers[SpecialAdd::SaveKeySpecialAdd] = [=]() { return (Item*)SpecialAdd::create(); };
	this->deserializers[SpecialAnd::SaveKeySpecialAnd] = [=]() { return (Item*)SpecialAnd::create(); };
	this->deserializers[SpecialFlip1::SaveKeySpecialFlip1] = [=]() { return (Item*)SpecialFlip1::create(); };
	this->deserializers[SpecialFlip2::SaveKeySpecialFlip2] = [=]() { return (Item*)SpecialFlip2::create(); };
	this->deserializers[SpecialFlip3::SaveKeySpecialFlip3] = [=]() { return (Item*)SpecialFlip3::create(); };
	this->deserializers[SpecialFlip4::SaveKeySpecialFlip4] = [=]() { return (Item*)SpecialFlip4::create(); };

	this->deserializers[SpecialGreed::SaveKeySpecialGreed] = [=]() { return (Item*)SpecialGreed::create(); };
	this->deserializers[SpecialInv::SaveKeySpecialInv] = [=]() { return (Item*)SpecialInv::create(); };
	this->deserializers[SpecialMov::SaveKeySpecialMov] = [=]() { return (Item*)SpecialMov::create(); };
	this->deserializers[SpecialOr::SaveKeySpecialOr] = [=]() { return (Item*)SpecialOr::create(); };
	this->deserializers[SpecialPeek::SaveKeySpecialPeek] = [=]() { return (Item*)SpecialPeek::create(); };
	this->deserializers[SpecialShl::SaveKeySpecialShl] = [=]() { return (Item*)SpecialShl::create(); };
	this->deserializers[SpecialShlCircular::SaveKeySpecialShlCircular] = [=]() { return (Item*)SpecialShlCircular::create(); };
	this->deserializers[SpecialShr::SaveKeySpecialShr] = [=]() { return (Item*)SpecialShr::create(); };
	this->deserializers[SpecialShrCircular::SaveKeySpecialShrCircular] = [=]() { return (Item*)SpecialShrCircular::create(); };
	this->deserializers[SpecialSteal::SaveKeySpecialSteal] = [=]() { return (Item*)SpecialSteal::create(); };
	this->deserializers[SpecialSub::SaveKeySpecialSub] = [=]() { return (Item*)SpecialSub::create(); };
	this->deserializers[SpecialXor::SaveKeySpecialXor] = [=]() { return (Item*)SpecialXor::create(); };

	// Crafting
	this->deserializers[Adamantite::SaveKeyAdamantite] = [=]() { return (Item*)Adamantite::create(); };
	this->deserializers[Coal::SaveKeyCoal] = [=]() { return (Item*)Coal::create(); };
	this->deserializers[Copper::SaveKeyCopper] = [=]() { return (Item*)Copper::create(); };
	this->deserializers[Diamond::SaveKeyDiamond] = [=]() { return (Item*)Diamond::create(); };
	this->deserializers[Emerald::SaveKeyEmerald] = [=]() { return (Item*)Emerald::create(); };
	this->deserializers[Gold::SaveKeyGold] = [=]() { return (Item*)Gold::create(); };
	this->deserializers[Iron::SaveKeyIron] = [=]() { return (Item*)Iron::create(); };
	this->deserializers[Jade::SaveKeyJade] = [=]() { return (Item*)Jade::create(); };
	this->deserializers[Obsidian::SaveKeyObsidian] = [=]() { return (Item*)Obsidian::create(); };
	this->deserializers[Quartz::SaveKeyQuartz] = [=]() { return (Item*)Quartz::create(); };
	this->deserializers[Ruby::SaveKeyRuby] = [=]() { return (Item*)Ruby::create(); };
	this->deserializers[Rune::SaveKeyRune] = [=]() { return (Item*)Rune::create(); };
	this->deserializers[Sulfur::SaveKeySulfur] = [=]() { return (Item*)Sulfur::create(); };
	this->deserializers[Tin::SaveKeyTin] = [=]() { return (Item*)Tin::create(); };
	
	this->deserializers[DarkWood::SaveKeyDarkWood] = [=]() { return (Item*)DarkWood::create(); };
	this->deserializers[LightWood::SaveKeyLightWood] = [=]() { return (Item*)LightWood::create(); };
	this->deserializers[Wood::SaveKeyWood] = [=]() { return (Item*)Wood::create(); };

	// Consumables
	this->deserializers[HealthPotion::SaveKeyHealthPotion] = [=]() { return (Item*)HealthPotion::create(); };
	this->deserializers[IncrementHealthFlask::SaveKeyIncrementHealthFlask] = [=]() { return (Item*)IncrementHealthFlask::create(); };
	this->deserializers[ManaPotion::SaveKeyManaPotion] = [=]() { return (Item*)ManaPotion::create(); };

	// Axes
	this->deserializers[BattleAxe::SaveKeyBattleAxe] = [=]() { return (Item*)BattleAxe::create(); };
	this->deserializers[BlueAxe::SaveKeyBlueAxe] = [=]() { return (Item*)BlueAxe::create(); };
	this->deserializers[FireAxe::SaveKeyFireAxe] = [=]() { return (Item*)FireAxe::create(); };
	this->deserializers[HandAxe::SaveKeyHandAxe] = [=]() { return (Item*)HandAxe::create(); };
	this->deserializers[HeadSplitter::SaveKeyHeadSplitter] = [=]() { return (Item*)HeadSplitter::create(); };
	this->deserializers[HedgeTrimmer::SaveKeyHedgeTrimmer] = [=]() { return (Item*)HedgeTrimmer::create(); };
	this->deserializers[IronAxe::SaveKeyIronAxe] = [=]() { return (Item*)IronAxe::create(); };
	this->deserializers[MithrilAxe::SaveKeyMithrilAxe] = [=]() { return (Item*)MithrilAxe::create(); };
	this->deserializers[Rend::SaveKeyRend] = [=]() { return (Item*)Rend::create(); };
	this->deserializers[Scythe::SaveKeyScythe] = [=]() { return (Item*)Scythe::create(); };
	this->deserializers[StarAxe::SaveKeyStarAxe] = [=]() { return (Item*)StarAxe::create(); };
	this->deserializers[SteelAxe::SaveKeySteelAxe] = [=]() { return (Item*)SteelAxe::create(); };
	this->deserializers[WoodCutter::SaveKeyWoodCutter] = [=]() { return (Item*)WoodCutter::create(); };

	this->deserializers[BattleAxePlans::SaveKeyBattleAxePlans] = [=]() { return (Item*)BattleAxePlans::create(); };

	// Bows
	this->deserializers[ArchersBow::SaveKeyArchersBow] = [=]() { return (Item*)ArchersBow::create(); };
	this->deserializers[BoneBow::SaveKeyBoneBow] = [=]() { return (Item*)BoneBow::create(); };
	this->deserializers[CompositeBow::SaveKeyCompositeBow] = [=]() { return (Item*)CompositeBow::create(); };
	this->deserializers[FrostBow::SaveKeyFrostBow] = [=]() { return (Item*)FrostBow::create(); };
	this->deserializers[HuntersBow::SaveKeyHuntersBow] = [=]() { return (Item*)HuntersBow::create(); };
	this->deserializers[IvoryBow::SaveKeyIvoryBow] = [=]() { return (Item*)IvoryBow::create(); };
	this->deserializers[OlympusBow::SaveKeyOlympusBow] = [=]() { return (Item*)OlympusBow::create(); };
	this->deserializers[WarBow::SaveKeyWarBow] = [=]() { return (Item*)WarBow::create(); };

	// Maces
	this->deserializers[BattleHammer::SaveKeyBattleHammer] = [=]() { return (Item*)BattleHammer::create(); };
	this->deserializers[BoneHammer::SaveKeyBoneHammer] = [=]() { return (Item*)BoneHammer::create(); };
	this->deserializers[CrystalMace::SaveKeyCrystalMace] = [=]() { return (Item*)CrystalMace::create(); };
	this->deserializers[Flail::SaveKeyFlail] = [=]() { return (Item*)Flail::create(); };
	this->deserializers[IronMace::SaveKeyIronMace] = [=]() { return (Item*)IronMace::create(); };
	this->deserializers[Judgement::SaveKeyJudgement] = [=]() { return (Item*)Judgement::create(); };
	this->deserializers[SkullCrusher::SaveKeySkullCrusher] = [=]() { return (Item*)SkullCrusher::create(); };
	this->deserializers[SpikedClub::SaveKeySpikedClub] = [=]() { return (Item*)SpikedClub::create(); };
	this->deserializers[WoodenMallet::SaveKeyWoodenMallet] = [=]() { return (Item*)WoodenMallet::create(); };

	// Spears
	this->deserializers[Impaler::SaveKeyImpaler] = [=]() { return (Item*)Impaler::create(); };

	// Swords
	this->deserializers[AshenBlade::SaveKeyAshenBlade] = [=]() { return (Item*)AshenBlade::create(); };
	this->deserializers[BattleSword::SaveKeyBattleSword] = [=]() { return (Item*)BattleSword::create(); };
	this->deserializers[BlueSword::SaveKeyBlueSword] = [=]() { return (Item*)BlueSword::create(); };
	this->deserializers[CandySword::SaveKeyCandySword] = [=]() { return (Item*)CandySword::create(); };
	this->deserializers[Cleaver::SaveKeyCleaver] = [=]() { return (Item*)Cleaver::create(); };
	this->deserializers[CrystalSword::SaveKeyCrystalSword] = [=]() { return (Item*)CrystalSword::create(); };
	this->deserializers[FangBlade::SaveKeyFangBlade] = [=]() { return (Item*)FangBlade::create(); };
	this->deserializers[GladiatorSword::SaveKeyGladiatorSword] = [=]() { return (Item*)GladiatorSword::create(); };
	this->deserializers[Gladius::SaveKeyGladius] = [=]() { return (Item*)Gladius::create(); };
	this->deserializers[Harbinger::SaveKeyHarbinger] = [=]() { return (Item*)Harbinger::create(); };
	this->deserializers[IronSword::SaveKeyIronSword] = [=]() { return (Item*)IronSword::create(); };
	this->deserializers[Katana::SaveKeyKatana] = [=]() { return (Item*)Katana::create(); };
	this->deserializers[MoonBlade::SaveKeyMoonBlade] = [=]() { return (Item*)MoonBlade::create(); };
	this->deserializers[Rapier::SaveKeyRapier] = [=]() { return (Item*)Rapier::create(); };
	this->deserializers[SteelSword::SaveKeySteelSword] = [=]() { return (Item*)SteelSword::create(); };
	this->deserializers[VikingSword::SaveKeyVikingSword] = [=]() { return (Item*)VikingSword::create(); };
	this->deserializers[WarCutlas::SaveKeyWarCutlas] = [=]() { return (Item*)WarCutlas::create(); };

	// Wands
	this->deserializers[ArcaneWand::SaveKeyArcaneWand] = [=]() { return (Item*)ArcaneWand::create(); };
	this->deserializers[ChieftainsWand::SaveKeyChieftainsWand] = [=]() { return (Item*)ChieftainsWand::create(); };
	this->deserializers[CrystalWand::SaveKeyCrystalWand] = [=]() { return (Item*)CrystalWand::create(); };
	this->deserializers[CursedWand::SaveKeyCursedWand] = [=]() { return (Item*)CursedWand::create(); };
	this->deserializers[EnchantedWand::SaveKeyEnchantedWand] = [=]() { return (Item*)EnchantedWand::create(); };
	this->deserializers[HolyWand::SaveKeyHolyWand] = [=]() { return (Item*)HolyWand::create(); };
	this->deserializers[ManaWand::SaveKeyManaWand] = [=]() { return (Item*)ManaWand::create(); };
	this->deserializers[NecroWand::SaveKeyNecroWand] = [=]() { return (Item*)NecroWand::create(); };
	this->deserializers[SerpentWand::SaveKeySerpentWand] = [=]() { return (Item*)SerpentWand::create(); };
	this->deserializers[TaserRod::SaveKeyTaserRod] = [=]() { return (Item*)TaserRod::create(); };
	this->deserializers[WitchDoctorsWand::SaveKeyWitchDoctorsWand] = [=]() { return (Item*)WitchDoctorsWand::create(); };
	this->deserializers[WoodenWand::SaveKeyWoodenWand] = [=]() { return (Item*)WoodenWand::create(); };

	// Hats
	this->deserializers[AcolytesCap::SaveKeyAcolytesCap] = [=]() { return (Item*)AcolytesCap::create(); };
	this->deserializers[ArchersHat::SaveKeyArchersHat] = [=]() { return (Item*)ArchersHat::create(); };
	this->deserializers[BarbedHelm::SaveKeyBarbedHelm] = [=]() { return (Item*)BarbedHelm::create(); };
	this->deserializers[BrocksHelm::SaveKeyBrocksHelm] = [=]() { return (Item*)BrocksHelm::create(); };
	this->deserializers[BucketHelm::SaveKeyBucketHelm] = [=]() { return (Item*)BucketHelm::create(); };
	this->deserializers[ConchHelm::SaveKeyConchHelm] = [=]() { return (Item*)ConchHelm::create(); };
	this->deserializers[CopperHelm::SaveKeyCopperHelm] = [=]() { return (Item*)CopperHelm::create(); };
	this->deserializers[CowboyHat::SaveKeyCowboyHat] = [=]() { return (Item*)CowboyHat::create(); };
	this->deserializers[DemonShell::SaveKeyDemonShell] = [=]() { return (Item*)DemonShell::create(); };
	this->deserializers[DepressingWig::SaveKeyDepressingWig] = [=]() { return (Item*)DepressingWig::create(); };
	this->deserializers[DraksHelm::SaveKeyDraksHelm] = [=]() { return (Item*)DraksHelm::create(); };
	this->deserializers[GardenersHat::SaveKeyGardenersHat] = [=]() { return (Item*)GardenersHat::create(); };
	this->deserializers[GoldenDungHelm::SaveKeyGoldenDungHelm] = [=]() { return (Item*)GoldenDungHelm::create(); };
	this->deserializers[GrandpasLuckyHat::SaveKeyGrandpasLuckyHat] = [=]() { return (Item*)GrandpasLuckyHat::create(); };
	this->deserializers[GuardsHelmet::SaveKeyGuardsHelmet] = [=]() { return (Item*)GuardsHelmet::create(); };
	this->deserializers[GunnersHat::SaveKeyGunnersHat] = [=]() { return (Item*)GunnersHat::create(); };
	this->deserializers[JesterHat::SaveKeyJesterHat] = [=]() { return (Item*)JesterHat::create(); };
	this->deserializers[JoustingHelmet::SaveKeyJoustingHelmet] = [=]() { return (Item*)JoustingHelmet::create(); };
	this->deserializers[LeatherCap::SaveKeyLeatherCap] = [=]() { return (Item*)LeatherCap::create(); };
	this->deserializers[MagesHatBlue::SaveKeyMagesHatBlue] = [=]() { return (Item*)MagesHatBlue::create(); };
	this->deserializers[MagesHatRed::SaveKeyMagesHatRed] = [=]() { return (Item*)MagesHatRed::create(); };
	this->deserializers[Monocle::SaveKeyMonocle] = [=]() { return (Item*)Monocle::create(); };
	this->deserializers[NecrobatHelm::SaveKeyNecrobatHelm] = [=]() { return (Item*)NecrobatHelm::create(); };
	this->deserializers[OldShoe::SaveKeyOldShoe] = [=]() { return (Item*)OldShoe::create(); };
	this->deserializers[OrnateHat::SaveKeyOrnateHat] = [=]() { return (Item*)OrnateHat::create(); };
	this->deserializers[PirateHat::SaveKeyPirateHat] = [=]() { return (Item*)PirateHat::create(); };
	this->deserializers[PriestHat::SaveKeyPriestHat] = [=]() { return (Item*)PriestHat::create(); };
	this->deserializers[ReindeerHat::SaveKeyReindeerHat] = [=]() { return (Item*)ReindeerHat::create(); };
	this->deserializers[RoyalCrown::SaveKeyRoyalCrown] = [=]() { return (Item*)RoyalCrown::create(); };
	this->deserializers[SamuraiHat::SaveKeySamuraiHat] = [=]() { return (Item*)SamuraiHat::create(); };
	this->deserializers[SantaHat::SaveKeySantaHat] = [=]() { return (Item*)SantaHat::create(); };
	this->deserializers[ShamanTiara::SaveKeyShamanTiara] = [=]() { return (Item*)ShamanTiara::create(); };
	this->deserializers[SnailShell::SaveKeySnailShell] = [=]() { return (Item*)SnailShell::create(); };
	this->deserializers[SnailShellSpiked::SaveKeySnailShellSpiked] = [=]() { return (Item*)SnailShellSpiked::create(); };
	this->deserializers[SteelHelm::SaveKeySteelHelm] = [=]() { return (Item*)SteelHelm::create(); };
	this->deserializers[TheGoldenEagle::SaveKeyTheGoldenEagle] = [=]() { return (Item*)TheGoldenEagle::create(); };
	this->deserializers[TheldarsHelm::SaveKeyTheldarsHelm] = [=]() { return (Item*)TheldarsHelm::create(); };
	this->deserializers[Tiara::SaveKeyTiara] = [=]() { return (Item*)Tiara::create(); };
	this->deserializers[TigersBane::SaveKeyTigersBane] = [=]() { return (Item*)TigersBane::create(); };
	this->deserializers[TopHat::SaveKeyTopHat] = [=]() { return (Item*)TopHat::create(); };
	this->deserializers[ToySoldierHat::SaveKeyToySoldierHat] = [=]() { return (Item*)ToySoldierHat::create(); };
	this->deserializers[Turban::SaveKeyTurban] = [=]() { return (Item*)Turban::create(); };
	this->deserializers[VikingHelmet::SaveKeyVikingHelmet] = [=]() { return (Item*)VikingHelmet::create(); };
	this->deserializers[WarlocksHeaddress::SaveKeyWarlocksHeaddress] = [=]() { return (Item*)WarlocksHeaddress::create(); };
	this->deserializers[WitchesHat::SaveKeyWitchesHat] = [=]() { return (Item*)WitchesHat::create(); };
	this->deserializers[WizardsHat::SaveKeyWizardsHat] = [=]() { return (Item*)WizardsHat::create(); };
	this->deserializers[WizardsHatArcane::SaveKeyWizardsHatArcane] = [=]() { return (Item*)WizardsHatArcane::create(); };
	this->deserializers[WizardsHatEarth::SaveKeyWizardsHatEarth] = [=]() { return (Item*)WizardsHatEarth::create(); };
	this->deserializers[WizardsHatShadow::SaveKeyWizardsHatShadow] = [=]() { return (Item*)WizardsHatShadow::create(); };
	this->deserializers[WizardsHatWater::SaveKeyWizardsHatWater] = [=]() { return (Item*)WizardsHatWater::create(); };
	this->deserializers[WolfHat::SaveKeyWolfHat] = [=]() { return (Item*)WolfHat::create(); };
	this->deserializers[WolfHatWhite::SaveKeyWolfHatWhite] = [=]() { return (Item*)WolfHatWhite::create(); };
	this->deserializers[WoodenPikeHelm::SaveKeyWoodenPikeHelm] = [=]() { return (Item*)WoodenPikeHelm::create(); };

	// Offhands
	this->deserializers[WoodenShield::SaveKeyWoodenShield] = [=]() { return (Item*)WoodenShield::create(); };

	// Necklaces
	this->deserializers[GlowingPendant::SaveKeyGlowingPendant] = [=]() { return (Item*)GlowingPendant::create(); };

	// Keys
	this->deserializers[MagesGuildPrisonKey::SaveKeyMagesGuildPrisonKey] = [=]() { return (Item*)MagesGuildPrisonKey::create(); };
	this->deserializers[MayanGemBlueItem::SaveKeyMayanGemBlueItem] = [=]() { return (Item*)MayanGemBlueItem::create(); };
	this->deserializers[MayanGemPurpleItem::SaveKeyMayanGemPurpleItem] = [=]() { return (Item*)MayanGemPurpleItem::create(); };
	this->deserializers[MayanGemRedItem::SaveKeyMayanGemRedItem] = [=]() { return (Item*)MayanGemRedItem::create(); };
	this->deserializers[RamWheel::SaveKeyRamWheel] = [=]() { return (Item*)RamWheel::create(); };
	this->deserializers[TownKey::SaveKeyTownKey] = [=]() { return (Item*)TownKey::create(); };
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
