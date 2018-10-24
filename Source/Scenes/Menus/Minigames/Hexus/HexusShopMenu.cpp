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

	this->lootBoxRewardBackground = LayerColor::create(Color4B::BLACK);
	this->lootBoxRewardBackground->setOpacity(0);

	this->chosenCardsNode = Node::create();
	Label* lootBoxReturnLabel = Label::create("Return", Localization::getMainFont(), Localization::getFontSizeH2(Localization::getMainFont()));
	Label* lootBoxReturnLabelSelected = Label::create("Return", Localization::getMainFont(), Localization::getFontSizeH2(Localization::getMainFont()));
	Label* lootBoxReturnLabelClick = Label::create("Return", Localization::getMainFont(), Localization::getFontSizeH2(Localization::getMainFont()));

	lootBoxReturnLabel->enableOutline(Color4B::BLACK, 2);
	lootBoxReturnLabelSelected->enableOutline(Color4B::BLACK, 2);
	lootBoxReturnLabelClick->enableOutline(Color4B::BLACK, 2);

	lootBoxReturnLabelSelected->setColor(Color3B::YELLOW);
	lootBoxReturnLabelClick->setColor(Color3B::YELLOW);

	this->lootBoxReturnButton = TextMenuSprite::create(
		lootBoxReturnLabel,
		lootBoxReturnLabelSelected,
		lootBoxReturnLabelClick,
		Resources::Minigames_Hexus_ButtonPlank,
		Resources::Minigames_Hexus_ButtonPlankHover,
		Resources::Minigames_Hexus_ButtonPlankClick
	);

	this->lootBoxReturnButton->disableInteraction(0);

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

	this->lootBoxes.push_back(this->constructLootBoxButton(Resources::Menus_StoreMenu_LootBoxes_Jungle_Animations, 5, HexusShopMenu::getCardsTier1()));
	this->lootBoxes.push_back(this->constructLootBoxButton(Resources::Menus_StoreMenu_LootBoxes_Ruins_Animations, 10, HexusShopMenu::getCardsTier2()));
	this->lootBoxes.push_back(this->constructLootBoxButton(Resources::Menus_StoreMenu_LootBoxes_Forest_Animations, 25, HexusShopMenu::getCardsTier3()));
	this->lootBoxes.push_back(this->constructLootBoxButton(Resources::Menus_StoreMenu_LootBoxes_Caverns_Animations, 50, HexusShopMenu::getCardsTier4()));
	this->lootBoxes.push_back(this->constructLootBoxButton(Resources::Menus_StoreMenu_LootBoxes_Castle_Animations, 100, HexusShopMenu::getCardsTier5()));
	this->lootBoxes.push_back(this->constructLootBoxButton(Resources::Menus_StoreMenu_LootBoxes_Ice_Animations, 250, HexusShopMenu::getCardsTier6()));
	this->lootBoxes.push_back(this->constructLootBoxButton(Resources::Menus_StoreMenu_LootBoxes_Volcano_Animations, 500, HexusShopMenu::getCardsTier7()));
	this->lootBoxes.push_back(this->constructLootBoxButton(Resources::Menus_StoreMenu_LootBoxes_Obelisk_Animations, 1000, HexusShopMenu::getCardsTier8()));
	this->lootBoxes.push_back(this->constructLootBoxButton(Resources::Menus_StoreMenu_LootBoxes_Vapor_Animations, 1500, HexusShopMenu::getCardsTier9()));

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
	this->addChild(this->lootBoxRewardBackground);
	this->addChild(this->chosenCardsNode);
	this->addChild(this->lootBoxReturnButton);

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
	this->lootBoxReturnButton->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));

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

MenuSprite* HexusShopMenu::constructLootBoxButton(std::string lootBoxAnimations, int price, std::map<CardData*, float> cardChoices)
{
	AnimationNode* animationNode = AnimationNode::create(lootBoxAnimations);

	SpriterEngine::EntityInstance* entity = animationNode->play("Entity");
	entity->setCurrentAnimation("Idle");

	MenuSprite* frame = MenuSprite::create(Resources::Menus_StoreMenu_StoreOption, Resources::Menus_StoreMenu_StoreOptionSelected, Resources::Menus_StoreMenu_StoreOptionSelected);
	Label* priceLabel = Label::create(std::to_string(price), Localization::getMainFont(), Localization::getFontSizeH3(Localization::getMainFont()));
	Sprite* goldIcon = Sprite::create(Resources::Menus_Objects_GOLD_1);

	animationNode->setScale(HexusShopMenu::lootBoxScale);
	animationNode->setPosition(Vec2(0.0f, 16.0f));

	frame->setClickCallback(CC_CALLBACK_1(HexusShopMenu::onLootBoxClick, this, price, cardChoices, animationNode, entity));
	goldIcon->setScale(0.75f);
	goldIcon->setPosition(Vec2(-32.0f, -72.0f));
	priceLabel->setAnchorPoint(Vec2(0.0f, 0.5f));
	priceLabel->setPosition(Vec2(16.0f, -72.0f));
	priceLabel->enableOutline(Color4B::BLACK, 4);

	frame->addChild(animationNode);
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

	Label* cardLimitLabel = Label::create("", Localization::getMainFont(), Localization::getFontSizeH2(Localization::getMainFont()));

	cardLimitLabel->setAnchorPoint(Vec2(0.0f, 0.5f));
	cardLimitLabel->enableOutline(Color4B::BLACK, 4);
	cardLimitLabel->setPosition(Vec2(-80.0f, 128.0f));

	this->updateCardLimitText(cardLimitLabel, cardData);

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

	cardContainer->setClickCallback(CC_CALLBACK_1(HexusShopMenu::onCardClick, this, cardData, price, cardLimitLabel));

	cardContainer->addChild(card);
	cardContainer->addChild(goldIcon);
	cardContainer->addChild(priceLabel);
	cardContainer->addChild(cardLimitLabel);

	return cardContainer;
}

