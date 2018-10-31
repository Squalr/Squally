#include "HexusDeckManagement.h"

HexusDeckManagement * HexusDeckManagement::create()
{
	HexusDeckManagement* instance = new HexusDeckManagement();

	instance->autorelease();

	return instance;
}

HexusDeckManagement::HexusDeckManagement()
{
	this->filters = ToggleGroup::create(CC_CALLBACK_1(HexusDeckManagement::onToggleSelect, this));
	this->activeFilter = CardFilterFlags::All;
	this->displayDeckCards = std::map<CardData*, MenuCard*>();
	this->displayStorageCards = std::map<CardData*, MenuCard*>();
	this->countLabels = std::map<MenuCard*, Label*>();
	this->deckCards = std::map<CardData*, int>();
	this->storageCards = std::map<CardData*, int>();

	this->background = Sprite::create(Resources::Menus_MinigamesMenu_Hexus_WoodBackground);
	this->storageScrollPane = ScrollPane::create(Size(720.0f, 820.0f), Color4B(0, 0, 0, 196));
	this->deckScrollPane = ScrollPane::create(Size(720.0f, 820.0f), Color4B(0, 0, 0, 196));
	this->storageSprite = Sprite::create(Resources::Menus_Icons_TreasureChest);
	this->storageLabel = Label::create("Cards in Storage", Localization::getMainFont(), Localization::getFontSizeH1(Localization::getMainFont()), Size::ZERO, cocos2d::TextHAlignment::LEFT);
	this->deckSprite = Sprite::create(Resources::Menus_Icons_Satchel);
	this->deckLabel = Label::create("Cards in Deck", Localization::getMainFont(), Localization::getFontSizeH1(Localization::getMainFont()), Size::ZERO, cocos2d::TextHAlignment::RIGHT);
	this->titleSprite = Sprite::create(Resources::Menus_MinigamesMenu_Hexus_AxeLogo);

	this->totalCardsInDeckLabel = Label::create("Cards in Deck", Localization::getMainFont(), Localization::getFontSizeH3(Localization::getMainFont()));
	this->totalCardsInDeckValueLabel = Label::create("PLACEHOLDER_CARDS_IN_DECK", Localization::getMainFont(), Localization::getFontSizeH3(Localization::getMainFont()));
	this->binaryCardsInDeckLabel = Label::create("Binary Cards", Localization::getMainFont(), Localization::getFontSizeH3(Localization::getMainFont()));
	this->binaryCardsInDeckValueLabel = Label::create("PLACEHOLDER_BINARY_CARDS_IN_DECK", Localization::getMainFont(), Localization::getFontSizeH3(Localization::getMainFont()));
	this->decimalCardsInDeckLabel = Label::create("Decimal Cards", Localization::getMainFont(), Localization::getFontSizeH3(Localization::getMainFont()));
	this->decimalCardsInDeckValueLabel = Label::create("PLACEHOLDER_DECIMAL_CARDS_IN_DECK", Localization::getMainFont(), Localization::getFontSizeH3(Localization::getMainFont()));
	this->hexCardsInDeckLabel = Label::create("Hex Cards", Localization::getMainFont(), Localization::getFontSizeH3(Localization::getMainFont()));
	this->hexCardsInDeckValueLabel = Label::create("PLACEHOLDER_HEX_CARDS_IN_DECK", Localization::getMainFont(), Localization::getFontSizeH3(Localization::getMainFont()));
	this->specialCardsInDeckLabel = Label::create("Special Cards", Localization::getMainFont(), Localization::getFontSizeH3(Localization::getMainFont()));
	this->specialCardsInDeckValueLabel = Label::create("PLACEHOLDER_SPECIAL_CARDS_IN_DECK", Localization::getMainFont(), Localization::getFontSizeH3(Localization::getMainFont()));

	MenuSprite* allButtonUnselected = MenuSprite::create(Resources::Menus_Buttons_WoodSquareButtonSmall, Resources::Menus_Buttons_WoodSquareButtonSmallSelected, Resources::Menus_Buttons_WoodSquareButtonSmallSelected);
	MenuSprite* allButtonSelected = MenuSprite::create(Resources::Menus_Buttons_WoodSquareButtonSmallSelected, Resources::Menus_Buttons_WoodSquareButtonSmallSelected, Resources::Menus_Buttons_WoodSquareButtonSmallSelected);
	allButtonUnselected->addChild(Sprite::create(Resources::Menus_MinigamesMenu_Hexus_IconAll));
	allButtonSelected->addChild(Sprite::create(Resources::Menus_MinigamesMenu_Hexus_IconAll));

	MenuSprite* specialButtonUnselected = MenuSprite::create(Resources::Menus_Buttons_WoodSquareButtonSmall, Resources::Menus_Buttons_WoodSquareButtonSmallSelected, Resources::Menus_Buttons_WoodSquareButtonSmallSelected);
	MenuSprite* specialButtonSelected = MenuSprite::create(Resources::Menus_Buttons_WoodSquareButtonSmallSelected, Resources::Menus_Buttons_WoodSquareButtonSmallSelected, Resources::Menus_Buttons_WoodSquareButtonSmallSelected);
	specialButtonUnselected->addChild(Sprite::create(Resources::Menus_MinigamesMenu_Hexus_IconSpecial));
	specialButtonSelected->addChild(Sprite::create(Resources::Menus_MinigamesMenu_Hexus_IconSpecial));

	MenuSprite* binaryButtonUnselected = MenuSprite::create(Resources::Menus_Buttons_WoodSquareButtonSmall, Resources::Menus_Buttons_WoodSquareButtonSmallSelected, Resources::Menus_Buttons_WoodSquareButtonSmallSelected);
	MenuSprite* binaryButtonSelected = MenuSprite::create(Resources::Menus_Buttons_WoodSquareButtonSmallSelected, Resources::Menus_Buttons_WoodSquareButtonSmallSelected, Resources::Menus_Buttons_WoodSquareButtonSmallSelected);
	binaryButtonUnselected->addChild(Sprite::create(Resources::Menus_MinigamesMenu_Hexus_IconBinary));
	binaryButtonSelected->addChild(Sprite::create(Resources::Menus_MinigamesMenu_Hexus_IconBinary));

	MenuSprite* decimalButtonUnselected = MenuSprite::create(Resources::Menus_Buttons_WoodSquareButtonSmall, Resources::Menus_Buttons_WoodSquareButtonSmallSelected, Resources::Menus_Buttons_WoodSquareButtonSmallSelected);
	MenuSprite* decimalButtonSelected = MenuSprite::create(Resources::Menus_Buttons_WoodSquareButtonSmallSelected, Resources::Menus_Buttons_WoodSquareButtonSmallSelected, Resources::Menus_Buttons_WoodSquareButtonSmallSelected);
	decimalButtonUnselected->addChild(Sprite::create(Resources::Menus_MinigamesMenu_Hexus_IconDecimal));
	decimalButtonSelected->addChild(Sprite::create(Resources::Menus_MinigamesMenu_Hexus_IconDecimal));

	MenuSprite* hexButtonUnselected = MenuSprite::create(Resources::Menus_Buttons_WoodSquareButtonSmall, Resources::Menus_Buttons_WoodSquareButtonSmallSelected, Resources::Menus_Buttons_WoodSquareButtonSmallSelected);
	MenuSprite* hexButtonSelected = MenuSprite::create(Resources::Menus_Buttons_WoodSquareButtonSmallSelected, Resources::Menus_Buttons_WoodSquareButtonSmallSelected, Resources::Menus_Buttons_WoodSquareButtonSmallSelected);
	hexButtonUnselected->addChild(Sprite::create(Resources::Menus_MinigamesMenu_Hexus_IconHex));
	hexButtonSelected->addChild(Sprite::create(Resources::Menus_MinigamesMenu_Hexus_IconHex));

	this->allButton = CCheckbox::create(allButtonUnselected, allButtonSelected, true, nullptr);
	this->specialButton = CCheckbox::create(specialButtonUnselected, specialButtonSelected, false, nullptr);
	this->binaryButton = CCheckbox::create(binaryButtonUnselected, binaryButtonSelected, false, nullptr);
	this->decimalButton = CCheckbox::create(decimalButtonUnselected, decimalButtonSelected, false, nullptr);
	this->hexButton = CCheckbox::create(hexButtonUnselected, hexButtonSelected, false, nullptr);

	this->filters->addToggle(this->allButton);
	this->filters->addToggle(this->specialButton);
	this->filters->addToggle(this->binaryButton);
	this->filters->addToggle(this->decimalButton);
	this->filters->addToggle(this->hexButton);
	
		this->activeFilter = CardFilterFlags::All;
	Label* backButtonLabel = Label::create("Back", Localization::getMainFont(), Localization::getFontSizeP(Localization::getMainFont()));
	Label* backButtonLabelHover = Label::create("Back", Localization::getMainFont(), Localization::getFontSizeP(Localization::getMainFont()));
	Label* backButtonLabelClick = Label::create("Back", Localization::getMainFont(), Localization::getFontSizeP(Localization::getMainFont()));

	backButtonLabel->enableOutline(Color4B::BLACK, 2);
	backButtonLabelHover->enableOutline(Color4B::BLACK, 2);
	backButtonLabelClick->enableOutline(Color4B::BLACK, 2);

	this->backButton = TextMenuSprite::create(
		backButtonLabel,
		backButtonLabelHover,
		backButtonLabelClick,
		Resources::Menus_Buttons_GenericButton,
		Resources::Menus_Buttons_GenericButtonHover,
		Resources::Menus_Buttons_GenericButtonClick
	);

	// Create all cards for deck. Every card gets created with count = 0, and those that are 0 get hidden
	for (auto it = CardList::getInstance()->cardListByName->begin(); it != CardList::getInstance()->cardListByName->end(); it++)
	{
		CardData* cardData = (*it).second;

		// These only need to be instantiated once
		if (this->displayDeckCards.find(cardData) == this->displayDeckCards.end())
		{
			MenuCard* card = this->createCard(cardData, 0);

			displayDeckCards.emplace(cardData, card);

			this->deckScrollPane->addChild(card);
		}
	}

	// Create all cards for storage. Every card gets created with count = 0, and those that are 0 get hidden
	for (auto it = CardList::getInstance()->cardListByName->begin(); it != CardList::getInstance()->cardListByName->end(); it++)
	{
		CardData* cardData = (*it).second;

		// These only need to be instantiated once
		if (this->displayStorageCards.find(cardData) == this->displayStorageCards.end())
		{
			MenuCard* card = this->createCard(cardData, 0);

			displayStorageCards.emplace(cardData, card);

			this->storageScrollPane->addChild(card);
		}
	}

	this->storageSprite->setAnchorPoint(Vec2(1.0f, 0.5f));
	this->storageLabel->setAnchorPoint(Vec2(1.0f, 0.5f));
	this->deckSprite->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->deckLabel->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->storageLabel->enableOutline(Color4B::BLACK, 2);
	this->deckLabel->enableOutline(Color4B::BLACK, 2);

	this->totalCardsInDeckLabel->enableOutline(Color4B::BLACK, 2);
	this->totalCardsInDeckValueLabel->enableOutline(Color4B::BLACK, 2);
	this->binaryCardsInDeckLabel->enableOutline(Color4B::BLACK, 2);
	this->binaryCardsInDeckValueLabel->enableOutline(Color4B::BLACK, 2);
	this->decimalCardsInDeckLabel->enableOutline(Color4B::BLACK, 2);
	this->decimalCardsInDeckValueLabel->enableOutline(Color4B::BLACK, 2);
	this->hexCardsInDeckLabel->enableOutline(Color4B::BLACK, 2);
	this->hexCardsInDeckValueLabel->enableOutline(Color4B::BLACK, 2);
	this->specialCardsInDeckLabel->enableOutline(Color4B::BLACK, 2);
	this->specialCardsInDeckValueLabel->enableOutline(Color4B::BLACK, 2);

	this->addChild(this->background);
	this->addChild(this->storageScrollPane);
	this->addChild(this->deckScrollPane);
	this->addChild(this->storageSprite);
	this->addChild(this->storageLabel);
	this->addChild(this->deckSprite);
	this->addChild(this->deckLabel);
	this->addChild(this->titleSprite);
	this->addChild(this->totalCardsInDeckLabel);
	this->addChild(this->totalCardsInDeckValueLabel);
	this->addChild(this->binaryCardsInDeckLabel);
	this->addChild(this->binaryCardsInDeckValueLabel);
	this->addChild(this->decimalCardsInDeckLabel);
	this->addChild(this->decimalCardsInDeckValueLabel);
	this->addChild(this->hexCardsInDeckLabel);
	this->addChild(this->hexCardsInDeckValueLabel);
	this->addChild(this->specialCardsInDeckLabel);
	this->addChild(this->specialCardsInDeckValueLabel);
	this->addChild(this->filters);
	this->addChild(this->backButton);
	this->addChild(Mouse::create());
}

