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

	this->addChild(this->background);
	this->addChild(this->storageScrollPane);
	this->addChild(this->deckScrollPane);
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
}

void HexusDeckManagement::initializePositions()
{
	FadeScene::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->background->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->storageScrollPane->setPosition(Vec2(visibleSize.width / 2.0f - 416.0f - 96.0f, visibleSize.height / 2.0f - 64.0f));
	this->deckScrollPane->setPosition(Vec2(visibleSize.width / 2.0f + 416.0f + 96.0f, visibleSize.height / 2.0f - 64.0f));
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
