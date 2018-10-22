#include "HexusShopMenu.h"

const float HexusShopMenu::lootBoxScale = 0.5f;

HexusShopMenu * HexusShopMenu::create()
{
	HexusShopMenu* instance = new HexusShopMenu();

	instance->autorelease();

	return instance;
}

HexusShopMenu::HexusShopMenu()
{
	this->lootBoxes = std::vector<MenuSprite*>();
	this->storeBack = Sprite::create(Resources::Menus_StoreMenu_StoreBack);
	this->shopKeeper = Shopkeeper::create();
	this->storeFront = Sprite::create(Resources::Menus_StoreMenu_Store);
	this->storeMenu = Sprite::create(Resources::Menus_StoreMenu_StoreBoard);
	this->storeLabel = Label::create("Store", Localization::getMainFont(), Localization::getFontSizeH1(Localization::getMainFont()));
	this->storeLabel->enableOutline(Color4B::BLACK, 4);

	this->lootBoxButton = MenuSprite::create(Resources::Menus_StoreMenu_TabButton, Resources::Menus_StoreMenu_TabButtonSelected, Resources::Menus_StoreMenu_TabButtonSelected);
	this->binaryButton = MenuSprite::create(Resources::Menus_StoreMenu_TabButton, Resources::Menus_StoreMenu_TabButtonSelected, Resources::Menus_StoreMenu_TabButtonSelected);
	this->decimalButton = MenuSprite::create(Resources::Menus_StoreMenu_TabButton, Resources::Menus_StoreMenu_TabButtonSelected, Resources::Menus_StoreMenu_TabButtonSelected);
	this->hexButton = MenuSprite::create(Resources::Menus_StoreMenu_TabButton, Resources::Menus_StoreMenu_TabButtonSelected, Resources::Menus_StoreMenu_TabButtonSelected);

	this->lootBoxButton->addChild(Sprite::create(Resources::Menus_StoreMenu_IconLootBox));
	this->binaryButton->addChild(Sprite::create(Resources::Menus_StoreMenu_IconBin));
	this->decimalButton->addChild(Sprite::create(Resources::Menus_StoreMenu_IconDec));
	this->hexButton->addChild(Sprite::create(Resources::Menus_StoreMenu_IconHex));

	this->lootBoxes.push_back(this->constructLootBoxButton(Resources::Menus_StoreMenu_LootBoxes_JungleChestClosed, 5));
	this->lootBoxes.push_back(this->constructLootBoxButton(Resources::Menus_StoreMenu_LootBoxes_RuinsChestClosed, 10));
	this->lootBoxes.push_back(this->constructLootBoxButton(Resources::Menus_StoreMenu_LootBoxes_ForestChestClosed, 25));
	this->lootBoxes.push_back(this->constructLootBoxButton(Resources::Menus_StoreMenu_LootBoxes_CavernsChestClosed, 50));
	this->lootBoxes.push_back(this->constructLootBoxButton(Resources::Menus_StoreMenu_LootBoxes_CastleChestClosed, 100));
	this->lootBoxes.push_back(this->constructLootBoxButton(Resources::Menus_StoreMenu_LootBoxes_IceChestClosed, 250));
	this->lootBoxes.push_back(this->constructLootBoxButton(Resources::Menus_StoreMenu_LootBoxes_VolcanoChestClosed, 500));
	this->lootBoxes.push_back(this->constructLootBoxButton(Resources::Menus_StoreMenu_LootBoxes_ObeliskChestClosed, 1000));
	this->lootBoxes.push_back(this->constructLootBoxButton(Resources::Menus_StoreMenu_LootBoxes_VaporChestClosed, 1500));

	this->storeBack->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->storeFront->setAnchorPoint(Vec2(0.0f, 0.5f));

	this->addChild(this->storeBack);
	this->addChild(this->shopKeeper);
	this->addChild(this->storeFront);
	this->addChild(this->storeMenu);
	this->addChild(this->lootBoxButton);
	this->addChild(this->binaryButton);
	this->addChild(this->decimalButton);
	this->addChild(this->hexButton);
	this->addChild(this->storeLabel);

	for (auto it = this->lootBoxes.begin(); it != this->lootBoxes.end(); it++)
	{
		this->addChild(*it);
	}

	this->addChild(Mouse::create());
}

HexusShopMenu::~HexusShopMenu()
{
}

void HexusShopMenu::onEnter()
{
	FadeScene::onEnter();

	float delay = 0.25f;
	float duration = 0.35f;
}

void HexusShopMenu::initializeListeners()
{
	FadeScene::initializeListeners();

	EventListenerKeyboard* keyboardListener = EventListenerKeyboard::create();

	keyboardListener->onKeyPressed = CC_CALLBACK_2(HexusShopMenu::onKeyPressed, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);
}

