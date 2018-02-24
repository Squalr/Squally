#include "Hexium.h"

const std::string BinariumGameStartEvent = "hexium_game_start_event";
const std::string BinariumGameEndEvent = "hexium_game_end_event";

Hexium* Hexium::create()
{
	Hexium* hexium = new Hexium();

	hexium->autorelease();

	return hexium;
}

Hexium::Hexium()
{
	this->gameBackground = Sprite::create(Resources::Minigames_Hexium_Gameboard);

	this->addChild(this->gameBackground);
}

Hexium::~Hexium()
{
}

void Hexium::onEnter()
{
	FadeScene::onEnter();

	this->initializePositions();
	this->initializeListeners();
}

void Hexium::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->gameBackground->setPosition(visibleSize.width / 2.0f, visibleSize.height / 2.0f);
}

void Hexium::initializeListeners()
{
	// this->returnButton->setClickCallback(CC_CALLBACK_1(Hexium::onClose, this));

	EventListenerKeyboard* listener = EventListenerKeyboard::create();

	listener->onKeyPressed = CC_CALLBACK_2(Hexium::onKeyPressed, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void Hexium::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_ESCAPE:
		GameUtils::navigateBack();
		event->stopPropagation();
		break;
	}
}

void Hexium::onClose(MenuSprite* menuSprite)
{
	GameUtils::navigateBack();
}
