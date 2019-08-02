#include "ShopItem.h"

#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Menus/Inventory/ItemPreview.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string ShopItem::MapKeyShopItem = "shop-item";

ShopItem* ShopItem::create(ValueMap& initProperties)
{
	ShopItem* instance = new ShopItem(initProperties);

	instance->autorelease();

	return instance;
}

ShopItem::ShopItem(ValueMap& initProperties) : super(initProperties)
{
	this->itemPreview = ItemPreview::create();
	this->itemClickHitbox = ClickableNode::create();

	this->itemClickHitbox->setContentSize(Size(224.0f, 224.0f));

	this->addChild(this->itemPreview);
	this->addChild(this->itemClickHitbox);
}

ShopItem::~ShopItem()
{
}

void ShopItem::onEnter()
{
	super::onEnter();
}

void ShopItem::initializePositions()
{
	super::initializePositions();
}

void ShopItem::initializeListeners()
{
	super::initializeListeners();
}
