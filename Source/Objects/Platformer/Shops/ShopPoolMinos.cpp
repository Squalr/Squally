#include "ShopPoolMinos.h"

#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
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

ShopPoolMinos::ShopPoolMinos(ValueMap& properties) : super(properties, ShopPoolMinos::PoolName, CardShopPoolTier1::create())
{
	this->addItemToPool(IronSword::create(), 1.0f);
	this->addItemToPool(WoodenMallet::create(), 1.0f);
	this->addItemToPool(WoodCutter::create(), 1.0f);
	this->addItemToPool(WoodenWand::create(), 1.0f);
	this->addItemToPool(CompositeBow::create(), 1.0f);
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
