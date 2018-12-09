#include "HexusStoreMenu.h"

HexusStoreMenu* HexusStoreMenu::instance;
const float HexusStoreMenu::lootBoxScale = 0.5f;

void HexusStoreMenu::registerGlobalScene()
{
	if (HexusStoreMenu::instance == nullptr)
	{
		HexusStoreMenu::instance = new HexusStoreMenu();

		HexusStoreMenu::instance->autorelease();
		HexusStoreMenu::instance->initializeListeners();
	}

	GlobalDirector::registerGlobalScene(HexusStoreMenu::instance);
}

HexusStoreMenu::HexusStoreMenu()
{
	this->lootBoxes = std::vector<std::tuple<MenuSprite*, int>>();
	this->binaryCards = std::vector<std::tuple<MenuSprite*, MenuCard*, int>>();
	this->decimalCards = std::vector<std::tuple<MenuSprite*, MenuCard*, int>>();
	this->hexCards = std::vector<std::tuple<MenuSprite*, MenuCard*, int>>();
	this->specialCards = std::vector<std::tuple<MenuSprite*, MenuCard*, int>>();
	this->limitLabels = std::map<MenuCard*, Label*>();

	this->dustParticles = ParticleSystemQuad::create(ParticleResources::Dust);

	this->goldPanel = Sprite::create(UIResources::Menus_StoreMenu_GoldPanel);
	this->goldIcon = Sprite::create(UIResources::Menus_Objects_GOLD_2);
	this->goldLabel = Label::create("", Localization::getMainFont(), Localization::getFontSizeH2(Localization::getMainFont()));

	this->goldLabel->enableOutline(Color4B::BLACK, 3);
	this->goldLabel->setPosition(Vec2(-32.0f, 0.0f));
	this->goldLabel->setAlignment(TextHAlignment::LEFT);
	this->goldLabel->setAnchorPoint(Vec2(0.0f, 0.5f));

	this->storeBack = Sprite::create(UIResources::Menus_StoreMenu_StoreBack);
	this->shopKeeper = Shopkeeper::create();
	this->storeFront = Sprite::create(UIResources::Menus_StoreMenu_Store);
	this->storeNode = Node::create();
	this->lootboxesNode = Node::create();
	this->storeMenu = Sprite::create(UIResources::Menus_StoreMenu_StoreBoard);

	Label* backButtonLabel = Label::create("Back", Localization::getMainFont(), Localization::getFontSizeP(Localization::getMainFont()));
	Label* backButtonLabelHover = Label::create("Back", Localization::getMainFont(), Localization::getFontSizeP(Localization::getMainFont()));
	Label* backButtonLabelClick = Label::create("Back", Localization::getMainFont(), Localization::getFontSizeP(Localization::getMainFont()));

	backButtonLabel->enableOutline(Color4B::BLACK, 2);
	backButtonLabelHover->enableOutline(Color4B::BLACK, 2);
	backButtonLabelClick->enableOutline(Color4B::BLACK, 2);

	this->backButton = TextMenuSprite::create(
		backButtonLabel,
		backButtonLabelHover,
		UIResources::Menus_Buttons_GenericButton,
		UIResources::Menus_Buttons_GenericButtonHover
	);

	this->lootBoxRewardBackground = LayerColor::create(Color4B::BLACK);
	this->lootBoxRewardBackground->setOpacity(0);

	this->chosenCardsNode = Node::create();
	Label* lootBoxReturnLabel = Label::create("Return", Localization::getMainFont(), Localization::getFontSizeP(Localization::getMainFont()));
	Label* lootBoxReturnLabelSelected = Label::create("Return", Localization::getMainFont(), Localization::getFontSizeP(Localization::getMainFont()));
	Label* lootBoxReturnLabelClick = Label::create("Return", Localization::getMainFont(), Localization::getFontSizeP(Localization::getMainFont()));

	lootBoxReturnLabel->enableOutline(Color4B::BLACK, 2);
	lootBoxReturnLabelSelected->enableOutline(Color4B::BLACK, 2);
	lootBoxReturnLabelClick->enableOutline(Color4B::BLACK, 2);

	this->lootBoxReturnButton = TextMenuSprite::create(
		lootBoxReturnLabel,
		lootBoxReturnLabelSelected,
		UIResources::Menus_Buttons_WoodButton,
		UIResources::Menus_Buttons_WoodButtonSelected
	);

	this->lootBoxReturnButton->disableInteraction(0);

	this->lootBoxButton = MenuSprite::create(UIResources::Menus_StoreMenu_TabButton, UIResources::Menus_StoreMenu_TabButtonSelected);
	this->binaryButton = MenuSprite::create(UIResources::Menus_StoreMenu_TabButton, UIResources::Menus_StoreMenu_TabButtonSelected);
	this->decimalButton = MenuSprite::create(UIResources::Menus_StoreMenu_TabButton, UIResources::Menus_StoreMenu_TabButtonSelected);
	this->hexButton = MenuSprite::create(UIResources::Menus_StoreMenu_TabButton, UIResources::Menus_StoreMenu_TabButtonSelected);
	this->specialButton = MenuSprite::create(UIResources::Menus_StoreMenu_TabButton, UIResources::Menus_StoreMenu_TabButtonSelected);

	const Size scrollPaneSize = Size(840.0f, 720.0f);

	this->binaryCardsScrollPane = ScrollPane::create(scrollPaneSize, Color4B(0, 0, 0, 196));
	this->decimalCardsScrollPane = ScrollPane::create(scrollPaneSize, Color4B(0, 0, 0, 196));
	this->hexCardsScrollPane = ScrollPane::create(scrollPaneSize, Color4B(0, 0, 0, 196));
	this->specialCardsScrollPane = ScrollPane::create(scrollPaneSize, Color4B(0, 0, 0, 196));

	Sprite* lootBoxIcon = Sprite::create(UIResources::Menus_StoreMenu_IconLootBox);
	Sprite* binaryIcon = Sprite::create(UIResources::Menus_StoreMenu_IconBin);
	Sprite* decimalIcon = Sprite::create(UIResources::Menus_StoreMenu_IconDec);
	Sprite* hexIcon = Sprite::create(UIResources::Menus_StoreMenu_IconHex);
	Sprite* specialIcon = Sprite::create(UIResources::Menus_StoreMenu_IconSpecial);

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

	this->lootBoxes.push_back(this->constructLootBoxButton(UIResources::Menus_StoreMenu_LootBoxes_Jungle_Animations, 5, HexusStoreMenu::getCardsTier1()));
	this->lootBoxes.push_back(this->constructLootBoxButton(UIResources::Menus_StoreMenu_LootBoxes_Ruins_Animations, 200, HexusStoreMenu::getCardsTier2()));
	this->lootBoxes.push_back(this->constructLootBoxButton(UIResources::Menus_StoreMenu_LootBoxes_Forest_Animations, 800, HexusStoreMenu::getCardsTier3()));
	this->lootBoxes.push_back(this->constructLootBoxButton(UIResources::Menus_StoreMenu_LootBoxes_Caverns_Animations, 1500, HexusStoreMenu::getCardsTier4()));
	this->lootBoxes.push_back(this->constructLootBoxButton(UIResources::Menus_StoreMenu_LootBoxes_Castle_Animations, 2500, HexusStoreMenu::getCardsTier5()));
	this->lootBoxes.push_back(this->constructLootBoxButton(UIResources::Menus_StoreMenu_LootBoxes_Ice_Animations, 3200, HexusStoreMenu::getCardsTier6()));
	this->lootBoxes.push_back(this->constructLootBoxButton(UIResources::Menus_StoreMenu_LootBoxes_Volcano_Animations, 4000, HexusStoreMenu::getCardsTier7()));
	this->lootBoxes.push_back(this->constructLootBoxButton(UIResources::Menus_StoreMenu_LootBoxes_Obelisk_Animations, 5200, HexusStoreMenu::getCardsTier8()));
	this->lootBoxes.push_back(this->constructLootBoxButton(UIResources::Menus_StoreMenu_LootBoxes_Vapor_Animations, 6500, HexusStoreMenu::getCardsTier9()));

	for (auto it = CardList::getInstance()->cardListByName->begin(); it != CardList::getInstance()->cardListByName->end(); it++)
	{
		CardData* cardData = (*it).second;

		switch (cardData->cardType)
		{
			case CardData::Binary:
			{
				this->binaryCards.push_back(this->constructCard(cardData));
				break;
			}
			case CardData::Decimal:
			{
				this->decimalCards.push_back(this->constructCard(cardData));
				break;
			}
			case CardData::Hexidecimal:
			{
				this->hexCards.push_back(this->constructCard(cardData));
				break;
			}
			default:
			{
				this->specialCards.push_back(this->constructCard(cardData));
				break;
			}
		}
	}

	// Sort cards on price
	std::sort(this->binaryCards.begin(), this->binaryCards.end(), [](std::tuple<MenuSprite*, MenuCard*, int> a, std::tuple<MenuSprite*, MenuCard*, int> b) -> bool
	{
		return std::get<2>(a) < std::get<2>(b);
	});

	std::sort(this->decimalCards.begin(), this->decimalCards.end(), [](std::tuple<MenuSprite*, MenuCard*, int> a, std::tuple<MenuSprite*, MenuCard*, int> b) -> bool
	{
		return std::get<2>(a) < std::get<2>(b);
	});

	std::sort(this->hexCards.begin(), this->hexCards.end(), [](std::tuple<MenuSprite*, MenuCard*, int> a, std::tuple<MenuSprite*, MenuCard*, int> b) -> bool
	{
		return std::get<2>(a) < std::get<2>(b);
	});

	std::sort(this->specialCards.begin(), this->specialCards.end(), [](std::tuple<MenuSprite*, MenuCard*, int> a, std::tuple<MenuSprite*, MenuCard*, int> b) -> bool
	{
		return std::get<2>(a) < std::get<2>(b);
	});

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
	this->addChild(this->backButton);
	this->addChild(this->lootBoxRewardBackground);
	this->addChild(this->chosenCardsNode);
	this->addChild(this->lootBoxReturnButton);

	for (auto it = this->lootBoxes.begin(); it != this->lootBoxes.end(); it++)
	{
		this->lootboxesNode->addChild(std::get<0>(*it));
	}

	for (auto it = this->binaryCards.begin(); it != this->binaryCards.end(); it++)
	{
		this->binaryCardsScrollPane->addChild(std::get<0>(*it));
	}

	for (auto it = this->decimalCards.begin(); it != this->decimalCards.end(); it++)
	{
		this->decimalCardsScrollPane->addChild(std::get<0>(*it));
	}

	for (auto it = this->hexCards.begin(); it != this->hexCards.end(); it++)
	{
		this->hexCardsScrollPane->addChild(std::get<0>(*it));
	}

	for (auto it = this->specialCards.begin(); it != this->specialCards.end(); it++)
	{
		this->specialCardsScrollPane->addChild(std::get<0>(*it));
	}

	this->addChild(Mouse::create());

	this->onLootBoxTabClick();
}

