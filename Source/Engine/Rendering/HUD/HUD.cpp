#include "Hud.h"

Hud* Hud::create()
{
	Hud* instance = new Hud();

	instance->autorelease();

	return instance;
}

Hud::Hud()
{
	this->heart = Sprite::create(Resources::HUD_Heart);
	this->healthBarFrame = Sprite::create(Resources::HUD_HealthBarFrame);
	this->dialogNode = Node::create();

	// this->addChild(this->healthBarFrame);
	// this->addChild(this->heart);
	this->addChild(this->dialogNode);

	this->initializeListeners();
}

Hud::~Hud()
{
}

void Hud::onEnter()
{
	Node::onEnter();

	this->initializePositions();
}

void Hud::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->healthBarFrame->setPosition(Vec2(this->heart->getContentSize().width + this->healthBarFrame->getContentSize().width / 2, visibleSize.height - this->heart->getContentSize().height / 2 - 16.0f));
	this->heart->setPosition(Vec2(this->heart->getContentSize().width / 2 + 16.0f, visibleSize.height - this->heart->getContentSize().height / 2 - 16.0f));
}

void Hud::initializeListeners()
{
	this->getEventDispatcher()->removeEventListenersForTarget(this);

	EventListenerCustom* dialogListener = EventListenerCustom::create(DialogEvents::DialogOpenEvent, CC_CALLBACK_1(Hud::onDialogOpen, this));
	EventListenerKeyboard* keyboardListener = EventListenerKeyboard::create();

	keyboardListener->onKeyPressed = CC_CALLBACK_2(Hud::onKeyPressed, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(dialogListener, this);
}

void Hud::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (GameUtils::isFocused(this))
	{
		switch (keyCode)
		{
		case EventKeyboard::KeyCode::KEY_TAB:
		case EventKeyboard::KeyCode::KEY_ESCAPE:
			GameUtils::focus(this->getParent());
			event->stopPropagation();

			break;
		}
	}
}

void Hud::onDialogOpen(EventCustom* event)
{
	DialogEvents::DialogOpenArgs* args = static_cast<DialogEvents::DialogOpenArgs*>(event->getUserData());

	this->dialogNode->removeAllChildren();
	//this->dialogNode->addChild(args->dialogMenu);
}