HexusDeckManagement::~HexusDeckManagement()
{
}

void HexusDeckManagement::onEnter()
{

	FadeScene::onEnter();

	float delay = 0.25f;
	float duration = 0.35f;

	GameUtils::fadeInObject(this->backButton, delay, duration);

	this->rebuildCardLists();
}

void HexusDeckManagement::onExit()
{
	this->save(false);

	FadeScene::onExit();
}

void HexusDeckManagement::initializeListeners()
{
	FadeScene::initializeListeners();

	EventListenerKeyboard* keyboardListener = EventListenerKeyboard::create();

	keyboardListener->onKeyPressed = CC_CALLBACK_2(HexusDeckManagement::onKeyPressed, this);
	
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);
	
	for (auto it = this->displayDeckCards.begin(); it != this->displayDeckCards.end(); it++)
	{
		(*it).second->setMouseClickCallback(CC_CALLBACK_1(HexusDeckManagement::onDeckCardClick, this));
		(*it).second->setMouseOverCallback(CC_CALLBACK_1(HexusDeckManagement::onDeckCardMouseOver, this));
	}
	
	for (auto it = this->displayStorageCards.begin(); it != this->displayStorageCards.end(); it++)
	{
		(*it).second->setMouseClickCallback(CC_CALLBACK_1(HexusDeckManagement::onStorageCardClick, this));
		(*it).second->setMouseOverCallback(CC_CALLBACK_1(HexusDeckManagement::onStorageCardMouseOver, this));
	}

	this->backButton->setClickCallback(CC_CALLBACK_1(HexusDeckManagement::onBackClick, this));
}

