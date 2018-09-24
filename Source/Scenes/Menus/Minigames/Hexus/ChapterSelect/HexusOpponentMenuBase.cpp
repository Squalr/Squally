#include "HexusOpponentMenuBase.h"

HexusOpponentMenuBase::HexusOpponentMenuBase()
{
	this->opponents = std::vector<HexusOpponentPreview*>();
	this->scrollPane = ScrollPane::create(Size(1536.0f, 960.0f), Color4B(0, 0, 0, 196));
	this->background = Sprite::create(Resources::Menus_MinigamesMenu_Hexus_WoodBackground);

	this->addChild(this->background);
	this->addChild(this->scrollPane);
	this->addChild(Mouse::create());
}

HexusOpponentMenuBase::~HexusOpponentMenuBase()
{
}

void HexusOpponentMenuBase::onEnter()
{
	FadeScene::onEnter();

	float delay = 0.25f;
	float duration = 0.35f;

	GameUtils::fadeInObject(this->scrollPane, delay, duration);
}

void HexusOpponentMenuBase::initializePositions()
{
	FadeScene::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->scrollPane->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));

	Size scrollPaneSize = this->scrollPane->getPaneSize();

	int index = 0;

	for (std::vector<HexusOpponentPreview*>::iterator it = this->opponents.begin(); it != this->opponents.end(); ++it)
	{
		int x = index % 3;
		int y = index / 3;

		if (x == 0)
		{
			(*it)->setPositionX(scrollPaneSize.width / 2.0f - 496.0f);
		}
		else if (x == 1)
		{
			(*it)->setPositionX(scrollPaneSize.width / 2.0f);
		}
		else if (x == 2)
		{
			(*it)->setPositionX(scrollPaneSize.width / 2.0f + 496.0f);
		}

		(*it)->setPositionY(y * 680.0f + 480.0f);

		index++;
	}

	this->scrollPane->fitSizeToContent();
}

void HexusOpponentMenuBase::initializeListeners()
{
	FadeScene::initializeListeners();

	EventListenerKeyboard* keyboardListener = EventListenerKeyboard::create();

	keyboardListener->onKeyPressed = CC_CALLBACK_2(HexusOpponentMenuBase::onKeyPressed, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);
}

void HexusOpponentMenuBase::onMouseOver(HexusOpponentPreview* opponent)
{
}

void HexusOpponentMenuBase::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
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

void HexusOpponentMenuBase::onCloseClick(MenuSprite* menuSprite)
{
	NavigationEvents::navigateBack();
}