HexusStoreMenu::~HexusStoreMenu()
{
}

void HexusStoreMenu::onEnter()
{
	GlobalScene::onEnter();

	const float delay = 0.25f;
	const float duration = 0.35f;

	GameUtils::fadeInObject(this->backButton, delay, duration);

	GameUtils::accelerateParticles(this->dustParticles, 5.0f);

	this->updateGoldText();
}

void HexusStoreMenu::initializeListeners()
{
	GlobalScene::initializeListeners();

	HexusStoreMenu::instance->addGlobalEventListener(EventListenerCustom::create(NavigationEvents::EventNavigateHexusShop, [](EventCustom* args)
	{
		GlobalDirector::loadScene(HexusStoreMenu::instance);
	}));

	EventListenerKeyboard* keyboardListener = EventListenerKeyboard::create();

	keyboardListener->onKeyPressed = CC_CALLBACK_2(HexusStoreMenu::onKeyPressed, this);

	this->addEventListener(keyboardListener);

	this->lootBoxButton->setClickCallback(CC_CALLBACK_0(HexusStoreMenu::onLootBoxTabClick, this));
	this->binaryButton->setClickCallback(CC_CALLBACK_0(HexusStoreMenu::onBinaryTabClick, this));
	this->decimalButton->setClickCallback(CC_CALLBACK_0(HexusStoreMenu::onDecimalTabClick, this));
	this->hexButton->setClickCallback(CC_CALLBACK_0(HexusStoreMenu::onHexTabClick, this));
	this->specialButton->setClickCallback(CC_CALLBACK_0(HexusStoreMenu::onSpecialTabClick, this));

	this->backButton->setClickCallback(CC_CALLBACK_1(HexusStoreMenu::onBackClick, this));
}