void HexusDeckManagement::initializePositions()
{
	FadeScene::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	const float totalsOffset = 320.0f;
	const float totalsSpacing = 32.0f;
	const float totalsValueOffset = 32.0f;

	this->background->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->storageScrollPane->setPosition(Vec2(visibleSize.width / 2.0f - 416.0f - 96.0f, visibleSize.height / 2.0f - 48.0f));
	this->deckScrollPane->setPosition(Vec2(visibleSize.width / 2.0f + 416.0f + 96.0f, visibleSize.height / 2.0f - 48.0f));
	this->storageSprite->setPosition(Vec2(visibleSize.width / 2.0f - 144.0f, visibleSize.height - 96.0f));
	this->storageLabel->setPosition(Vec2(visibleSize.width / 2.0f - (144.0f + 80.0f), visibleSize.height - 96.0f));
	this->deckSprite->setPosition(Vec2(visibleSize.width / 2.0f + 144.0f, visibleSize.height - 96.0f));
	this->deckLabel->setPosition(Vec2(visibleSize.width / 2.0f + (144.0f + 80.0f), visibleSize.height - 96.0f));
	this->titleSprite->setPosition(Vec2(visibleSize.width / 2.0f + 756.0f, visibleSize.height / 2.0f + 320.0f));

	this->totalCardsInDeckLabel->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f + totalsOffset - totalsSpacing * 0));
	this->totalCardsInDeckValueLabel->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f + totalsOffset - totalsSpacing * 0 - totalsValueOffset));
	this->binaryCardsInDeckLabel->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f + totalsOffset - totalsSpacing * 1));
	this->binaryCardsInDeckValueLabel->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f + totalsOffset - totalsSpacing * 1 - totalsValueOffset));
	this->decimalCardsInDeckLabel->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f + totalsOffset - totalsSpacing * 2));
	this->decimalCardsInDeckValueLabel->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f + totalsOffset - totalsSpacing * 2 - totalsValueOffset));
	this->hexCardsInDeckLabel->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f + totalsOffset - totalsSpacing * 3));
	this->hexCardsInDeckValueLabel->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f + totalsOffset - totalsSpacing * 3 - totalsValueOffset));
	this->specialCardsInDeckLabel->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f + totalsOffset - totalsSpacing * 4));
	this->specialCardsInDeckValueLabel->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f + totalsOffset - totalsSpacing * 4 - totalsValueOffset));

	this->backButton->setPosition(Vec2(visibleSize.width / 2.0f - 756.0f, visibleSize.height - 64.0f));
	this->allButton->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f + 32.0f - 112.0f * 0));
	this->specialButton->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f + 32.0f - 112.0f * 1));
	this->binaryButton->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f + 32.0f - 112.0f * 2));
	this->decimalButton->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f + 32.0f - 112.0f * 3));
	this->hexButton->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f + 32.0f - 112.0f * 4));

	/*
	// Sort cards first
	std::sort(this->displayStorageCards.begin(), this->displayStorageCards.end(), [](Card* a, Card* b) -> bool
	{ 
		return std::strcmp(a->cardData == nullptr ? "" : a->cardData->cardName.c_str(), b->cardData == nullptr ? "" : b->cardData->cardName.c_str()) < 0;
	});
	
	std::sort(this->displayDeckCards.begin(), this->displayDeckCards.end(), [](Card* a, Card* b) -> bool
	{ 
		return std::strcmp(a->cardData == nullptr ? "" : a->cardData->cardName.c_str(), b->cardData == nullptr ? "" : b->cardData->cardName.c_str()) < 0;
	});
	*/

	auto positionCards = [=](ScrollPane* scrollPane, std::map<CardData*, int> cards, std::map<CardData*, MenuCard*> displayCards)
	{
		// Position cards
		const Size cardGridSize = Size(176.0f, 256.0f);
		const int cardsPerRow = 4;
		Size paneSize = scrollPane->getContentSize();
		Size marginSize = (paneSize - (cardGridSize * cardsPerRow)) / 2.0f;
		int index = 0;
		int visibleCardCount = 0;

		for (auto it = displayCards.begin(); it != displayCards.end(); it++)
		{
			MenuCard* card = (*it).second;

			if (card->isVisible())
			{
				visibleCardCount++;
			}
		}

		for (auto it = displayCards.begin(); it != displayCards.end(); it++)
		{
			CardData* cardData = (*it).first;
			MenuCard* card = (*it).second;

			int x = index % cardsPerRow;
			int y = (visibleCardCount - 1 - index + (cardsPerRow - visibleCardCount % cardsPerRow)) / cardsPerRow - (visibleCardCount % cardsPerRow == 0 ? 1 : 0);

			card->setPosition(Vec2(paneSize.width / 2.0f + marginSize.width - (x - cardsPerRow / 2 + 1) * cardGridSize.width, y * cardGridSize.height + 128.0f));

			if (card->isVisible())
			{
				index++;
			}
		}

		scrollPane->fitSizeToContent(Rect(0.0f, 64.0f, 0.0f, 0.0f));
	};

	positionCards(this->storageScrollPane, this->storageCards, this->displayStorageCards);
	positionCards(this->deckScrollPane, this->deckCards, this->displayDeckCards);
}

