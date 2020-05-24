#include "ShopPoolMinos.h"

#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/ItemChance.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string ShopPoolMinos::MapKey = "shop-pool-minos";
const std::string ShopPoolMinos::PoolName = "shop-pool-minos";

ShopPoolMinos* ShopPoolMinos::create(ValueMap& properties)
{
	ShopPoolMinos* instance = new ShopPoolMinos(properties);

	instance->autorelease();

	return instance;
}

ShopPoolMinos::ShopPoolMinos(ValueMap& properties) : super(properties, ShopPoolMinos::PoolName, { })
{
	this->addItemToPool(ItemChance::create(Wood::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(Coal::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(Quartz::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(Copper::create(), ItemChance::Probability::Guaranteed));
	// this->addItemToPool(ItemChance::create(Iron::create(), ItemChance::Probability::Guaranteed));
	// this->addItemToPool(ItemChance::create(Tin::create(), ItemChance::Probability::Guaranteed));
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
