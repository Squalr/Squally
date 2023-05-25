#include "SmithingPoolCV.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

const std::string SmithingPoolCV::PoolName = "smithing-pool-cv";

SmithingPoolCV* SmithingPoolCV::create(ValueMap& properties)
{
	SmithingPoolCV* instance = new SmithingPoolCV(properties);

	instance->autorelease();

	return instance;
}

SmithingPoolCV::SmithingPoolCV(ValueMap& properties) : super(properties, SmithingPoolCV::PoolName, SampleMethod::Unbounded, 1, 1)
{
	// Allows for stability in item ordering
	this->toggleDisableShuffle(true);
	
	this->addItemToPool(ItemChance::create(MithrilSwordPlans::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(MithrilAxePlans::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(MithrilMacePlans::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(IvyBowPlans::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(SapphireWandPlans::create(), ItemChance::Probability::Guaranteed));
	
	this->addItemToPool(ItemChance::create(GoldenSwordPlans::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(GoldenAxePlans::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(GoldenMacePlans::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(GoldenBowPlans::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(GoldenWandPlans::create(), ItemChance::Probability::Guaranteed));
	
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

SmithingPoolCV::~SmithingPoolCV()
{
}