void HexusDeckManagement::onToggleSelect(CCheckbox* activeToggle)
{
	if (activeToggle == this->allButton)
	{
		this->activeFilter = CardFilterFlags::All;
	}
	else if (activeToggle == this->specialButton)
	{
		this->activeFilter = CardFilterFlags::Special;
	}
	else if (activeToggle == this->binaryButton)
	{
		this->activeFilter = CardFilterFlags::Binary;
	}
	else if (activeToggle == this->decimalButton)
	{
		this->activeFilter = CardFilterFlags::Decimal;
	}
	else if (activeToggle == this->hexButton)
	{
		this->activeFilter = CardFilterFlags::Hex;
	}

	this->rebuildCardLists();
}

void HexusDeckManagement::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode)
	{
		case EventKeyboard::KeyCode::KEY_ESCAPE:
			event->stopPropagation();
			this->save(true);
			break;
		default:
			break;
	}
}

void HexusDeckManagement::onBackClick(MenuSprite* menuSprite)
{
	this->save(true);
}

void HexusDeckManagement::save(bool exit)
{
	CardStorage::saveDeckCardsByCount(this->deckCards);
	CardStorage::saveStorageCardsByCount(this->storageCards);

	if (exit)
	{
		NavigationEvents::navigateBack();
	}
}