void HexusShopMenu::initializePositions()
{
	FadeScene::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	const float storeOffsetY = -128.0f;
	const Vec2 storeMenuOffset = Vec2(320.0f, 0.0f);

	this->storeBack->setPosition(Vec2(0.0f, visibleSize.height / 2.0f + storeOffsetY + 144.0f));
	this->shopKeeper->setPosition(Vec2(visibleSize.width / 2.0f - 680.0f, visibleSize.height / 2.0f + storeOffsetY));
	this->storeFront->setPosition(Vec2(0.0f, visibleSize.height / 2.0f + storeOffsetY - 176.0f));
	this->storeMenu->setPosition(Vec2(visibleSize.width / 2.0f + storeMenuOffset.x, visibleSize.height / 2.0f));
	this->lootBoxButton->setPosition(Vec2(visibleSize.width / 2.0f + storeMenuOffset.x - 640.0f, visibleSize.height / 2.0f + 256.0f));
	this->binaryButton->setPosition(Vec2(visibleSize.width / 2.0f + storeMenuOffset.x - 640.0f, visibleSize.height / 2.0f + 128.0f));
	this->decimalButton->setPosition(Vec2(visibleSize.width / 2.0f + storeMenuOffset.x - 640.0f, visibleSize.height / 2.0f + 0.0f));
	this->hexButton->setPosition(Vec2(visibleSize.width / 2.0f + storeMenuOffset.x - 640.0f, visibleSize.height / 2.0f - 128.0f));
	this->storeLabel->setPosition(Vec2(visibleSize.width / 2.0f + storeMenuOffset.x, visibleSize.height / 2.0f));

	const Size chestGridSize = Size(288.0f, 240.0f);
	int index = 0;

	for (auto it = this->lootBoxes.begin(); it != this->lootBoxes.end(); it++)
	{
		int x = index % 3 - 1;
		int y = index / 3 - 1;

		(*it)->setPosition(Vec2(visibleSize.width / 2.0f + storeMenuOffset.x + x * chestGridSize.width, visibleSize.height / 2.0f + storeMenuOffset.y - 32.0f - y * chestGridSize.height));

		index++;
	}
}

MenuSprite* HexusShopMenu::constructLootBoxButton(std::string lootBoxIcon, int price)
{
	MenuSprite* frame = MenuSprite::create(Resources::Menus_StoreMenu_StoreOption, Resources::Menus_StoreMenu_StoreOptionSelected, Resources::Menus_StoreMenu_StoreOptionSelected);
	Sprite* sprite = Sprite::create(lootBoxIcon);
	Label* priceLabel = Label::create(std::to_string(price), Localization::getMainFont(), Localization::getFontSizeH3(Localization::getMainFont()));
	Sprite* goldIcon = Sprite::create(Resources::Menus_Objects_GOLD_1);

	sprite->setScale(HexusShopMenu::lootBoxScale);
	sprite->setPosition(Vec2(0.0f, 16.0f));

	frame->setClickCallback(CC_CALLBACK_1(HexusShopMenu::onLootBoxClick, this, price));
	goldIcon->setScale(0.75f);
	goldIcon->setPosition(Vec2(-32.0f, -72.0f));
	priceLabel->setAnchorPoint(Vec2(0.0f, 0.5f));
	priceLabel->setPosition(Vec2(16.0f, -72.0f));
	priceLabel->enableOutline(Color4B::BLACK, 4);

	frame->addChild(sprite);
	frame->addChild(goldIcon);
	frame->addChild(priceLabel);

	return frame;
}

void HexusShopMenu::onLootBoxClick(MenuSprite* sprite, int price)
{
	int gold = CardStorage::getGold();

	if (gold < price)
	{
		return;
	}

	gold -= price;

	CardStorage::saveGold(gold);

	sprite->runAction(Sequence::create(
		CallFunc::create([=]()
		{
			for (auto it = this->lootBoxes.begin(); it != this->lootBoxes.end(); it++)
			{
				(*it)->disableInteraction();
			}
		}),
		ScaleTo::create(0.5f, 1.0f),
		ScaleTo::create(0.5f, HexusShopMenu::lootBoxScale),
		CallFunc::create([=]()
		{
			for (auto it = this->lootBoxes.begin(); it != this->lootBoxes.end(); it++)
			{
				if (price <= gold)
				{
					(*it)->enableInteraction();
				}
			}
		}),
		nullptr
	));
}

void HexusShopMenu::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode)
	{
		case EventKeyboard::KeyCode::KEY_ESCAPE:
			event->stopPropagation();
			NavigationEvents::navigateBack();
			break;
		default:
			break;
	}
}
