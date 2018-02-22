#include "Hud.h"

Hud* Hud::create()
{
	Hud* hud = new Hud();

	hud->autorelease();

	return hud;
}

Hud::Hud()
{
	this->heart = Sprite::create(Resources::HUD_Heart);
	this->healthBarFrame = Sprite::create(Resources::HUD_HealthBarFrame);
	this->dialogNode = Node::create();

	this->addChild(this->healthBarFrame);
	this->addChild(this->heart);
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
	EventListenerCustom* dialogListener = EventListenerCustom::create(DialogMenu::DialogOpenEvent, CC_CALLBACK_1(Hud::onDialogOpen, this));
	EventListenerKeyboard* listener = EventListenerKeyboard::create();

	listener->onKeyPressed = CC_CALLBACK_2(Hud::onKeyPressed, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(dialogListener, this);
}

void Hud::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (Utils::isFocused(this))
	{
		switch (keyCode)
		{
		case EventKeyboard::KeyCode::KEY_TAB:
		case EventKeyboard::KeyCode::KEY_ESCAPE:
			Utils::focus(this->getParent());
			event->stopPropagation();

			break;
		}
	}
}

void Hud::onDialogOpen(EventCustom* event)
{
	DialogMenu::DialogOpenArgs* args = static_cast<DialogMenu::DialogOpenArgs*>(event->getUserData());

	this->dialogNode->removeAllChildren();
	this->dialogNode->addChild(args->dialogMenu);
}