void HexusStoreMenu::initializePositions()
{
	GlobalScene::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	const float storeOffsetY = -128.0f;
	const Vec2 storeMenuOffset = Vec2(352.0f, 0.0f);
	const Vec2 storeContentOffset = Vec2(0.0f, -64.0f);
	const Vec2 goldPanelOffset = Vec2(412.0f, 464.0f);

	this->dustParticles->setPosition(Vec2(visibleSize.width, visibleSize.height / 2));
	this->storeBack->setPosition(Vec2(0.0f, visibleSize.height / 2.0f + storeOffsetY + 144.0f));
	this->shopKeeper->setPosition(Vec2(visibleSize.width / 2.0f - 680.0f, visibleSize.height / 2.0f + storeOffsetY));
	this->storeFront->setPosition(Vec2(0.0f, visibleSize.height / 2.0f + storeOffsetY - 176.0f));
	this->storeMenu->setPosition(Vec2(visibleSize.width / 2.0f + storeMenuOffset.x, visibleSize.height / 2.0f + storeMenuOffset.y - 48.0f));

	this->goldPanel->setPosition(Vec2(visibleSize.width / 2.0f + storeMenuOffset.x + goldPanelOffset.x, visibleSize.height / 2.0f + storeMenuOffset.y + goldPanelOffset.y));
	this->goldIcon->setPosition(Vec2(visibleSize.width / 2.0f + storeMenuOffset.x + goldPanelOffset.x - 80.0f, visibleSize.height / 2.0f + storeMenuOffset.y + goldPanelOffset.y));
	this->goldLabel->setPosition(Vec2(visibleSize.width / 2.0f + storeMenuOffset.x + goldPanelOffset.x - 8.0f, visibleSize.height / 2.0f + storeMenuOffset.y + goldPanelOffset.y));

	this->backButton->setPosition(Vec2(visibleSize.width / 2.0f - 756.0f, visibleSize.height - 64.0f));

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
	this->lootBoxReturnButton->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));

	const Size chestGridSize = Size(288.0f, 240.0f);
	int index = 0;

	for (auto it = this->lootBoxes.begin(); it != this->lootBoxes.end(); it++)
	{
		int x = index % 3 - 1;
		int y = index / 3 - 1;

		std::get<0>(*it)->setPosition(Vec2(x * chestGridSize.width, - 32.0f - y * chestGridSize.height));

		index++;
	}

	const Size cardGridSize = Size(256.0f, 384.0f);

	index = 0;

	for (auto it = this->binaryCards.begin(); it != this->binaryCards.end(); it++)
	{
		int x = index % 3 - 1;
		int y = (this->binaryCards.size() - 1 - index + (3 - this->binaryCards.size() % 3)) / 3 - (this->binaryCards.size() % 3 == 0 ? 1 : 0);

		std::get<0>(*it)->setPosition(Vec2(x * cardGridSize.width + this->binaryCardsScrollPane->getPaneSize().width / 2.0f, 128.0f + y * cardGridSize.height));

		index++;
	}

	index = 0;

	for (auto it = this->decimalCards.begin(); it != this->decimalCards.end(); it++)
	{
		int x = index % 3 - 1;
		int y = (this->decimalCards.size() - 1 - index + (3 - this->decimalCards.size() % 3)) / 3 - (this->decimalCards.size() % 3 == 0 ? 1 : 0);

		std::get<0>((*it))->setPosition(Vec2(x * cardGridSize.width + this->decimalCardsScrollPane->getPaneSize().width / 2.0f, 128.0f + y * cardGridSize.height));

		index++;
	}

	index = 0;

	for (auto it = this->hexCards.begin(); it != this->hexCards.end(); it++)
	{
		int x = index % 3 - 1;
		int y = (this->hexCards.size() - 1 - index + (3 - this->hexCards.size() % 3)) / 3 - (this->hexCards.size() % 3 == 0 ? 1 : 0);

		std::get<0>(*it)->setPosition(Vec2(x * cardGridSize.width + this->hexCardsScrollPane->getPaneSize().width / 2.0f, 128.0f + y * cardGridSize.height));

		index++;
	}

	index = 0;

	for (auto it = this->specialCards.begin(); it != this->specialCards.end(); it++)
	{
		int x = index % 3 - 1;
		int y = (this->specialCards.size() - 1 - index + (3 - this->specialCards.size() % 3)) / 3 - (this->specialCards.size() % 3 == 0 ? 1 : 0);

		std::get<0>(*it)->setPosition(Vec2(x * cardGridSize.width + this->specialCardsScrollPane->getPaneSize().width / 2.0f, 128.0f + y * cardGridSize.height));

		index++;
	}

	binaryCardsScrollPane->fitSizeToContent(Rect(0.0f, 64.0f, 0.0f, 0.0f));
	decimalCardsScrollPane->fitSizeToContent(Rect(0.0f, 64.0f, 0.0f, 0.0f));
	hexCardsScrollPane->fitSizeToContent(Rect(0.0f, 64.0f, 0.0f, 0.0f));
	specialCardsScrollPane->fitSizeToContent(Rect(0.0f, 64.0f, 0.0f, 0.0f));
}

