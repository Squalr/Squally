#include "ShopPoolGeryon.h"

#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/ItemChance.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string ShopPoolGeryon::MapKey = "shop-pool-geryon";
const std::string ShopPoolGeryon::PoolName = "shop-pool-geryon";

ShopPoolGeryon* ShopPoolGeryon::create(ValueMap& properties)
{
	ShopPoolGeryon* instance = new ShopPoolGeryon(properties);

	instance->autorelease();

	return instance;
}

ShopPoolGeryon::ShopPoolGeryon(ValueMap& properties) : super(properties, ShopPoolGeryon::PoolName, { })
{
	this->addItemToPool(ItemChance::create(Wood::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(Coal::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(Quartz::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(Copper::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(Iron::create(), ItemChance::Probability::Guaranteed));
}

ShopPoolGeryon::~ShopPoolGeryon()
{
}

void ShopPoolGeryon::onEnter()
{
	super::onEnter(); 
}

void ShopPoolGeryon::initializePositions()
{
	super::initializePositions();
}

void ShopPoolGeryon::initializeListeners()
{
	super::initializeListeners();
}