void HexusDeckManagement::rebuildCardList(std::map<CardData*, int> cards, std::map<CardData*, MenuCard*> displayCards)
{
	// Update the display counts
	for (auto it = displayCards.begin(); it != displayCards.end(); it++)
	{
		CardData* cardData = (*it).first;
		MenuCard* card = (*it).second;
		int count = 0;

		if (cards.find(cardData) != cards.end())
		{
			count = cards[cardData];

			this->updateCardCount(displayCards[cardData], count);
		}

		// Always hide cards when we have none of that type
		if (count <= 0)
		{
			card->setVisible(false);
			continue;
		}

		// Hide based on filters
		switch (cardData->cardType)
		{
			case CardData::CardType::Binary:
			{
				if ((this->activeFilter & CardFilterFlags::Binary) != 0)
				{
					card->setVisible(true);
				}
				else
				{
					card->setVisible(false);
				}

				break;
			}
			case CardData::CardType::Decimal:
			{
				if ((this->activeFilter & CardFilterFlags::Decimal) != 0)
				{
					card->setVisible(true);
				}
				else
				{
					card->setVisible(false);
				}

				break;
			}
			case CardData::CardType::Hexidecimal:
			{
				if ((this->activeFilter & CardFilterFlags::Hex) != 0)
				{
					card->setVisible(true);
				}
				else
				{
					card->setVisible(false);
				}

				break;
			}
			default:
			{
				if ((this->activeFilter & CardFilterFlags::Special) != 0)
				{
					card->setVisible(true);
				}
				else
				{
					card->setVisible(false);
				}

				break;
			}
		}
	}
}

