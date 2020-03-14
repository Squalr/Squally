#include "ShopPoolToben.h"

#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/ItemChance.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier1/CardPoolTier1.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string ShopPoolToben::MapKeyShopPoolToben = "shop-pool-toben";
const std::string ShopPoolToben::PoolName = "shop-pool-toben";

ShopPoolToben* ShopPoolToben::create(ValueMap& properties)
{
	ShopPoolToben* instance = new ShopPoolToben(properties);

	instance->autorelease();

	return instance;
}

ShopPoolToben::ShopPoolToben(ValueMap& properties) : super(properties, ShopPoolToben::PoolName,
	{ CardPoolTier1::create(SampleMethod::Guarantee, 3, 3) })
{
	this->addItemToPool(ItemChance::create(HealthPotion::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(ManaPotion::create(), ItemChance::Probability::Guaranteed));
}

ShopPoolToben::~ShopPoolToben()
{
}

void ShopPoolToben::onEnter()
{
	super::onEnter(); 
}

void ShopPoolToben::initializePositions()
{
	super::initializePositions();
}

void ShopPoolToben::initializeListeners()
{
	super::initializeListeners();
}
