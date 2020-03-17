#include "SmithingPoolEF.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

const std::string SmithingPoolEF::PoolName = "smithing-pool-ef";

SmithingPoolEF* SmithingPoolEF::create(ValueMap& properties)
{
	SmithingPoolEF* instance = new SmithingPoolEF(properties);

	instance->autorelease();

	return instance;
}

SmithingPoolEF::SmithingPoolEF(ValueMap& properties) : super(properties, SmithingPoolEF::PoolName, SampleMethod::Unbounded, 1, 1)
{
	this->addItemToPool(ItemChance::create(IronSwordPlans::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(RapierPlans::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(WoodenMalletPlans::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(SpikedClubPlans::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(WoodenWandPlans::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(EnchantedWandPlans::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(HandAxePlans::create(), ItemChance::Probability::Guaranteed));
}

SmithingPoolEF::~SmithingPoolEF()
{
}