void HexusDeckManagement::rebuildCardLists()
{
	this->storageCards = CardStorage::getStorageCardsByCount();
	this->deckCards = CardStorage::getDeckCardsByCount();

	// Rebuild deck/storage
	this->rebuildCardList(this->deckCards, this->displayDeckCards);
	this->rebuildCardList(this->storageCards, this->displayStorageCards);

	// Update total counts
	int totalDeckCards = 0;
	int totalDeckBinaryCards = 0;
	int totalDeckDecimalCards = 0;
	int totalDeckHexCards = 0;
	int totalDeckSpecialCards = 0;

	for (auto it = this->deckCards.begin(); it != this->deckCards.end(); it++)
	{
		CardData* cardData = (*it).first;
		int count = (*it).second;

		totalDeckCards += count;

		switch (cardData->cardType)
		{
			case CardData::CardType::Binary:
				totalDeckBinaryCards++;
				break;
			case CardData::CardType::Decimal:
				totalDeckDecimalCards++;
				break;
			case CardData::CardType::Hexidecimal:
				totalDeckHexCards++;
				break;
			default:
				totalDeckSpecialCards++;
				break;
		}
	}

	if (totalDeckCards < CardStorage::minimumDeckCards)
	{
		this->totalCardsInDeckValueLabel->setString(std::to_string(totalDeckCards) + " / " + std::to_string(CardStorage::minimumDeckCards));
		this->totalCardsInDeckValueLabel->setTextColor(Color4B::RED);
	}
	else
	{
		this->totalCardsInDeckValueLabel->setString(std::to_string(totalDeckCards));
		this->totalCardsInDeckValueLabel->setTextColor(Color4B::YELLOW);
	}

	this->binaryCardsInDeckValueLabel->setString(std::to_string(totalDeckBinaryCards));
	this->decimalCardsInDeckValueLabel->setString(std::to_string(totalDeckDecimalCards));
	this->hexCardsInDeckValueLabel->setString(std::to_string(totalDeckHexCards));
	this->specialCardsInDeckValueLabel->setString(std::to_string(totalDeckSpecialCards));

	// Position all the cards
	this->initializeListeners();
	this->initializePositions();
}