std::tuple<MenuSprite*, int> HexusStoreMenu::constructLootBoxButton(std::string lootBoxAnimations, int price, std::map<CardData*, float> cardChoices)
{
	AnimationNode* animationNode = AnimationNode::create(lootBoxAnimations);

	SpriterEngine::EntityInstance* entity = animationNode->play("Entity");
	entity->setCurrentAnimation("Idle");

	MenuSprite* frame = MenuSprite::create(UIResources::Menus_StoreMenu_StoreOption, UIResources::Menus_StoreMenu_StoreOptionSelected);
	Label* priceLabel = Label::create(std::to_string(price), Localization::getMainFont(), Localization::getFontSizeH3(Localization::getMainFont()));
	Sprite* goldIcon = Sprite::create(UIResources::Menus_Objects_GOLD_1);

	animationNode->setScale(HexusStoreMenu::lootBoxScale);
	animationNode->setPosition(Vec2(0.0f, 16.0f));

	frame->setClickCallback(CC_CALLBACK_1(HexusStoreMenu::onLootBoxClick, this, price, cardChoices, animationNode, entity));
	goldIcon->setScale(0.75f);
	goldIcon->setPosition(Vec2(-32.0f, -72.0f));
	priceLabel->setAnchorPoint(Vec2(0.0f, 0.5f));
	priceLabel->setPosition(Vec2(16.0f, -72.0f));
	priceLabel->enableOutline(Color4B::BLACK, 4);

	frame->addChild(animationNode);
	frame->addChild(goldIcon);
	frame->addChild(priceLabel);

	return std::tuple<MenuSprite*, int>(frame, price);
}

