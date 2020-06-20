#include "ChestPoolPinata.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

const std::string ChestPoolPinata::PoolName = "pinata";

ChestPoolPinata* ChestPoolPinata::create(ValueMap& properties)
{
	ChestPoolPinata* instance = new ChestPoolPinata(properties);

	instance->autorelease();

	return instance;
}

ChestPoolPinata::ChestPoolPinata(ValueMap& properties) : super(
	properties, ChestPoolPinata::PoolName, SampleMethod::Guarantee, 8, 45,
	{ })
{
	this->addItemToPool(ItemChance::create(CrystalBow::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(DemonicBow::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(GoldenBow::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(HuntersBow::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(IvyBow::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(SteelBow::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(VoidBow::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(WoodenBow::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(Bludgeon::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(BoneHammer::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(CopperMallet::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(CrystalMace::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(DemonicMace::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(GoldenMace::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(MithrilMace::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(SteelMace::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(Timmy::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(VoidMace::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(WitchingMace::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(WoodenClub::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(BoneAxe::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(CopperAxe::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(CrystalAxe::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(DemonicAxe::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(FrostAxe::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(GoldenAxe::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(MithrilAxe::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(Scythe::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(SteelAxe::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(VoidAxe::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(WoodenAxe::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(Bone::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(Coal::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(Copper::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(Diamond::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(Emerald::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(Gold::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(Iron::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(Mithril::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(Obsidian::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(Quartz::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(Ruby::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(Sapphire::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(Sulfur::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(Wood::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(Snowball::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(PhoenixFeather::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(Honey::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(Feather::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(Eggplant::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(Egg::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(DemonSkull::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(BlackBlood::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(VoidFlower::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(SandRoot::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(PoisonMushroom::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(Mandrake::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(GoldWeed::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(FrostBerries::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(DemonRoot::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(DarkSeed::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(Clover::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(VoidCrystal::create(), ItemChance::Probability::Common));
}

ChestPoolPinata::~ChestPoolPinata()
{
}
