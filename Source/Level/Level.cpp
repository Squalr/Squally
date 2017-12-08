#include "Level.h"
#include "Resources.h"
#include "../Entities/Player.h"

Level::Level()
{
	if (!Scene::init())
	{
		throw std::uncaught_exception();
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	this->backGround = Sprite::create(Resources::Background_GrassBG);
	this->player = new Player();

	this->backGround->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - this->backGround->getContentSize().height / 2));
	this->player->sprite->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));

	this->addChild(this->backGround);
	this->addChild(this->player->sprite);

	this->InitializeListeners();
}


Level::~Level()
{
	delete(this->backGround);
	delete(this->player);
}

void Level::InitializeListeners()
{
	EventListenerKeyboard* listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(Level::onKeyPressed, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

// Implementation of the keyboard event callback function prototype
void Level::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_ESCAPE:
		break;
	}
}