MenuCard* HexusDeckManagement::createCard(CardData* cardData, int count)
{
	MenuCard* card = MenuCard::create(Card::CardStyle::Earth, cardData);
	Label* label = Label::create("PLACEHOLDER_CARD_COUNT", Localization::getCodingFont(), 64.0f);

	label->enableOutline(Color4B::BLACK, 4);
	label->setAnchorPoint(Vec2(0.0f, 0.5f));
	label->setPosition(Vec2(-96.0f, 128.0f));

	card->addDisplayItem(label);

	card->setScale(0.6f);
	card->reveal();

	this->countLabels.emplace(card, label);
	this->updateCardCount(card, count);

	return card;
}

void HexusDeckManagement::updateCardCount(MenuCard* card, int count)
{
	if (this->countLabels.find(card) != this->countLabels.end())
	{
		this->countLabels[card]->setString("x" + std::to_string(count));
	}
}

void HexusDeckManagement::onDeckCardClick(Card* card)
{
	// Remove from deck
	this->deckCards[card->cardData] = MathUtils::clamp(this->deckCards[card->cardData] - 1, 0, 3);

	// Add to storage
	this->storageCards[card->cardData] = MathUtils::clamp(this->storageCards[card->cardData] + 1, 0, 3);

	this->save(false);

	SoundManager::playSoundResource(Resources::Sounds_Hexus_08_Card);

	this->rebuildCardLists();
}

void HexusDeckManagement::onStorageCardClick(Card* card)
{
	// Remove from storage
	this->storageCards[card->cardData] = MathUtils::clamp(this->storageCards[card->cardData] - 1, 0, 3);

	// Add to deck
	this->deckCards[card->cardData] = MathUtils::clamp(this->deckCards[card->cardData] + 1, 0, 3);

	this->save(false);

	SoundManager::playSoundResource(Resources::Sounds_Hexus_08_Card);
	
	this->rebuildCardLists();
}

void HexusDeckManagement::onDeckCardMouseOver(Card* card)
{
}

void HexusDeckManagement::onStorageCardMouseOver(Card* card)
{
}
