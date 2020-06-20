#include "SmithingPoolVS.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

const std::string SmithingPoolVS::PoolName = "smithing-pool-vs";

SmithingPoolVS* SmithingPoolVS::create(ValueMap& properties)
{
	SmithingPoolVS* instance = new SmithingPoolVS(properties);

	instance->autorelease();

	return instance;
}

SmithingPoolVS::SmithingPoolVS(ValueMap& properties) : super(properties, SmithingPoolVS::PoolName, SampleMethod::Unbounded, 1, 1)
{
	// Allows for stability in item ordering
	this->toggleDisableShuffle(true);
	
	this->addItemToPool(ItemChance::create(VoidSwordPlans::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(VoidAxePlans::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(VoidMacePlans::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(VoidBowPlans::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(VoidWandPlans::create(), ItemChance::Probability::Guaranteed));
	
	this->addItemToPool(ItemChance::create(BoneSwordPlans::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(BoneAxePlans::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(BoneHammerPlans::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(BoneBowPlans::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(BoneWandPlans::create(), ItemChance::Probability::Guaranteed));
	
	this->addItemToPool(ItemChance::create(DemonicSwordPlans::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(DemonicAxePlans::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(DemonicMacePlans::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(DemonicBowPlans::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(DemonicWandPlans::create(), ItemChance::Probability::Guaranteed));
	
	this->addItemToPool(ItemChance::create(CrystalSwordPlans::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(CrystalAxePlans::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(CrystalMacePlans::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(CrystalBowPlans::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(CrystalWandPlans::create(), ItemChance::Probability::Guaranteed));
	
	this->addItemToPool(ItemChance::create(MithrilSwordPlans::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(MithrilAxePlans::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(MithrilMacePlans::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(IvyBowPlans::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(SapphireWandPlans::create(), ItemChance::Probability::Guaranteed));
	
	this->addItemToPool(ItemChance::create(GoldenSwordPlans::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(GoldenAxePlans::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(GoldenMacePlans::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(GoldenBowPlans::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(SapphireWandPlans::create(), ItemChance::Probability::Guaranteed));
	
	this->addItemToPool(ItemChance::create(SteelSwordPlans::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(SteelAxePlans::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(SteelMacePlans::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(SteelBowPlans::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(EmeraldWandPlans::create(), ItemChance::Probability::Guaranteed));
	
	this->addItemToPool(ItemChance::create(CopperSwordPlans::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(CopperAxePlans::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(CopperMalletPlans::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(HuntersBowPlans::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(QuartzWandPlans::create(), ItemChance::Probability::Guaranteed));
	
	this->addItemToPool(ItemChance::create(WoodenSwordPlans::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(WoodenAxePlans::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(WoodenClubPlans::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(WoodenBowPlans::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(WoodenWandPlans::create(), ItemChance::Probability::Guaranteed));
}

SmithingPoolVS::~SmithingPoolVS()
{
}
