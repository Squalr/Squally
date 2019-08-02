#include "ShopPoolToben.h"

#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Menus/Inventory/ItemPreview.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string ShopPoolToben::MapKeyShopPoolToben = "shop-pool-toben";
const std::string ShopPoolToben::PoolName = "toben";

ShopPoolToben* ShopPoolToben::create(ValueMap& initProperties)
{
	ShopPoolToben* instance = new ShopPoolToben(initProperties);

	instance->autorelease();

	return instance;
}

ShopPoolToben::ShopPoolToben(ValueMap& initProperties) : super(initProperties, ShopPoolToben::PoolName)
{
	this->addItemToPool(HealthPotion::create(), 1.0f);
	this->addItemToPool(ManaPotion::create(), 1.0f);
	this->addItemToPool(SpeedRune::create(), 1.0f);
	this->addItemToPool(BlueAxe::create(), 1.0f);
	this->addItemToPool(CandySword::create(), 1.0f);
	this->addItemToPool(CrystalSword::create(), 1.0f);
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
