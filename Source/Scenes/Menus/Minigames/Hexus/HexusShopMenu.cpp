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
	this->binaryCards = std::map<int, Node*>();
	this->decimalCards = std::map<int, Node*>();
	this->hexCards = std::map<int, Node*>();
	this->specialCards = std::vector<Node*>();

	this->dustParticles = ParticleSystemQuad::create(Resources::Particles_Dust);

	this->goldPanel = Sprite::create(Resources::Menus_StoreMenu_GoldPanel);
	this->goldIcon = Sprite::create(Resources::Menus_Objects_GOLD_2);
	this->goldLabel = Label::create("", Localization::getMainFont(), Localization::getFontSizeH2(Localization::getMainFont()));

	this->goldLabel->enableOutline(Color4B::BLACK, 3);
	this->goldLabel->setPosition(Vec2(-32.0f, 0.0f));
	this->goldLabel->setAlignment(TextHAlignment::LEFT);
	this->goldLabel->setAnchorPoint(Vec2(0.0f, 0.5f));

	this->storeBack = Sprite::create(Resources::Menus_StoreMenu_StoreBack);
	this->shopKeeper = Shopkeeper::create();
	this->storeFront = Sprite::create(Resources::Menus_StoreMenu_Store);
	this->storeNode = Node::create();
	this->lootboxesNode = Node::create();
	this->storeMenu = Sprite::create(Resources::Menus_StoreMenu_StoreBoard);
	this->storeLabel = Label::create("HEXUS STORE", Localization::getMainFont(), Localization::getFontSizeH1(Localization::getMainFont()));
	this->storeLabel->enableOutline(Color4B::BLACK, 3);
	this->storeLabel->setAlignment(TextHAlignment::CENTER);
	this->storeLabel->setAnchorPoint(Vec2(0.5f, 0.5f));

	this->lootBoxButton = MenuSprite::create(Resources::Menus_StoreMenu_TabButton, Resources::Menus_StoreMenu_TabButtonSelected, Resources::Menus_StoreMenu_TabButtonSelected);
	this->binaryButton = MenuSprite::create(Resources::Menus_StoreMenu_TabButton, Resources::Menus_StoreMenu_TabButtonSelected, Resources::Menus_StoreMenu_TabButtonSelected);
	this->decimalButton = MenuSprite::create(Resources::Menus_StoreMenu_TabButton, Resources::Menus_StoreMenu_TabButtonSelected, Resources::Menus_StoreMenu_TabButtonSelected);
	this->hexButton = MenuSprite::create(Resources::Menus_StoreMenu_TabButton, Resources::Menus_StoreMenu_TabButtonSelected, Resources::Menus_StoreMenu_TabButtonSelected);
	this->specialButton = MenuSprite::create(Resources::Menus_StoreMenu_TabButton, Resources::Menus_StoreMenu_TabButtonSelected, Resources::Menus_StoreMenu_TabButtonSelected);

	const Size scrollPaneSize = Size(840.0f, 720.0f);

	this->binaryCardsScrollPane = ScrollPane::create(scrollPaneSize, Color4B(0, 0, 0, 196));
	this->decimalCardsScrollPane = ScrollPane::create(scrollPaneSize, Color4B(0, 0, 0, 196));
	this->hexCardsScrollPane = ScrollPane::create(scrollPaneSize, Color4B(0, 0, 0, 196));
	this->specialCardsScrollPane = ScrollPane::create(scrollPaneSize, Color4B(0, 0, 0, 196));

	Sprite* lootBoxIcon = Sprite::create(Resources::Menus_StoreMenu_IconLootBox);
	Sprite* binaryIcon = Sprite::create(Resources::Menus_StoreMenu_IconBin);
	Sprite* decimalIcon = Sprite::create(Resources::Menus_StoreMenu_IconDec);
	Sprite* hexIcon = Sprite::create(Resources::Menus_StoreMenu_IconHex);
	Sprite* specialIcon = Sprite::create(Resources::Menus_StoreMenu_IconSpecial);

	lootBoxIcon->setPosition(Vec2(-32.0f, 0.0f));
	binaryIcon->setPosition(Vec2(-32.0f, 0.0f));
	decimalIcon->setPosition(Vec2(-32.0f, 0.0f));
	hexIcon->setPosition(Vec2(-32.0f, 0.0f));
	specialIcon->setPosition(Vec2(-32.0f, 0.0f));

	Label* binaryLabel = Label::create("1111", Localization::getMainFont(), Localization::getFontSizeH1(Localization::getMainFont()));
	Label* decimalLabel = Label::create("15", Localization::getMainFont(), Localization::getFontSizeH1(Localization::getMainFont()));
	Label* hexLabel = Label::create("F", Localization::getMainFont(), Localization::getFontSizeH1(Localization::getMainFont()));
	Label* specialLabel = Label::create("OR", Localization::getMainFont(), Localization::getFontSizeH1(Localization::getMainFont()));

	binaryLabel->enableOutline(Color4B::BLACK, 3);
	binaryLabel->setPosition(Vec2(-32.0f, 0.0f));
	binaryLabel->setAlignment(TextHAlignment::CENTER);
	binaryLabel->setAnchorPoint(Vec2(0.5f, 0.5f));
	decimalLabel->enableOutline(Color4B::BLACK, 3);
	decimalLabel->setPosition(Vec2(-32.0f, 0.0f));
	decimalLabel->setAlignment(TextHAlignment::CENTER);
	decimalLabel->setAnchorPoint(Vec2(0.5f, 0.5f));
	hexLabel->enableOutline(Color4B::BLACK, 3);
	hexLabel->setPosition(Vec2(-32.0f, 0.0f));
	hexLabel->setAlignment(TextHAlignment::CENTER);
	hexLabel->setAnchorPoint(Vec2(0.5f, 0.5f));
	specialLabel->enableOutline(Color4B::BLACK, 3);
	specialLabel->setPosition(Vec2(-32.0f, 0.0f));
	specialLabel->setAlignment(TextHAlignment::CENTER);
	specialLabel->setAnchorPoint(Vec2(0.5f, 0.5f));

	binaryLabel->setTextColor(Card::binaryColor);
	decimalLabel->setTextColor(Card::decimalColor);
	hexLabel->setTextColor(Card::hexColor);
	specialLabel->setTextColor(Card::specialColor);

	this->lootBoxButton->addChild(lootBoxIcon);
	this->binaryButton->addChild(binaryIcon);
	this->decimalButton->addChild(decimalIcon);
	this->hexButton->addChild(hexIcon);
	this->specialButton->addChild(specialIcon);

	this->binaryButton->addChild(binaryLabel);
	this->decimalButton->addChild(decimalLabel);
	this->hexButton->addChild(hexLabel);
	this->specialButton->addChild(specialLabel);

	this->lootBoxes.push_back(this->constructLootBoxButton(Resources::Menus_StoreMenu_LootBoxes_JungleChestClosed, 5));
	this->lootBoxes.push_back(this->constructLootBoxButton(Resources::Menus_StoreMenu_LootBoxes_RuinsChestClosed, 10));
	this->lootBoxes.push_back(this->constructLootBoxButton(Resources::Menus_StoreMenu_LootBoxes_ForestChestClosed, 25));
	this->lootBoxes.push_back(this->constructLootBoxButton(Resources::Menus_StoreMenu_LootBoxes_CavernsChestClosed, 50));
	this->lootBoxes.push_back(this->constructLootBoxButton(Resources::Menus_StoreMenu_LootBoxes_CastleChestClosed, 100));
	this->lootBoxes.push_back(this->constructLootBoxButton(Resources::Menus_StoreMenu_LootBoxes_IceChestClosed, 250));
	this->lootBoxes.push_back(this->constructLootBoxButton(Resources::Menus_StoreMenu_LootBoxes_VolcanoChestClosed, 500));
	this->lootBoxes.push_back(this->constructLootBoxButton(Resources::Menus_StoreMenu_LootBoxes_ObeliskChestClosed, 1000));
	this->lootBoxes.push_back(this->constructLootBoxButton(Resources::Menus_StoreMenu_LootBoxes_VaporChestClosed, 1500));

	for (auto it = CardList::getInstance()->cardListByName->begin(); it != CardList::getInstance()->cardListByName->end(); it++)
	{
		CardData* cardData = (*it).second;

		switch (cardData->cardType)
		{
			case CardData::Binary:
				this->binaryCards.emplace(cardData->attack, this->constructCard(cardData));
				break;
			case CardData::Decimal:
				this->decimalCards.emplace(cardData->attack, this->constructCard(cardData));
				break;
			case CardData::Hexidecimal:
				this->hexCards.emplace(cardData->attack, this->constructCard(cardData));
				break;
			default:
				this->specialCards.push_back(this->constructCard(cardData));
				break;
		}
	}

	this->storeBack->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->storeFront->setAnchorPoint(Vec2(0.0f, 0.5f));

	this->addChild(this->dustParticles);
	this->addChild(this->storeBack);
	this->addChild(this->shopKeeper);
	this->addChild(this->storeFront);
	this->addChild(storeNode);
	this->storeNode->addChild(this->storeMenu);
	this->storeNode->addChild(this->goldPanel);
	this->storeNode->addChild(this->goldIcon);
	this->storeNode->addChild(this->goldLabel);
	this->storeNode->addChild(this->lootboxesNode);
	this->storeNode->addChild(this->binaryCardsScrollPane);
	this->storeNode->addChild(this->decimalCardsScrollPane);
	this->storeNode->addChild(this->hexCardsScrollPane);
	this->storeNode->addChild(this->specialCardsScrollPane);
	this->storeNode->addChild(this->lootBoxButton);
	this->storeNode->addChild(this->binaryButton);
	this->storeNode->addChild(this->hexButton);
	this->storeNode->addChild(this->decimalButton);
	this->storeNode->addChild(this->specialButton);
	this->addChild(this->storeLabel);

	for (auto it = this->lootBoxes.begin(); it != this->lootBoxes.end(); it++)
	{
		this->lootboxesNode->addChild(*it);
	}

	for (auto it = this->binaryCards.begin(); it != this->binaryCards.end(); it++)
	{
		this->binaryCardsScrollPane->addChild((*it).second);
	}

	for (auto it = this->decimalCards.begin(); it != this->decimalCards.end(); it++)
	{
		this->decimalCardsScrollPane->addChild((*it).second);
	}

	for (auto it = this->hexCards.begin(); it != this->hexCards.end(); it++)
	{
		this->hexCardsScrollPane->addChild((*it).second);
	}

	for (auto it = this->specialCards.begin(); it != this->specialCards.end(); it++)
	{
		this->specialCardsScrollPane->addChild(*it);
	}

	this->addChild(Mouse::create());

	this->onLootBoxTabClick();
	this->updateGoldText();
}