std::tuple<MenuSprite*, MenuCard*, int> HexusStoreMenu::constructCard(CardData* cardData)
{
	MenuSprite* cardContainer =  MenuSprite::create(UIResources::Menus_StoreMenu_CardPanel, UIResources::Menus_StoreMenu_CardPanelSelected);
	MenuCard* menuCard = MenuCard::create(Card::CardStyle::Earth, cardData);
	int price = 0;

	switch (cardData->cardType)
	{
		case CardData::CardType::Special_FLIP1:
		{
			price = 50;
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
			price = 1800;
			break;
		}
		case CardData::CardType::Special_ADD:
		{
			price = 335;
			break;
		}
		case CardData::CardType::Special_SUB:
		{
			price = 335;
			break;
		}
		case CardData::CardType::Special_MOV:
		{
			price = 280;
			break;
		}
		case CardData::CardType::Special_AND:
		{
			price = 640;
			break;
		}
		case CardData::CardType::Special_OR:
		{
			price = 640;
			break;
		}
		case CardData::CardType::Special_XOR:
		{
			price = 640;
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
			price = 2500;
			break;
		}
		case CardData::CardType::Special_SHL:
		{
			price = 750;
			break;
		}
		case CardData::CardType::Special_SHR:
		{
			price = 250;
			break;
		}
		default:
		{
			price = cardData->attack * cardData->attack * 10 + 6;
			break;
		}
	}

	Label* cardLimitLabel = Label::create("", Localization::getMainFont(), 48.0f);

	cardLimitLabel->setAnchorPoint(Vec2(0.0f, 0.5f));
	cardLimitLabel->enableOutline(Color4B::BLACK, 4);
	cardLimitLabel->setPosition(Vec2(-96.0f, 128.0f));

	this->updateCardLimitText(cardLimitLabel, cardData);

	Label* priceLabel = Label::create(std::to_string(price), Localization::getMainFont(), Localization::getFontSizeH3(Localization::getMainFont()));
	Sprite* goldIcon = Sprite::create(UIResources::Menus_Objects_GOLD_1);

	goldIcon->setScale(0.75f);
	goldIcon->setPosition(Vec2(-32.0f, -144.0f));
	priceLabel->setAnchorPoint(Vec2(0.0f, 0.5f));
	priceLabel->setPosition(Vec2(16.0f, -144.0f));
	priceLabel->enableOutline(Color4B::BLACK, 4);

	cardContainer->addChild(menuCard);

	menuCard->reveal();
	menuCard->disableInteraction();
	menuCard->setPosition(Vec2(0.0f, 16.0f));
	menuCard->setScale(0.8f);

	cardContainer->setClickCallback(CC_CALLBACK_1(HexusStoreMenu::onCardClick, this, cardData, price, cardLimitLabel));

	cardContainer->addChild(goldIcon);
	cardContainer->addChild(priceLabel);
	menuCard->addDisplayItem(cardLimitLabel);

	this->limitLabels.emplace(menuCard, cardLimitLabel);

	return std::tuple<MenuSprite*, MenuCard*, int>(cardContainer, menuCard, price);
}

void HexusStoreMenu::updateAllCardLimits()
{
	for (auto it = this->binaryCards.begin(); it != this->binaryCards.end(); it++)
	{
		this->updateCardLimitText(this->limitLabels[std::get<1>(*it)], std::get<1>(*it)->cardData);
	}

	for (auto it = this->decimalCards.begin(); it != this->decimalCards.end(); it++)
	{
		this->updateCardLimitText(this->limitLabels[std::get<1>(*it)], std::get<1>(*it)->cardData);
	}

	for (auto it = this->hexCards.begin(); it != this->hexCards.end(); it++)
	{
		this->updateCardLimitText(this->limitLabels[std::get<1>(*it)], std::get<1>(*it)->cardData);
	}
}

void HexusStoreMenu::updateCardLimitText(Label* label, CardData* cardData)
{
	int ownedCount = CardStorage::getOwnedCardCount(cardData);

	label->setString(std::to_string(ownedCount) + " / " + std::to_string(3));

	if (ownedCount >= 3)
	{
		label->setTextColor(Color4B::GREEN);
	}
	else
	{
		label->setTextColor(Color4B::WHITE);
	}
}

void HexusStoreMenu::onCardClick(MenuSprite* card, CardData* cardData, int price, Label* cardLimitLabel)
{
	int gold = CardStorage::getGold();

	if (gold < price || CardStorage::getOwnedCardCount(cardData) >= 3)
	{
		SoundManager::playSoundResource(SoundResources::AFX_INTERFACE_ERROR_1_DFMG);
		return;
	}

	gold -= price;
	SoundManager::playSoundResource(SoundResources::Item_Purchase__1_);

	CardStorage::saveGold(gold);
	this->updateGoldText();

	CardStorage::addStorageCard(cardData);

	this->updateCardLimitText(cardLimitLabel, cardData);
}

