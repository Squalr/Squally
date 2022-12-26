#include "ShopPoolSmithT1.h"

#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/ItemChance.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string ShopPoolSmithT1::MapKey = "shop-pool-smith-t1";
const std::string ShopPoolSmithT1::PoolName = "shop-pool-smith-t1";

ShopPoolSmithT1* ShopPoolSmithT1::create(ValueMap& properties)
{
	ShopPoolSmithT1* instance = new ShopPoolSmithT1(properties);

	instance->autorelease();

	return instance;
}

ShopPoolSmithT1::ShopPoolSmithT1(ValueMap& properties) : super(properties, ShopPoolSmithT1::PoolName, { })
{
	this->addItemToPool(ItemChance::create(Wood::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(Coal::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(Quartz::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(Copper::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(Feather::create(), ItemChance::Probability::Guaranteed));
}

ShopPoolSmithT1::~ShopPoolSmithT1()
{
}