HexusShopMenu::~HexusShopMenu()
{
}

void HexusShopMenu::onEnter()
{
	FadeScene::onEnter();

	float delay = 0.25f;
	float duration = 0.35f;

	GameUtils::accelerateParticles(this->dustParticles, 5.0f);
}

void HexusShopMenu::initializeListeners()
{
	FadeScene::initializeListeners();

	EventListenerKeyboard* keyboardListener = EventListenerKeyboard::create();

	keyboardListener->onKeyPressed = CC_CALLBACK_2(HexusShopMenu::onKeyPressed, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);

	this->lootBoxButton->setClickCallback(CC_CALLBACK_0(HexusShopMenu::onLootBoxTabClick, this));
	this->binaryButton->setClickCallback(CC_CALLBACK_0(HexusShopMenu::onBinaryTabClick, this));
	this->decimalButton->setClickCallback(CC_CALLBACK_0(HexusShopMenu::onDecimalTabClick, this));
	this->hexButton->setClickCallback(CC_CALLBACK_0(HexusShopMenu::onHexTabClick, this));
	this->specialButton->setClickCallback(CC_CALLBACK_0(HexusShopMenu::onSpecialTabClick, this));
}

void HexusShopMenu::initializePositions()
{
	FadeScene::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	const float storeOffsetY = -128.0f;
	const Vec2 storeMenuOffset = Vec2(352.0f, 0.0f);
	const Vec2 storeContentOffset = Vec2(0.0f, -64.0f);
	const Vec2 goldPanelOffset = Vec2(448.0f, 464.0f);

	this->dustParticles->setPosition(Vec2(visibleSize.width, visibleSize.height / 2));
	this->storeBack->setPosition(Vec2(0.0f, visibleSize.height / 2.0f + storeOffsetY + 144.0f));
	this->shopKeeper->setPosition(Vec2(visibleSize.width / 2.0f - 680.0f, visibleSize.height / 2.0f + storeOffsetY));
	this->storeFront->setPosition(Vec2(0.0f, visibleSize.height / 2.0f + storeOffsetY - 176.0f));
	this->storeMenu->setPosition(Vec2(visibleSize.width / 2.0f + storeMenuOffset.x, visibleSize.height / 2.0f + storeMenuOffset.y));

	this->goldPanel->setPosition(Vec2(visibleSize.width / 2.0f + storeMenuOffset.x + goldPanelOffset.x, visibleSize.height / 2.0f + storeMenuOffset.y + goldPanelOffset.y));
	this->goldIcon->setPosition(Vec2(visibleSize.width / 2.0f + storeMenuOffset.x + goldPanelOffset.x - 48.0f, visibleSize.height / 2.0f + storeMenuOffset.y + goldPanelOffset.y));
	this->goldLabel->setPosition(Vec2(visibleSize.width / 2.0f + storeMenuOffset.x + goldPanelOffset.x + 24.0f, visibleSize.height / 2.0f + storeMenuOffset.y + goldPanelOffset.y));

	this->lootboxesNode->setPosition(Vec2(visibleSize.width / 2.0f + storeMenuOffset.x + storeContentOffset.x, visibleSize.height / 2.0f + storeMenuOffset.y + storeContentOffset.y));
	this->binaryCardsScrollPane->setPosition(Vec2(visibleSize.width / 2.0f + storeMenuOffset.x + storeContentOffset.x, visibleSize.height / 2.0f + storeMenuOffset.y + storeContentOffset.y));
	this->decimalCardsScrollPane->setPosition(Vec2(visibleSize.width / 2.0f + storeMenuOffset.x + storeContentOffset.x, visibleSize.height / 2.0f + storeMenuOffset.y + storeContentOffset.y));
	this->hexCardsScrollPane->setPosition(Vec2(visibleSize.width / 2.0f + storeMenuOffset.x + storeContentOffset.x, visibleSize.height / 2.0f + storeMenuOffset.y + storeContentOffset.y));
	this->specialCardsScrollPane->setPosition(Vec2(visibleSize.width / 2.0f + storeMenuOffset.x + storeContentOffset.x, visibleSize.height / 2.0f + storeMenuOffset.y + storeContentOffset.y));
	this->lootBoxButton->setPosition(Vec2(visibleSize.width / 2.0f + storeMenuOffset.x - 640.0f, visibleSize.height / 2.0f + 256.0f - 144.0f * 0));
	this->binaryButton->setPosition(Vec2(visibleSize.width / 2.0f + storeMenuOffset.x - 640.0f, visibleSize.height / 2.0f + 256.0f - 144.0f * 1));
	this->decimalButton->setPosition(Vec2(visibleSize.width / 2.0f + storeMenuOffset.x - 640.0f, visibleSize.height / 2.0f + 256.0f - 144.0f * 2));
	this->hexButton->setPosition(Vec2(visibleSize.width / 2.0f + storeMenuOffset.x - 640.0f, visibleSize.height / 2.0f + 256.0f - 144.0f * 3));
	this->specialButton->setPosition(Vec2(visibleSize.width / 2.0f + storeMenuOffset.x - 640.0f, visibleSize.height / 2.0f + 256.0f - 144.0f * 4));
	this->storeLabel->setPosition(Vec2(visibleSize.width / 2.0f + storeMenuOffset.x, visibleSize.height / 2.0f + 448.0f));

	const Size chestGridSize = Size(288.0f, 240.0f);
	int index = 0;

	for (auto it = this->lootBoxes.begin(); it != this->lootBoxes.end(); it++)
	{
		int x = index % 3 - 1;
		int y = index / 3 - 1;

		(*it)->setPosition(Vec2(x * chestGridSize.width, - 32.0f - y * chestGridSize.height));

		index++;
	}

	const Size cardGridSize = Size(256.0f, 384.0f);

	index = 0;

	for (auto it = this->binaryCards.begin(); it != this->binaryCards.end(); it++)
	{
		int x = index % 3 - 1;
		int y = (this->binaryCards.size() - 1 - index + (3 - this->binaryCards.size() % 3)) / 3 - (this->binaryCards.size() % 3 == 0 ? 1 : 0);

		(*it).second->setPosition(Vec2(x * cardGridSize.width + this->binaryCardsScrollPane->getPaneSize().width / 2.0f, 128.0f + y * cardGridSize.height));

		index++;
	}

	index = 0;

	for (auto it = this->decimalCards.begin(); it != this->decimalCards.end(); it++)
	{
		int x = index % 3 - 1;
		int y = (this->decimalCards.size() - 1 - index + (3 - this->decimalCards.size() % 3)) / 3 - (this->decimalCards.size() % 3 == 0 ? 1 : 0);

		(*it).second->setPosition(Vec2(x * cardGridSize.width + this->decimalCardsScrollPane->getPaneSize().width / 2.0f, 128.0f + y * cardGridSize.height));

		index++;
	}

	index = 0;

	for (auto it = this->hexCards.begin(); it != this->hexCards.end(); it++)
	{
		int x = index % 3 - 1;
		int y = (this->hexCards.size() - 1 - index + (3 - this->hexCards.size() % 3)) / 3 - (this->hexCards.size() % 3 == 0 ? 1 : 0);

		(*it).second->setPosition(Vec2(x * cardGridSize.width + this->hexCardsScrollPane->getPaneSize().width / 2.0f, 128.0f + y * cardGridSize.height));

		index++;
	}

	index = 0;

	for (auto it = this->specialCards.begin(); it != this->specialCards.end(); it++)
	{
		int x = index % 3 - 1;
		int y = (this->specialCards.size() - 1 - index + (3 - this->specialCards.size() % 3)) / 3 - (this->specialCards.size() % 3 == 0 ? 1 : 0);

		(*it)->setPosition(Vec2(x * cardGridSize.width + this->specialCardsScrollPane->getPaneSize().width / 2.0f, 128.0f + y * cardGridSize.height));

		index++;
	}

	binaryCardsScrollPane->fitSizeToContent(Rect(0.0f, 64.0f, 0.0f, 0.0f));
	decimalCardsScrollPane->fitSizeToContent(Rect(0.0f, 64.0f, 0.0f, 0.0f));
	hexCardsScrollPane->fitSizeToContent(Rect(0.0f, 64.0f, 0.0f, 0.0f));
	specialCardsScrollPane->fitSizeToContent(Rect(0.0f, 64.0f, 0.0f, 0.0f));
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

MenuSprite* HexusShopMenu::constructCard(CardData* cardData)
{
	MenuSprite* cardContainer = MenuSprite::create(Resources::Menus_StoreMenu_CardPanel, Resources::Menus_StoreMenu_CardPanelSelected, Resources::Menus_StoreMenu_CardPanelSelected);
	Card* card = nullptr;
	int price = 0;

	switch (cardData->cardType)
	{
		case CardData::CardType::Special_FLIP1:
		{
			price = 5;
			break;
		}
		case CardData::CardType::Special_FLIP2:
		{
			price = 150;
			break;
		}
		case CardData::CardType::Special_FLIP3:
		{
			price = 1250;
			break;
		}
		case CardData::CardType::Special_FLIP4:
		{
			price = 2000;
			break;
		}
		case CardData::CardType::Special_ADD:
		{
			price = 500;
			break;
		}
		case CardData::CardType::Special_AND:
		{
			price = 500;
			break;
		}
		case CardData::CardType::Special_ENV_BIN_STORM:
		{
			price = 500;
			break;
		}
		case CardData::CardType::Special_ENV_CLEAR:
		{
			price = 500;
			break;
		}
		case CardData::CardType::Special_ENV_DEC_STORM:
		{
			price = 500;
			break;
		}
		case CardData::CardType::Special_ENV_HEX_STORM:
		{
			price = 500;
			break;
		}
		case CardData::CardType::Special_INV:
		{
			price = 500;
			break;
		}
		case CardData::CardType::Special_OR:
		{
			price = 500;
			break;
		}
		case CardData::CardType::Special_SHL:
		{
			price = 500;
			break;
		}
		case CardData::CardType::Special_SHR:
		{
			price = 500;
			break;
		}
		case CardData::CardType::Special_SUB:
		{
			price = 500;
			break;
		}
		case CardData::CardType::Special_XOR:
		{
			price = 500;
			break;
		}
		default:
		{
			price = cardData->attack * cardData->attack * 10 + 6;
			break;
		}
	}

	Label* priceLabel = Label::create(std::to_string(price), Localization::getMainFont(), Localization::getFontSizeH3(Localization::getMainFont()));
	Sprite* goldIcon = Sprite::create(Resources::Menus_Objects_GOLD_1);

	goldIcon->setScale(0.75f);
	goldIcon->setPosition(Vec2(-32.0f, -144.0f));
	priceLabel->setAnchorPoint(Vec2(0.0f, 0.5f));
	priceLabel->setPosition(Vec2(16.0f, -144.0f));
	priceLabel->enableOutline(Color4B::BLACK, 4);

	switch (cardData->cardType)
	{
		case CardData::CardType::Binary:
		{
			card = Card::create(Card::CardStyle::Water, cardData);
			this->binaryCardsScrollPane->addChild(cardContainer);
			break;
		}
		case CardData::CardType::Decimal:
		{
			card = Card::create(Card::CardStyle::Air, cardData);
			this->decimalCardsScrollPane->addChild(cardContainer);
			break;
		}
		case CardData::CardType::Hexidecimal:
		{
			card = Card::create(Card::CardStyle::Earth, cardData);
			this->hexCardsScrollPane->addChild(cardContainer);
			break;
		}
		default:
		{
			card = Card::create(Card::CardStyle::Fire, cardData);
			this->specialCardsScrollPane->addChild(cardContainer);
			break;
		}
	}

	card->reveal();
	card->disableInteraction();
	card->setPosition(Vec2(0.0f, 16.0f));
	card->setScale(0.8f);

	cardContainer->setClickCallback(CC_CALLBACK_1(HexusShopMenu::onCardClick, this, cardData, price));

	cardContainer->addChild(card);
	cardContainer->addChild(goldIcon);
	cardContainer->addChild(priceLabel);

	return cardContainer;
}

void HexusShopMenu::onCardClick(MenuSprite* sprite, CardData* cardData, int price)
{
	int gold = CardStorage::getGold();

	if (gold < price)
	{
		SoundManager::playSoundResource(Resources::Sounds_AFX_INTERFACE_ERROR_1_DFMG);
		return;
	}

	gold -= price;
	SoundManager::playSoundResource(Resources::Sounds_Item_Purchase__1_);

	CardStorage::saveGold(gold);
	this->updateGoldText();

	CardStorage::addStorageCard(cardData);
}

void HexusShopMenu::onLootBoxClick(MenuSprite* sprite, int price)
{
	int gold = CardStorage::getGold();

	if (gold < price)
	{
		SoundManager::playSoundResource(Resources::Sounds_AFX_INTERFACE_ERROR_1_DFMG);
		return;
	}

	gold -= price;
	SoundManager::playSoundResource(Resources::Sounds_Item_Purchase__1_);

	CardStorage::saveGold(gold);
	this->updateGoldText();

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

void HexusShopMenu::onLootBoxTabClick()
{
	this->hideMenus();
	this->lootBoxButton->setZOrder(1);
	this->lootboxesNode->setVisible(true);
}

void HexusShopMenu::onBinaryTabClick()
{
	this->hideMenus();
	this->binaryButton->setZOrder(1);
	this->binaryCardsScrollPane->setVisible(true);
}

void HexusShopMenu::onDecimalTabClick()
{
	this->hideMenus();
	this->decimalButton->setZOrder(1);
	this->decimalCardsScrollPane->setVisible(true);
}

void HexusShopMenu::onHexTabClick()
{
	this->hideMenus();
	this->hexButton->setZOrder(1);
	this->hexCardsScrollPane->setVisible(true);
}

void HexusShopMenu::onSpecialTabClick()
{
	this->hideMenus();
	this->specialButton->setZOrder(1);
	this->specialCardsScrollPane->setVisible(true);
}

void HexusShopMenu::hideMenus()
{
	this->lootBoxButton->setZOrder(-1);
	this->storeMenu->setZOrder(0);
	this->binaryButton->setZOrder(-1);
	this->decimalButton->setZOrder(-1);
	this->hexButton->setZOrder(-1);
	this->specialButton->setZOrder(-1);

	this->lootboxesNode->setVisible(false);
	this->binaryCardsScrollPane->setVisible(false);
	this->decimalCardsScrollPane->setVisible(false);
	this->hexCardsScrollPane->setVisible(false);
	this->specialCardsScrollPane->setVisible(false);
}

void HexusShopMenu::updateGoldText()
{
	this->goldLabel->setString(std::to_string(CardStorage::getGold()));
}
