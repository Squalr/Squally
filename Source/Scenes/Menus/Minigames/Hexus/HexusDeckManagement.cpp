#include "HexusDeckManagement.h"

HexusDeckManagement * HexusDeckManagement::create()
{
	HexusDeckManagement* instance = new HexusDeckManagement();

	instance->autorelease();

	return instance;
}

HexusDeckManagement::HexusDeckManagement()
{
	this->displayDeckCards = std::map<CardData*, MenuCard*>();
	this->displayStorageCards = std::map<CardData*, MenuCard*>();
	this->countLabels = std::map<MenuCard*, Label*>();
	this->deckCards = std::map<CardData*, int>();
	this->storageCards = std::map<CardData*, int>();

	this->background = Sprite::create(Resources::Menus_MinigamesMenu_Hexus_WoodBackground);
	this->storageScrollPane = ScrollPane::create(Size(720.0f, 824.0f), Color4B(0, 0, 0, 196));
	this->deckScrollPane = ScrollPane::create(Size(720.0f, 824.0f), Color4B(0, 0, 0, 196));
	this->storageSprite = Sprite::create(Resources::Menus_Icons_TreasureChest);
	this->storageLabel = Label::create("Cards in Storage", Localization::getMainFont(), Localization::getFontSizeH1(Localization::getMainFont()), Size::ZERO, cocos2d::TextHAlignment::LEFT);
	this->deckSprite = Sprite::create(Resources::Menus_Icons_Satchel);
	this->deckLabel = Label::create("Cards in Deck", Localization::getMainFont(), Localization::getFontSizeH1(Localization::getMainFont()), Size::ZERO, cocos2d::TextHAlignment::RIGHT);
	this->titleSprite = Sprite::create(Resources::Menus_MinigamesMenu_Hexus_AxeLogo);
	this->cardManagementLabel = Label::create("Card Management", Localization::getMainFont(), Localization::getFontSizeH1(Localization::getMainFont()));
	this->cardsInDeckLabel = Label::create("Cards in Deck", Localization::getMainFont(), Localization::getFontSizeH2(Localization::getMainFont()));
	this->cardsInDeckValueLabel = Label::create("CARDS_IN_DECK", Localization::getMainFont(), Localization::getFontSizeH2(Localization::getMainFont()));

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

	cardsInDeckValueLabel->setTextColor(Color4B::GRAY);

	this->storageSprite->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->storageLabel->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->deckSprite->setAnchorPoint(Vec2(1.0f, 0.5f));
	this->deckLabel->setAnchorPoint(Vec2(1.0f, 0.5f));
	this->storageLabel->enableOutline(Color4B::BLACK, 2);
	this->deckLabel->enableOutline(Color4B::BLACK, 2);
	this->cardManagementLabel->enableOutline(Color4B::BLACK, 2);
	this->cardsInDeckLabel->enableOutline(Color4B::BLACK, 2);
	this->cardsInDeckValueLabel->enableOutline(Color4B::BLACK, 2);

	this->addChild(this->background);
	this->addChild(this->storageScrollPane);
	this->addChild(this->deckScrollPane);
	this->addChild(this->storageSprite);
	this->addChild(this->storageLabel);
	this->addChild(this->deckSprite);
	this->addChild(this->deckLabel);
	this->addChild(this->titleSprite);
	this->addChild(this->cardManagementLabel);
	this->addChild(this->cardsInDeckLabel);
	this->addChild(this->cardsInDeckValueLabel);
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

	this->background->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->storageScrollPane->setPosition(Vec2(visibleSize.width / 2.0f - 416.0f - 96.0f, visibleSize.height / 2.0f - 48.0f));
	this->deckScrollPane->setPosition(Vec2(visibleSize.width / 2.0f + 416.0f + 96.0f, visibleSize.height / 2.0f - 48.0f));
	this->storageSprite->setPosition(Vec2(visibleSize.width / 2.0f - 880.0f, visibleSize.height - 96.0f));
	this->storageLabel->setPosition(Vec2(visibleSize.width / 2.0f - 800.0f, visibleSize.height - 96.0f));
	this->deckSprite->setPosition(Vec2(visibleSize.width / 2.0f + 880.0f, visibleSize.height - 96.0f));
	this->deckLabel->setPosition(Vec2(visibleSize.width / 2.0f + 800.0f, visibleSize.height - 96.0f));
	this->titleSprite->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f + 256.0f));
	this->cardManagementLabel->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height - 48.0f));
	this->cardsInDeckLabel->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->cardsInDeckValueLabel->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f - 32.0f));
	this->backButton->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f - 448.0f));

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

	// Position cards
	const Size cardGridSize = Size(176.0f, 256.0f);
	const int cardsPerRow = 4;
	Size storageScrollPaneSize = this->deckScrollPane->getContentSize();
	int storageIndex = 0;

	// Position storage cards
	for (auto it = this->displayStorageCards.begin(); it != this->displayStorageCards.end(); it++)
	{
		CardData* cardData = (*it).first;
		MenuCard* card = (*it).second;

		if (this->storageCards.find(cardData) != this->storageCards.end())
		{
			int count = this->storageCards[cardData];
			int x = storageIndex % cardsPerRow;
			int y = (this->storageCards.size() - 1 - storageIndex + (cardsPerRow - this->storageCards.size() % cardsPerRow)) / cardsPerRow - (this->storageCards.size() % cardsPerRow == 0 ? 1 : 0);

			card->setPosition(Vec2(storageScrollPaneSize.width / 2.0f - 1.5f * cardGridSize.width + x * cardGridSize.width, y * cardGridSize.height + 256.0f));
			
			if (count > 0)
			{
				storageIndex++;
			}
		}
	}

	this->storageScrollPane->fitSizeToContent();

	Size deckScrollPaneSize = this->deckScrollPane->getContentSize();
	int deckIndex = 0;

	// Position deck cards
	for (auto it = this->displayDeckCards.begin(); it != this->displayDeckCards.end(); it++)
	{
		CardData* cardData = (*it).first;
		MenuCard* card = (*it).second;

		if (this->deckCards.find(cardData) != this->deckCards.end())
		{
			int count = this->deckCards[cardData];
			int x = deckIndex % cardsPerRow;
			int y = (this->deckCards.size() - 1 - deckIndex + (cardsPerRow - this->deckCards.size() % cardsPerRow)) / cardsPerRow - (this->deckCards.size() % cardsPerRow == 0 ? 1 : 0);

			card->setPosition(Vec2(storageScrollPaneSize.width / 2.0f - 1.5f * cardGridSize.width + x * cardGridSize.width, y * cardGridSize.height + 256.0f));

			if (count > 0)
			{
				deckIndex++;
			}
		}
	}

	this->deckScrollPane->fitSizeToContent();
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

