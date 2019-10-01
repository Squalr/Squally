#include "ShopItem.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/ItemEvents.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/CurrencyInventory.h"
#include "Engine/Inventory/Inventory.h"
#include "Engine/Inventory/Item.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Utils/GameUtils.h"
#include "Menus/Inventory/ItemPreview.h"
#include "Objects/Platformer/Collectables/IOU.h"
#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string ShopItem::MapKeyShopItem = "shop-item";
const std::string ShopItem::MapKeyPropertyShopPool = "pool";

ShopItem* ShopItem::create(ValueMap& properties)
{
	ShopItem* instance = new ShopItem(properties);

	instance->autorelease();

	return instance;
}

ShopItem::ShopItem(ValueMap& properties) : super(properties)
{
	this->item = nullptr;
	this->itemPreview = ItemPreview::create(false, true);
	this->itemNode = Node::create();
	this->itemClickHitbox = ClickableNode::create();
	this->poolName = GameUtils::getKeyOrDefault(this->properties, ShopItem::MapKeyPropertyShopPool, Value("")).asString();
	this->currencySprite = Sprite::create(IOU::getIconResource());
	this->itemCostString = ConstantString::create(std::to_string(0));
	this->itemCostLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H2, this->itemCostString);
	this->itemCost = -1;
	this->available = true;

	this->currencySprite->setScale(0.4f);
	this->itemClickHitbox->setContentSize(Size(224.0f, 224.0f));
	this->itemCostLabel->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->itemCostLabel->enableOutline(Color4B::BLACK, 2);

	this->setVisible(false);

	this->addChild(this->itemPreview);
	this->addChild(this->itemNode);
	this->addChild(this->itemClickHitbox);
	this->addChild(this->currencySprite);
	this->addChild(this->itemCostLabel);
}

ShopItem::~ShopItem()
{
}

void ShopItem::onEnterTransitionDidFinish()
{
	super::onEnterTransitionDidFinish();

	ItemEvents::TriggerRequestItem(ItemEvents::ItemRequestArgs(this->poolName, [=](Item* item)
	{
		this->item = item;

		if (this->item != nullptr)
		{
			this->setVisible(true);
			this->itemNode->addChild(this->item);
			this->itemPreview->preview(this->item);

			CurrencyInventory* cost = item->getCost();

			if (cost != nullptr)
			{
				this->itemCost = cost->getCurrencyCount(IOU::getIdentifier());
				this->itemCostString->setString(std::to_string(this->itemCost));
			}
		}
		else
		{
			this->setVisible(false);
		}
	}));
}

void ShopItem::initializePositions()
{
	super::initializePositions();

	this->currencySprite->setPosition(Vec2(-32.0f, -132.0f));
	this->itemCostLabel->setPosition(Vec2(-32.0f + 24.0f, -132.0f));
}

void ShopItem::initializeListeners()
{
	super::initializeListeners();

	this->itemClickHitbox->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		this->sellItem();
	});
}

void ShopItem::sellItem()
{
	if (!this->available)
	{
		return;
	}

	CurrencyInventory* playerCurrencyInventory = CurrencyInventory::create(SaveKeys::SaveKeySquallyCurrencyInventory);
	int playerCurrency = playerCurrencyInventory->getCurrencyCount(IOU::getIdentifier());

	if (this->itemCost >= 0 && playerCurrency >= this->itemCost)
	{
		Inventory* playerInventory = Inventory::create(SaveKeys::SaveKeySquallyInventory);

		playerInventory->tryInsert(this->item->clone(),
		[=](Item*)
		{
			this->available = false;
			playerCurrencyInventory->removeCurrency(IOU::getIdentifier(), this->itemCost);
			this->itemPreview->preview(nullptr);
			this->currencySprite->setVisible(false);
			this->itemCostLabel->setVisible(false);
			this->itemClickHitbox->setMouseClickCallback(nullptr);
			this->itemClickHitbox->disableInteraction(0);
		},
		[=](Item*)
		{
			// Failure!
		});
	}
}
