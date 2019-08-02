#include "ShopItem.h"

#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/Item.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Events/ShopEvents.h"
#include "Menus/Inventory/ItemPreview.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string ShopItem::MapKeyShopItem = "shop-item";
const std::string ShopItem::MapKeyPropertyShopPool = "pool";

ShopItem* ShopItem::create(ValueMap& initProperties)
{
	ShopItem* instance = new ShopItem(initProperties);

	instance->autorelease();

	return instance;
}

ShopItem::ShopItem(ValueMap& initProperties) : super(initProperties)
{
	this->item = nullptr;
	this->itemPreview = ItemPreview::create(false);
	this->itemNode = Node::create();
	this->itemClickHitbox = ClickableNode::create();
	this->poolName = GameUtils::getKeyOrDefault(this->properties, ShopItem::MapKeyPropertyShopPool, Value("")).asString();

	this->itemClickHitbox->setContentSize(Size(224.0f, 224.0f));

	this->addChild(this->itemPreview);
	this->addChild(this->itemNode);
	this->addChild(this->itemClickHitbox);
}

ShopItem::~ShopItem()
{
}

void ShopItem::onEnterTransitionDidFinish()
{
	super::onEnterTransitionDidFinish();

	ShopEvents::TriggerRequestItem(ShopEvents::ItemRequestArgs(this->poolName, [=](Item* item)
	{
		this->item = item;

		if (this->item != nullptr)
		{
			this->itemNode->addChild(this->item);
			this->itemPreview->preview(this->item);
		}
	}));
}

void ShopItem::initializePositions()
{
	super::initializePositions();
}

void ShopItem::initializeListeners()
{
	super::initializeListeners();
}