void HexusStoreMenu::onLootBoxClick(MenuSprite* sprite, int price, std::map<CardData*, float> cardChoices, AnimationNode* animationNode, SpriterEngine::EntityInstance* entity)
{
	int gold = CardStorage::getGold();

	if (gold < price)
	{
		SoundManager::playSoundResource(SoundResources::AFX_INTERFACE_ERROR_1_DFMG);
		return;
	}

	gold -= price;
	SoundManager::playSoundResource(SoundResources::Item_Purchase__1_);

	CardStorage::saveGold(gold);
	this->updateGoldText();

	std::vector<Card*> chosenCards = std::vector<Card*>
	{
		Card::create(Card::CardStyle::Earth, HexusStoreMenu::chooseRandomCard(cardChoices)),
		Card::create(Card::CardStyle::Earth, HexusStoreMenu::chooseRandomCard(cardChoices)),
		Card::create(Card::CardStyle::Earth, HexusStoreMenu::chooseRandomCard(cardChoices)),
	};

	Size visibleSize = Director::getInstance()->getVisibleSize();

	int index = 0;

	for (auto it = chosenCards.begin(); it != chosenCards.end(); it++)
	{
		float radians = (index * 360.0f / chosenCards.size() + 90.0f) * M_PI / 180.0f;

		(*it)->setScale(1.0f);
		(*it)->reveal();
		(*it)->disableInteraction();
		(*it)->setOpacity(0);
		(*it)->setPosition(Vec2(visibleSize.width / 2.0f + std::cos(radians) * 320.0f, visibleSize.height / 2.0f + std::sin(radians) * 320.0f));

		this->chosenCardsNode->addChild((*it));
		index++;

		// Save the card
		CardStorage::addStorageCard((*it)->cardData);
	}

	this->updateAllCardLimits();

	animationNode->runAction(Sequence::create(
		CallFunc::create([=]()
		{
			this->lootBoxReturnButton->setClickCallback(nullptr);

			for (auto it = this->lootBoxes.begin(); it != this->lootBoxes.end(); it++)
			{
				std::get<0>(*it)->disableInteraction();
			}

			this->backButton->disableInteraction();
			this->lootBoxButton->disableInteraction();
			this->binaryButton->disableInteraction();
			this->decimalButton->disableInteraction();
			this->hexButton->disableInteraction();
			this->specialButton->disableInteraction();

			entity->setCurrentTime(0.0f);
			entity->setCurrentAnimation("Open", 0.25f);
		}),
		DelayTime::create(1.5f),
		CallFunc::create([=]()
		{
			this->lootBoxRewardBackground->runAction(FadeTo::create(0.5f, 196));

			for (auto it = chosenCards.begin(); it != chosenCards.end(); it++)
			{
				(*it)->runAction(FadeIn::create(0.5f));
			}

			this->lootBoxReturnButton->runAction(Sequence::create(
				FadeIn::create(0.5f),
				CallFunc::create([=]()
				{
					this->lootBoxReturnButton->setClickCallback(CC_CALLBACK_0(HexusStoreMenu::onLootBoxReturnButtonClick, this, price, chosenCards));
					this->lootBoxReturnButton->enableInteraction();
				}),
				nullptr
			));

			entity->setCurrentTime(0.0f);
			entity->setCurrentAnimation("Idle", 0.25f);
		}),
		nullptr
	));
}

void HexusStoreMenu::onLootBoxReturnButtonClick(int price, std::vector<Card*> chosenCards)
{
	int gold = CardStorage::getGold();

	this->runAction(Sequence::create(
		CallFunc::create([=]()
		{
			this->lootBoxRewardBackground->runAction(FadeTo::create(0.25f, 0));

			this->lootBoxReturnButton->disableInteraction(255);
			this->lootBoxReturnButton->runAction(FadeOut::create(0.25f));

			for (auto it = chosenCards.begin(); it != chosenCards.end(); it++)
			{
				Card* card = *it;

				card->runAction(Sequence::create(
					FadeOut::create(0.25f),
					DelayTime::create(0.25f),
					CallFunc::create([=]()
					{
						this->chosenCardsNode->removeChild(card);
					}),
					nullptr
				));
			}
		}),
		DelayTime::create(0.25f),
		CallFunc::create([=]()
		{
			for (auto it = this->lootBoxes.begin(); it != this->lootBoxes.end(); it++)
			{
				std::get<0>(*it)->enableInteraction();
			}

			this->backButton->enableInteraction();
			this->lootBoxButton->enableInteraction();
			this->binaryButton->enableInteraction();
			this->decimalButton->enableInteraction();
			this->hexButton->enableInteraction();
			this->specialButton->enableInteraction();
		}),
		nullptr
	));
}

void HexusStoreMenu::onBackClick(MenuSprite* menuSprite)
{
	NavigationEvents::navigateBack();
}

void HexusStoreMenu::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (!GameUtils::isVisible(this))
	{
		return;
	}

	switch (keyCode)
	{
		case EventKeyboard::KeyCode::KEY_ESCAPE:
		{
			event->stopPropagation();
			NavigationEvents::navigateBack();
			break;
		}
		default:
		{
			break;
		}
	}
}

void HexusStoreMenu::onLootBoxTabClick()
{
	this->hideMenus();
	this->lootBoxButton->setZOrder(1);
	this->lootboxesNode->setVisible(true);
}

void HexusStoreMenu::onBinaryTabClick()
{
	this->hideMenus();
	this->binaryButton->setZOrder(1);
	this->binaryCardsScrollPane->setVisible(true);
}

void HexusStoreMenu::onDecimalTabClick()
{
	this->hideMenus();
	this->decimalButton->setZOrder(1);
	this->decimalCardsScrollPane->setVisible(true);
}

void HexusStoreMenu::onHexTabClick()
{
	this->hideMenus();
	this->hexButton->setZOrder(1);
	this->hexCardsScrollPane->setVisible(true);
}

