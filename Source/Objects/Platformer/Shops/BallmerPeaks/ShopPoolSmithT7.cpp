#include "ShopPoolSmithT7.h"

#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/ItemChance.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string ShopPoolSmithT7::MapKey = "shop-pool-smith-t7";
const std::string ShopPoolSmithT7::PoolName = "shop-pool-smith-t7";

ShopPoolSmithT7* ShopPoolSmithT7::create(ValueMap& properties)
{
	ShopPoolSmithT7* instance = new ShopPoolSmithT7(properties);

	instance->autorelease();

	return instance;
}

ShopPoolSmithT7::ShopPoolSmithT7(ValueMap& properties) : super(properties, ShopPoolSmithT7::PoolName, { })
{
	this->addItemToPool(ItemChance::create(Wood::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(Coal::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(Emerald::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(Sapphire::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(Iron::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(Gold::create(), ItemChance::Probability::Guaranteed));
}

ShopPoolSmithT7::~ShopPoolSmithT7()
{
}
