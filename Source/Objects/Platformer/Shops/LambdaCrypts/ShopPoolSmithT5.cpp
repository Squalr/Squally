#include "ShopPoolSmithT5.h"

#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/ItemChance.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string ShopPoolSmithT5::MapKey = "shop-pool-smith-t5";
const std::string ShopPoolSmithT5::PoolName = "shop-pool-smith-t5";

ShopPoolSmithT5* ShopPoolSmithT5::create(ValueMap& properties)
{
	ShopPoolSmithT5* instance = new ShopPoolSmithT5(properties);

	instance->autorelease();

	return instance;
}

ShopPoolSmithT5::ShopPoolSmithT5(ValueMap& properties) : super(properties, ShopPoolSmithT5::PoolName, { })
{
	this->addItemToPool(ItemChance::create(Wood::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(Coal::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(Emerald::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(Sapphire::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(Iron::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(Gold::create(), ItemChance::Probability::Guaranteed));
}

ShopPoolSmithT5::~ShopPoolSmithT5()
{
}
