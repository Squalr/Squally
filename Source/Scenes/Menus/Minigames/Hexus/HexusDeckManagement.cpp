#include "HexusDeckManagement.h"

HexusDeckManagement * HexusDeckManagement::create()
{
	HexusDeckManagement* instance = new HexusDeckManagement();

	instance->autorelease();

	return instance;
}

HexusDeckManagement::HexusDeckManagement()
{
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
	FadeScene::onEnter();

	float delay = 0.25f;
	float duration = 0.35f;

	this->loadStorageCards();
	this->loadDeckCards();
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
}

void HexusDeckManagement::initializeListeners()
{
	FadeScene::initializeListeners();

	EventListenerKeyboard* keyboardListener = EventListenerKeyboard::create();

	keyboardListener->onKeyPressed = CC_CALLBACK_2(HexusDeckManagement::onKeyPressed, this);
	
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);
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
	std::vector<CardData*> storageCards = CardStorage::getStorageCards();

	int index = 0;

	for (auto it = storageCards.begin(); it != storageCards.end(); it++)
	{
		int x = index % 3;
		int y = index / 3;

		Card* card = Card::create(Card::CardStyle::Earth, *it);
		this->storageScrollPane->addChild(card);

		card->setPosition(Vec2(x * 256.0f, y * 256.0f));
	}

	storageScrollPane->fitSizeToContent();
}

void HexusDeckManagement::loadDeckCards()
{
	std::vector<CardData*> deckCards = CardStorage::getDeckCards();

	int index = 0;

	for (auto it = deckCards.begin(); it != deckCards.end(); it++)
	{
		int x = index % 3;
		int y = index / 3;

		Card* card = Card::create(Card::CardStyle::Earth, *it);
		card->reveal();
		card->setScale(0.6f);

		this->deckScrollPane->addChild(card);

		Size paneSize = this->deckScrollPane->getContentSize();
		card->setPosition(Vec2(paneSize.width / 2.0f + (x - 1) * 240.0f, y * 320.0f + 256.0f));

		index++;
	}

	deckScrollPane->fitSizeToContent();
}
