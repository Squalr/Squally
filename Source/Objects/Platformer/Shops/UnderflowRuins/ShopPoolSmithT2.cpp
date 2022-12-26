#include "ShopPoolSmithT2.h"

#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/ItemChance.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string ShopPoolSmithT2::MapKey = "shop-pool-geryon";
const std::string ShopPoolSmithT2::PoolName = "shop-pool-geryon";

ShopPoolSmithT2* ShopPoolSmithT2::create(ValueMap& properties)
{
	ShopPoolSmithT2* instance = new ShopPoolSmithT2(properties);

	instance->autorelease();

	return instance;
}

ShopPoolSmithT2::ShopPoolSmithT2(ValueMap& properties) : super(properties, ShopPoolSmithT2::PoolName, { })
{
	this->addItemToPool(ItemChance::create(Wood::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(Coal::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(Quartz::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(Emerald::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(Copper::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(Iron::create(), ItemChance::Probability::Guaranteed));
}

ShopPoolSmithT2::~ShopPoolSmithT2()
{
}
