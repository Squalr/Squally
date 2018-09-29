#include "HexusDeckManagement.h"

HexusDeckManagement * HexusDeckManagement::create()
{
	HexusDeckManagement* instance = new HexusDeckManagement();

	instance->autorelease();

	return instance;
}

HexusDeckManagement::HexusDeckManagement()
{
	this->deckCards = std::vector<Card*>();
	this->storageCards = std::vector<Card*>();

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
	this->loadStorageCards();
	this->loadDeckCards();
	this->refreshCardCounts();

	FadeScene::onEnter();

	float delay = 0.25f;
	float duration = 0.35f;

	GameUtils::fadeInObject(this->backButton, delay, duration);
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
	
	for (auto it = this->deckCards.begin(); it != this->deckCards.end(); it++)
	{
		(*it)->setMouseClickCallback(CC_CALLBACK_1(HexusDeckManagement::onDeckCardClick, this));
		(*it)->setMouseOverCallback(CC_CALLBACK_1(HexusDeckManagement::onDeckCardMouseOver, this));
	}
	
	for (auto it = this->storageCards.begin(); it != this->storageCards.end(); it++)
	{
		(*it)->setMouseClickCallback(CC_CALLBACK_1(HexusDeckManagement::onStorageCardClick, this));
		(*it)->setMouseOverCallback(CC_CALLBACK_1(HexusDeckManagement::onStorageCardMouseOver, this));
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

	// Sort cards first
	sort(this->storageCards.begin(), this->storageCards.end(), [](Card* a, Card* b) -> bool
	{ 
		return std::strcmp(a->cardData == nullptr ? "" : a->cardData->cardName.c_str(), b->cardData == nullptr ? "" : b->cardData->cardName.c_str()) < 0;
	});
	
	sort(this->deckCards.begin(), this->deckCards.end(), [](Card* a, Card* b) -> bool
	{ 
		return std::strcmp(a->cardData == nullptr ? "" : a->cardData->cardName.c_str(), b->cardData == nullptr ? "" : b->cardData->cardName.c_str()) < 0;
	});

	// Position cards
	Size storageScrollPaneSize = this->deckScrollPane->getContentSize();
	int index = 0;

	for (auto it = this->storageCards.begin(); it != this->storageCards.end(); it++)
	{
		int x = index % 3;
		int y = (this->storageCards.size() - 1 - index + (3 - this->storageCards.size() % 3)) / 3 - (this->storageCards.size() % 3 == 0 ? 1 : 0);

		(*it)->setPosition(Vec2(storageScrollPaneSize.width / 2.0f + (x - 1) * 240.0f, y * 480.0f + 256.0f));

		index++;
	}

	this->storageScrollPane->fitSizeToContent();

	Size deckScrollPaneSize = this->deckScrollPane->getContentSize();
	index = 0;

	for (auto it = this->deckCards.begin(); it != this->deckCards.end(); it++)
	{
		int x = index % 3;
		int y = (this->deckCards.size() - 1 - index + (3 - this->deckCards.size() % 3)) / 3 - (this->deckCards.size() % 3 == 0 ? 1 : 0);

		(*it)->setPosition(Vec2(deckScrollPaneSize.width / 2.0f + (x - 1) * 240.0f, y * 480.0f + 256.0f));

		index++;
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
	std::vector<CardData*> deckCardData = std::vector<CardData*>();
	
	for (auto it = this->deckCards.begin(); it != this->deckCards.end(); it++)
	{
		deckCardData.push_back((*it)->cardData);
	}

	std::vector<CardData*> storageCardData = std::vector<CardData*>();
	
	for (auto it = this->storageCards.begin(); it != this->storageCards.end(); it++)
	{
		storageCardData.push_back((*it)->cardData);
	}

	CardStorage::saveDeckCards(deckCardData);
	CardStorage::saveStorageCards(storageCardData);

	if (exit)
	{
		NavigationEvents::navigateBack();
	}
}

void HexusDeckManagement::loadStorageCards()
{
	for (auto it = storageCards.begin(); it != storageCards.end(); it++)
	{
		this->storageScrollPane->removeChild(*it);
	}

	this->storageCards.clear();

	std::vector<CardData*> savedStorageCards = CardStorage::getStorageCards();

	for (auto it = savedStorageCards.begin(); it != savedStorageCards.end(); it++)
	{
		Card* card = Card::create(Card::CardStyle::Earth, *it);
		card->reveal();
		card->setScale(1.0f);

		this->storageCards.push_back(card);
		this->storageScrollPane->addChild(card);
	}
}

void HexusDeckManagement::loadDeckCards()
{
	for (auto it = deckCards.begin(); it != deckCards.end(); it++)
	{
		this->deckScrollPane->removeChild(*it);
	}

	this->deckCards.clear();

	std::vector<CardData*> savedDeckCards = CardStorage::getDeckCards();

	for (auto it = savedDeckCards.begin(); it != savedDeckCards.end(); it++)
	{
		Card* card = Card::create(Card::CardStyle::Earth, *it);
		card->reveal();
		card->setScale(1.0f);

		this->deckCards.push_back(card);
		this->deckScrollPane->addChild(card);
	}
}

void HexusDeckManagement::refreshCardCounts()
{
	if ((int)this->deckCards.size() < CardStorage::minimumDeckCards)
	{
		this->cardsInDeckValueLabel->setString(std::to_string(this->deckCards.size()) + " / " + std::to_string(CardStorage::minimumDeckCards));
		this->cardsInDeckValueLabel->setTextColor(Color4B::RED);
	}
	else
	{
		this->cardsInDeckValueLabel->setString(std::to_string(this->deckCards.size()));
		this->cardsInDeckValueLabel->setTextColor(Color4B::GRAY);
	}
}

void HexusDeckManagement::onDeckCardClick(Card* card)
{
	this->deckCards.erase(std::remove(this->deckCards.begin(), this->deckCards.end(), card), this->deckCards.end());
	this->storageCards.push_back(card);
	GameUtils::changeParent(card, this->storageScrollPane, false);
	SoundManager::playSoundResource(Resources::Sounds_Hexus_08_Card);

	this->initializeListeners();
	this->initializePositions();
	this->refreshCardCounts();
}

void HexusDeckManagement::onStorageCardClick(Card* card)
{
	this->storageCards.erase(std::remove(this->storageCards.begin(), this->storageCards.end(), card), this->storageCards.end());
	this->deckCards.push_back(card);
	GameUtils::changeParent(card, this->deckScrollPane, false);
	SoundManager::playSoundResource(Resources::Sounds_Hexus_08_Card);
	
	this->initializeListeners();
	this->initializePositions();
	this->refreshCardCounts();
}

void HexusDeckManagement::onDeckCardMouseOver(Card* card)
{
	
}

void HexusDeckManagement::onStorageCardMouseOver(Card* card)
{

}