void HexusDeckManagement::rebuildCardLists()
{
	// Rebuild deck/storage
	this->rebuildDeckCards();
	this->rebuildStorageCards();

	// Update total counts
	int totalStorageCards = 0;
	int totalDeckCards = 0;

	for (auto it = this->storageCards.begin(); it != this->storageCards.end(); it++)
	{
		totalStorageCards += (*it).second;
	}

	for (auto it = this->deckCards.begin(); it != this->deckCards.end(); it++)
	{
		totalDeckCards += (*it).second;
	}

	if (totalDeckCards < CardStorage::minimumDeckCards)
	{
		this->cardsInDeckValueLabel->setString(std::to_string(totalDeckCards) + " / " + std::to_string(CardStorage::minimumDeckCards));
		this->cardsInDeckValueLabel->setTextColor(Color4B::RED);
	}
	else
	{
		this->cardsInDeckValueLabel->setString(std::to_string(totalDeckCards));
		this->cardsInDeckValueLabel->setTextColor(Color4B::GRAY);
	}

	// Position all the cards
	this->initializeListeners();
	this->initializePositions();
}

void HexusDeckManagement::rebuildStorageCards()
{
	this->storageCards = CardStorage::getStorageCardsByCount();

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

	// Update the display counts for all storage cards
	for (auto it = this->displayStorageCards.begin(); it != this->displayStorageCards.end(); it++)
	{
		CardData* cardData = (*it).first;
		MenuCard* card = (*it).second;
		int count = 0;

		if (this->storageCards.find(cardData) != this->storageCards.end())
		{
			count = this->storageCards[cardData];

			this->updateCardCount(this->displayStorageCards[cardData], count);
		}

		// Toggle visibility of the cards
		if (count <= 0)
		{
			card->setVisible(false);
		}
		else
		{
			card->setVisible(true);
		}
	}
}

void HexusDeckManagement::rebuildDeckCards()
{
	this->deckCards = CardStorage::getDeckCardsByCount();

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

	// Update the display counts for all deck cards
	for (auto it = this->displayDeckCards.begin(); it != this->displayDeckCards.end(); it++)
	{
		CardData* cardData = (*it).first;
		MenuCard* card = (*it).second;
		int count = 0;

		if (this->deckCards.find(cardData) != this->deckCards.end())
		{
			count = this->deckCards[cardData];

			this->updateCardCount(this->displayDeckCards[cardData], count);
		}

		// Toggle visibility of the cards
		if (count <= 0)
		{
			card->setVisible(false);
		}
		else
		{
			card->setVisible(true);
		}
	}
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