void HexusStoreMenu::onSpecialTabClick()
{
	this->hideMenus();
	this->specialButton->setZOrder(1);
	this->specialCardsScrollPane->setVisible(true);
}

void HexusStoreMenu::hideMenus()
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

void HexusStoreMenu::updateGoldText()
{
	this->goldLabel->setString(std::to_string(CardStorage::getGold()));
}

CardData* HexusStoreMenu::chooseRandomCard(std::map<CardData*, float> cardChoices)
{
	float totalChance = 0.0f;

	for (auto it = cardChoices.begin(); it != cardChoices.end(); it++)
	{
		totalChance += (*it).second;
	}

	float selection = RandomHelper::random_real(0.0f, totalChance);
	float sum = 0.0f;

	for (auto it = cardChoices.begin(); it != cardChoices.end(); it++)
	{
		sum += (*it).second;

		if (selection <= sum)
		{
			return (*it).first;
		}
	}

	// Just some non-null default (should not be possible)
	return CardList::getInstance()->cardListByName->at(CardKeys::Binary0);
}

std::map<CardData*, float> HexusStoreMenu::getCardsTier1()
{
	return std::map<CardData*, float>
	{
		{ CardList::getInstance()->cardListByName->at(CardKeys::Decimal0), 0.75f },
		{ CardList::getInstance()->cardListByName->at(CardKeys::Decimal1), 1.0f },
		{ CardList::getInstance()->cardListByName->at(CardKeys::Decimal2), 1.0f },
		{ CardList::getInstance()->cardListByName->at(CardKeys::Hex0), 0.75f },
		{ CardList::getInstance()->cardListByName->at(CardKeys::Hex1), 1.0f },
		{ CardList::getInstance()->cardListByName->at(CardKeys::Hex2), 1.0f },
		{ CardList::getInstance()->cardListByName->at(CardKeys::Binary0), 0.75f },
		{ CardList::getInstance()->cardListByName->at(CardKeys::Binary1), 1.0f },
		{ CardList::getInstance()->cardListByName->at(CardKeys::Binary2), 1.0f },
	};
}

std::map<CardData*, float> HexusStoreMenu::getCardsTier2()
{
	return std::map<CardData*, float>
	{
		{ CardList::getInstance()->cardListByName->at(CardKeys::Decimal2), 0.75f },
		{ CardList::getInstance()->cardListByName->at(CardKeys::Decimal3), 1.0f },
		{ CardList::getInstance()->cardListByName->at(CardKeys::Decimal4), 1.0f },
		{ CardList::getInstance()->cardListByName->at(CardKeys::Hex2), 0.75f },
		{ CardList::getInstance()->cardListByName->at(CardKeys::Hex3), 1.0f },
		{ CardList::getInstance()->cardListByName->at(CardKeys::Hex4), 1.0f },
		{ CardList::getInstance()->cardListByName->at(CardKeys::Binary2), 0.75f },
		{ CardList::getInstance()->cardListByName->at(CardKeys::Binary3), 1.0f },
		{ CardList::getInstance()->cardListByName->at(CardKeys::Binary4), 1.0f },
	};
}

std::map<CardData*, float> HexusStoreMenu::getCardsTier3()
{
	return std::map<CardData*, float>
	{
		{ CardList::getInstance()->cardListByName->at(CardKeys::Decimal4), 0.75f },
		{ CardList::getInstance()->cardListByName->at(CardKeys::Decimal5), 1.0f },
		{ CardList::getInstance()->cardListByName->at(CardKeys::Decimal6), 1.0f },
		{ CardList::getInstance()->cardListByName->at(CardKeys::Hex4), 0.75f },
		{ CardList::getInstance()->cardListByName->at(CardKeys::Hex5), 1.0f },
		{ CardList::getInstance()->cardListByName->at(CardKeys::Hex6), 1.0f },
		{ CardList::getInstance()->cardListByName->at(CardKeys::Binary4), 0.75f },
		{ CardList::getInstance()->cardListByName->at(CardKeys::Binary5), 1.0f },
		{ CardList::getInstance()->cardListByName->at(CardKeys::Binary6), 1.0f },
	};
}

std::map<CardData*, float> HexusStoreMenu::getCardsTier4()
{
	return std::map<CardData*, float>
	{
		{ CardList::getInstance()->cardListByName->at(CardKeys::Decimal5), 0.75f },
		{ CardList::getInstance()->cardListByName->at(CardKeys::Decimal6), 1.0f },
		{ CardList::getInstance()->cardListByName->at(CardKeys::Decimal7), 1.0f },
		{ CardList::getInstance()->cardListByName->at(CardKeys::Hex5), 0.75f },
		{ CardList::getInstance()->cardListByName->at(CardKeys::Hex6), 1.0f },
		{ CardList::getInstance()->cardListByName->at(CardKeys::Hex7), 1.0f },
		{ CardList::getInstance()->cardListByName->at(CardKeys::Binary5), 0.75f },
		{ CardList::getInstance()->cardListByName->at(CardKeys::Binary6), 1.0f },
		{ CardList::getInstance()->cardListByName->at(CardKeys::Binary7), 1.0f },
	};
}

