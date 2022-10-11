#include "ShopPoolBrock.h"

#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/ItemChance.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string ShopPoolBrock::MapKey = "shop-pool-brock";
const std::string ShopPoolBrock::PoolName = "shop-pool-brock";

ShopPoolBrock* ShopPoolBrock::create(ValueMap& properties)
{
	ShopPoolBrock* instance = new ShopPoolBrock(properties);

	instance->autorelease();

	return instance;
}

ShopPoolBrock::ShopPoolBrock(ValueMap& properties) : super(properties, ShopPoolBrock::PoolName, { })
{
	this->addItemToPool(ItemChance::create(Wood::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(Coal::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(Emerald::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(Sapphire::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(Iron::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(Gold::create(), ItemChance::Probability::Guaranteed));
}

ShopPoolBrock::~ShopPoolBrock()
{
}