void HexusShopMenu::updateCardLimitText(Label* label, CardData* cardData)
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

void HexusShopMenu::onCardClick(MenuSprite* sprite, CardData* cardData, int price, Label* cardLimitLabel)
{
	int gold = CardStorage::getGold();

	if (gold < price || CardStorage::getOwnedCardCount(cardData) >= 3)
	{
		SoundManager::playSoundResource(Resources::Sounds_AFX_INTERFACE_ERROR_1_DFMG);
		return;
	}

	gold -= price;
	SoundManager::playSoundResource(Resources::Sounds_Item_Purchase__1_);

	CardStorage::saveGold(gold);
	this->updateGoldText();

	CardStorage::addStorageCard(cardData);

	this->updateCardLimitText(cardLimitLabel, cardData);
}

void HexusShopMenu::onLootBoxClick(MenuSprite* sprite, int price, std::map<CardData*, float> cardChoices, AnimationNode* animationNode, SpriterEngine::EntityInstance* entity)
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

	std::vector<Card*> chosenCards = std::vector<Card*>
	{
		Card::create(Card::CardStyle::Earth, HexusShopMenu::chooseRandomCard(cardChoices)),
		Card::create(Card::CardStyle::Earth, HexusShopMenu::chooseRandomCard(cardChoices)),
		Card::create(Card::CardStyle::Earth, HexusShopMenu::chooseRandomCard(cardChoices)),
	};

	Size visibleSize = Director::getInstance()->getVisibleSize();

	int index = 0;

	for (auto it = chosenCards.begin(); it != chosenCards.end(); it++)
	{
		float radians = (index * 360.0f / chosenCards.size() + 90.0f) * std::_Pi / 180.0f;

		(*it)->setScale(1.0f);
		(*it)->reveal();
		(*it)->disableInteraction();
		(*it)->setOpacity(0);
		(*it)->setPosition(Vec2(visibleSize.width / 2.0f + std::cos(radians) * 320.0f, visibleSize.height / 2.0f + std::sin(radians) * 320.0f));

		this->addChild((*it));
		index++;
	}

	animationNode->runAction(Sequence::create(
		CallFunc::create([=]()
		{
			this->lootBoxReturnButton->setClickCallback(nullptr);

			for (auto it = this->lootBoxes.begin(); it != this->lootBoxes.end(); it++)
			{
				(*it)->disableInteraction();
			}

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
					this->lootBoxReturnButton->setClickCallback(CC_CALLBACK_0(HexusShopMenu::onLootBoxReturnButtonClick, this, price, chosenCards));
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

void HexusShopMenu::onLootBoxReturnButtonClick(int price, std::vector<Card*> chosenCards)
{
	int gold = CardStorage::getGold();

	this->runAction(Sequence::create(
		CallFunc::create([=]()
		{
			this->lootBoxRewardBackground->runAction(FadeTo::create(0.5f, 0));

			this->lootBoxReturnButton->disableInteraction(255);
			this->lootBoxReturnButton->runAction(FadeOut::create(0.5f));

			for (auto it = chosenCards.begin(); it != chosenCards.end(); it++)
			{
				Card* card = *it;

				card->runAction(Sequence::create(
					FadeOut::create(0.5f),
					DelayTime::create(0.25f),
					CallFunc::create([=]()
					{
						this->chosenCardsNode->removeChild(card);
					}),
					nullptr
				));
			}
		}),
		DelayTime::create(1.5f),
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

CardData* HexusShopMenu::chooseRandomCard(std::map<CardData*, float> cardChoices)
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
		if (sum <= (*it).second)
		{
			return (*it).first;
		}

		sum += (*it).second;
	}

	// Just some non-null default (should not be possible)
	return CardList::getInstance()->cardListByName->at(CardKeys::Binary0);
}

std::map<CardData*, float> HexusShopMenu::getCardsTier1()
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

std::map<CardData*, float> HexusShopMenu::getCardsTier2()
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

std::map<CardData*, float> HexusShopMenu::getCardsTier3()
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

std::map<CardData*, float> HexusShopMenu::getCardsTier4()
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

std::map<CardData*, float> HexusShopMenu::getCardsTier5()
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

std::map<CardData*, float> HexusShopMenu::getCardsTier6()
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

std::map<CardData*, float> HexusShopMenu::getCardsTier7()
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

std::map<CardData*, float> HexusShopMenu::getCardsTier8()
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

std::map<CardData*, float> HexusShopMenu::getCardsTier9()
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