std::map<CardData*, float> HexusStoreMenu::getCardsTier5()
{
	return std::map<CardData*, float>
	{
		{ CardList::getInstance()->cardListByName->at(CardKeys::Decimal7), 0.75f },
		{ CardList::getInstance()->cardListByName->at(CardKeys::Decimal8), 1.0f },
		{ CardList::getInstance()->cardListByName->at(CardKeys::Decimal9), 1.0f },
		{ CardList::getInstance()->cardListByName->at(CardKeys::Hex7), 0.75f },
		{ CardList::getInstance()->cardListByName->at(CardKeys::Hex8), 1.0f },
		{ CardList::getInstance()->cardListByName->at(CardKeys::Hex9), 1.0f },
		{ CardList::getInstance()->cardListByName->at(CardKeys::Binary7), 0.75f },
		{ CardList::getInstance()->cardListByName->at(CardKeys::Binary8), 1.0f },
		{ CardList::getInstance()->cardListByName->at(CardKeys::Binary9), 1.0f },
	};
}

std::map<CardData*, float> HexusStoreMenu::getCardsTier6()
{
	return std::map<CardData*, float>
	{
		{ CardList::getInstance()->cardListByName->at(CardKeys::Decimal9), 0.75f },
		{ CardList::getInstance()->cardListByName->at(CardKeys::Decimal10), 1.0f },
		{ CardList::getInstance()->cardListByName->at(CardKeys::Decimal11), 1.0f },
		{ CardList::getInstance()->cardListByName->at(CardKeys::Hex9), 0.75f },
		{ CardList::getInstance()->cardListByName->at(CardKeys::Hex10), 1.0f },
		{ CardList::getInstance()->cardListByName->at(CardKeys::Hex11), 1.0f },
		{ CardList::getInstance()->cardListByName->at(CardKeys::Binary9), 0.75f },
		{ CardList::getInstance()->cardListByName->at(CardKeys::Binary10), 1.0f },
		{ CardList::getInstance()->cardListByName->at(CardKeys::Binary11), 1.0f },
	};
}

std::map<CardData*, float> HexusStoreMenu::getCardsTier7()
{
	return std::map<CardData*, float>
	{
		{ CardList::getInstance()->cardListByName->at(CardKeys::Decimal10), 0.75f },
		{ CardList::getInstance()->cardListByName->at(CardKeys::Decimal11), 1.0f },
		{ CardList::getInstance()->cardListByName->at(CardKeys::Decimal12), 1.0f },
		{ CardList::getInstance()->cardListByName->at(CardKeys::Hex10), 0.75f },
		{ CardList::getInstance()->cardListByName->at(CardKeys::Hex11), 1.0f },
		{ CardList::getInstance()->cardListByName->at(CardKeys::Hex12), 1.0f },
		{ CardList::getInstance()->cardListByName->at(CardKeys::Binary10), 0.75f },
		{ CardList::getInstance()->cardListByName->at(CardKeys::Binary11), 1.0f },
		{ CardList::getInstance()->cardListByName->at(CardKeys::Binary12), 1.0f },
	};
}

std::map<CardData*, float> HexusStoreMenu::getCardsTier8()
{
	return std::map<CardData*, float>
	{
		{ CardList::getInstance()->cardListByName->at(CardKeys::Decimal12), 0.75f },
		{ CardList::getInstance()->cardListByName->at(CardKeys::Decimal13), 1.0f },
		{ CardList::getInstance()->cardListByName->at(CardKeys::Decimal14), 1.0f },
		{ CardList::getInstance()->cardListByName->at(CardKeys::Hex12), 0.75f },
		{ CardList::getInstance()->cardListByName->at(CardKeys::Hex13), 1.0f },
		{ CardList::getInstance()->cardListByName->at(CardKeys::Hex14), 1.0f },
		{ CardList::getInstance()->cardListByName->at(CardKeys::Binary12), 0.75f },
		{ CardList::getInstance()->cardListByName->at(CardKeys::Binary13), 1.0f },
		{ CardList::getInstance()->cardListByName->at(CardKeys::Binary14), 1.0f },
	};
}

std::map<CardData*, float> HexusStoreMenu::getCardsTier9()
{
	return std::map<CardData*, float>
	{
		{ CardList::getInstance()->cardListByName->at(CardKeys::Decimal13), 0.75f },
		{ CardList::getInstance()->cardListByName->at(CardKeys::Decimal14), 1.0f },
		{ CardList::getInstance()->cardListByName->at(CardKeys::Decimal15), 1.0f },
		{ CardList::getInstance()->cardListByName->at(CardKeys::Hex13), 0.75f },
		{ CardList::getInstance()->cardListByName->at(CardKeys::Hex14), 1.0f },
		{ CardList::getInstance()->cardListByName->at(CardKeys::Hex15), 1.0f },
		{ CardList::getInstance()->cardListByName->at(CardKeys::Binary13), 0.75f },
		{ CardList::getInstance()->cardListByName->at(CardKeys::Binary14), 1.0f },
		{ CardList::getInstance()->cardListByName->at(CardKeys::Binary15), 1.0f },
	};
}

