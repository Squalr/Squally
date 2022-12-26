#include "ShopPoolSmithT4.h"

#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/ItemChance.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string ShopPoolSmithT4::MapKey = "shop-pool-smith-t4";
const std::string ShopPoolSmithT4::PoolName = "shop-pool-smith-t4";

ShopPoolSmithT4* ShopPoolSmithT4::create(ValueMap& properties)
{
	ShopPoolSmithT4* instance = new ShopPoolSmithT4(properties);

	instance->autorelease();

	return instance;
}

ShopPoolSmithT4::ShopPoolSmithT4(ValueMap& properties) : super(properties, ShopPoolSmithT4::PoolName, { })
{
	this->addItemToPool(ItemChance::create(Wood::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(Coal::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(Emerald::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(Sapphire::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(Iron::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(Gold::create(), ItemChance::Probability::Guaranteed));
}

ShopPoolSmithT4::~ShopPoolSmithT4()
{
}
