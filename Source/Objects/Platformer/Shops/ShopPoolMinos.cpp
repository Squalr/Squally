#include "ShopPoolMinos.h"

#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Menus/Inventory/ItemPreview.h"
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
	this->addItemToPool(BlueAxe::create(), 1.0f);
	this->addItemToPool(CandySword::create(), 1.0f);
	this->addItemToPool(CrystalSword::create(), 1.0f);
	this->addItemToPool(SantaHat::create(), 1.0f);
	this->addItemToPool(WoodenShield::create(), 1.0f);
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
