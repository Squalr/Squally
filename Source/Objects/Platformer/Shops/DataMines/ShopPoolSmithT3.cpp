#include "ShopPoolSmithT3.h"

#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/ItemChance.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string ShopPoolSmithT3::MapKey = "shop-pool-smith-t3";
const std::string ShopPoolSmithT3::PoolName = "shop-pool-smith-t3";

ShopPoolSmithT3* ShopPoolSmithT3::create(ValueMap& properties)
{
	ShopPoolSmithT3* instance = new ShopPoolSmithT3(properties);

	instance->autorelease();

	return instance;
}

ShopPoolSmithT3::ShopPoolSmithT3(ValueMap& properties) : super(properties, ShopPoolSmithT3::PoolName, { })
{
	// Phasing in
	this->addItemToPool(ItemChance::create(Gold::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(Emerald::create(), ItemChance::Probability::Guaranteed));
	
	// Phasing out
	this->addItemToPool(ItemChance::create(Iron::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(Silver::create(), ItemChance::Probability::Guaranteed));

	// Universal
	this->addItemToPool(ItemChance::create(Wood::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(Coal::create(), ItemChance::Probability::Guaranteed));
}

ShopPoolSmithT3::~ShopPoolSmithT3()
{
}
