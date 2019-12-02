#include "ShopPoolMinos.h"

#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/ItemChance.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Objects/Platformer/ItemPools/CardPools/CardPools.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string ShopPoolMinos::MapKeyShopPoolMinos = "shop-pool-minos";
const std::string ShopPoolMinos::PoolName = "minos";

ShopPoolMinos* ShopPoolMinos::create(ValueMap& properties)
{
	ShopPoolMinos* instance = new ShopPoolMinos(properties);

	instance->autorelease();

	return instance;
}

ShopPoolMinos::ShopPoolMinos(ValueMap& properties) : super(properties, ShopPoolMinos::PoolName)
{
	this->addItemToPool(ItemChance::create(IronSword::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(WoodenMallet::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(WoodCutter::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(WoodenWand::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(CompositeBow::create(), ItemChance::Probability::Guaranteed));
}

ShopPoolMinos::~ShopPoolMinos()
{
}

void ShopPoolMinos::onEnter()
{
	super::onEnter(); 
}

void ShopPoolMinos::initializePositions()
{
	super::initializePositions();
}

void ShopPoolMinos::initializeListeners()
{
	super::initializeListeners();
}
