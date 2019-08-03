#include "ShopItem.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/CurrencyInventory.h"
#include "Engine/Inventory/Item.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Utils/GameUtils.h"
#include "Events/ShopEvents.h"
#include "Menus/Inventory/ItemPreview.h"
#include "Objects/Platformer/Collectables/IOU.h"

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
	this->currencySprite = Sprite::create(IOU::getIconResource());
	this->itemCostString = ConstantString::create(std::to_string(0));
	this->itemCost = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H2, this->itemCostString);

	this->currencySprite->setScale(0.4f);
	this->itemClickHitbox->setContentSize(Size(224.0f, 224.0f));
	this->itemCost->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->itemCost->enableOutline(Color4B::BLACK, 2);

	this->addChild(this->itemPreview);
	this->addChild(this->itemNode);
	this->addChild(this->itemClickHitbox);
	this->addChild(this->currencySprite);
	this->addChild(this->itemCost);
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

			CurrencyInventory* cost = item->getCost();

			if (cost != nullptr)
			{
				this->itemCostString->setString(std::to_string(cost->getCurrencyCount(IOU::getIdentifier())));
			}
		}
	}));
}

void ShopItem::initializePositions()
{
	super::initializePositions();

	this->currencySprite->setPosition(Vec2(-32.0f, -132.0f));
	this->itemCost->setPosition(Vec2(-32.0f + 24.0f, -132.0f));
}

void ShopItem::initializeListeners()
{
	super::initializeListeners();
}
