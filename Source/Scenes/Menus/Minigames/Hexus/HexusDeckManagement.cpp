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
	this->storageScrollPane = ScrollPane::create(Size(720.0f, 840.0f), Color4B(0, 0, 0, 196));
	this->deckScrollPane = ScrollPane::create(Size(720.0f, 840.0f), Color4B(0, 0, 0, 196));
	this->storageLabel = Label::create("Storage", Localization::getMainFont(), Localization::getFontSizeH1(Localization::getMainFont()));
	this->deckLabel = Label::create("Deck", Localization::getMainFont(), Localization::getFontSizeH1(Localization::getMainFont()));

	this->storageLabel->enableOutline(Color4B::BLACK, 2);
	this->deckLabel->enableOutline(Color4B::BLACK, 2);

	this->addChild(this->background);
	this->addChild(this->storageScrollPane);
	this->addChild(this->deckScrollPane);
	this->addChild(this->storageLabel);
	this->addChild(this->deckLabel);
	this->addChild(Mouse::create());
}

HexusDeckManagement::~HexusDeckManagement()
{
}

void HexusDeckManagement::onEnter()
{
	this->loadStorageCards();
	this->loadDeckCards();

	FadeScene::onEnter();

	float delay = 0.25f;
	float duration = 0.35f;
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
}

void HexusDeckManagement::initializePositions()
{
	FadeScene::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->background->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->storageScrollPane->setPosition(Vec2(visibleSize.width / 2.0f - 416.0f - 96.0f, visibleSize.height / 2.0f - 64.0f));
	this->deckScrollPane->setPosition(Vec2(visibleSize.width / 2.0f + 416.0f + 96.0f, visibleSize.height / 2.0f - 64.0f));
	this->storageLabel->setPosition(Vec2(visibleSize.width / 2.0f - 416.0f - 96.0f, visibleSize.height - 96.0f));
	this->deckLabel->setPosition(Vec2(visibleSize.width / 2.0f + 416.0f + 96.0f, visibleSize.height - 96.0f));

	// Sort cards first
	sort(this->storageCards.begin(), this->storageCards.end(), [](Card* a, Card* b) -> bool
	{ 
		return std::strcmp(a->cardData->cardName.c_str(), b->cardData->cardName.c_str()) < 0;
	});
	
	sort(this->deckCards.begin(), this->deckCards.end(), [](Card* a, Card* b) -> bool
	{ 
		return std::strcmp(a->cardData->cardName.c_str(), b->cardData->cardName.c_str()) < 0;
	});

	// Position cards
	Size storageScrollPaneSize = this->deckScrollPane->getContentSize();
	int index = 0;

	for (auto it = this->storageCards.begin(); it != this->storageCards.end(); it++)
	{
		int x = index % 3;
		int y = index / 3;

		(*it)->setPosition(Vec2(storageScrollPaneSize.width / 2.0f + (x - 1) * 240.0f, y * 320.0f + 256.0f));

		index++;
	}

	this->storageScrollPane->fitSizeToContent();

	Size deckScrollPaneSize = this->deckScrollPane->getContentSize();
	index = 0;

	for (auto it = this->deckCards.begin(); it != this->deckCards.end(); it++)
	{
		int x = index % 3;
		int y = index / 3;

		(*it)->setPosition(Vec2(deckScrollPaneSize.width / 2.0f + (x - 1) * 240.0f, y * 320.0f + 256.0f));

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
			NavigationEvents::navigateBack();
			break;
		default:
			break;
	}
}

void HexusDeckManagement::onCloseClick(MenuSprite* menuSprite)
{
	NavigationEvents::navigateBack();
}

void HexusDeckManagement::loadStorageCards()
{
	this->storageScrollPane->removeAllChildren();

	std::vector<CardData*> savedStorageCards = CardStorage::getStorageCards();

	for (auto it = savedStorageCards.begin(); it != savedStorageCards.end(); it++)
	{
		Card* card = Card::create(Card::CardStyle::Earth, *it);
		card->reveal();
		card->setScale(0.6f);

		this->storageCards.push_back(card);
		this->storageScrollPane->addChild(card);
	}
}

void HexusDeckManagement::loadDeckCards()
{
	this->deckScrollPane->removeAllChildren();

	std::vector<CardData*> savedDeckCards = CardStorage::getDeckCards();

	for (auto it = savedDeckCards.begin(); it != savedDeckCards.end(); it++)
	{
		Card* card = Card::create(Card::CardStyle::Earth, *it);
		card->reveal();
		card->setScale(0.6f);

		this->deckCards.push_back(card);
		this->deckScrollPane->addChild(card);
	}
}

void HexusDeckManagement::onDeckCardClick(Card* card)
{
	this->deckCards.erase(std::remove(this->deckCards.begin(), this->deckCards.end(), card), this->deckCards.end());
	this->storageCards.push_back(card);
	GameUtils::changeParent(card, this->storageScrollPane, false);

	this->initializeListeners();
	this->initializePositions();
}

void HexusDeckManagement::onStorageCardClick(Card* card)
{
	this->storageCards.erase(std::remove(this->storageCards.begin(), this->storageCards.end(), card), this->storageCards.end());
	this->deckCards.push_back(card);
	GameUtils::changeParent(card, this->deckScrollPane, false);
	
	this->initializeListeners();
	this->initializePositions();
}

void HexusDeckManagement::onDeckCardMouseOver(Card* card)
{
	
}

void HexusDeckManagement::onStorageCardMouseOver(Card* card)
{

}
