#include "HUD.h"

HUD* HUD::create()
{
	HUD* hud = new HUD();

	hud->autorelease();

	return hud;
}

HUD::HUD()
{
	this->heart = Sprite::create(Resources::HUD_Heart);
	this->healthBarFrame = Sprite::create(Resources::HUD_HealthBarFrame);
	this->dialogNode = Node::create();

	this->hackableObjectsHud = Layer::create();
	this->radialMenu = RadialMenu::create();

	this->radialMenu->setVisible(false);

	this->addChild(this->healthBarFrame);
	this->addChild(this->heart);
	this->addChild(this->dialogNode);
	this->addChild(this->hackableObjectsHud);
	this->addChild(this->radialMenu);

	this->initializeListeners();
}

HUD::~HUD()
{
}

void HUD::onEnter()
{
	Node::onEnter();

	this->initializePositions();
}

void HUD::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->healthBarFrame->setPosition(Vec2(this->heart->getContentSize().width + this->healthBarFrame->getContentSize().width / 2, visibleSize.height - this->heart->getContentSize().height / 2 - 16.0f));
	this->heart->setPosition(Vec2(this->heart->getContentSize().width / 2 + 16.0f, visibleSize.height - this->heart->getContentSize().height / 2 - 16.0f));
}

void HUD::initializeListeners()
{
	EventListenerCustom* dialogListener = EventListenerCustom::create(DialogMenu::DialogOpenEvent, CC_CALLBACK_1(HUD::onDialogOpen, this));
	EventListenerKeyboard* listener = EventListenerKeyboard::create();

	listener->onKeyPressed = CC_CALLBACK_2(HUD::onKeyPressed, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(dialogListener, this);
}

void HUD::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
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

void HUD::registerHackableObject(HackableObject* hackableObject)
{
	if (hackableObject == nullptr)
	{
		return;
	}

	// Create the hackable button for this hackable object
	MenuSprite* hackableMenuButton = MenuSprite::create(Resources::Menus_HackerModeMenu_HackButton, Resources::Menus_HackerModeMenu_HackButtonHover, Resources::Menus_HackerModeMenu_HackButtonClick);
	hackableMenuButton->setClickCallback(CC_CALLBACK_1(HackableObject::onHackableClick, hackableObject));
	hackableObject->bindHackableButton(hackableMenuButton);

	this->hackableObjectsHud->addChild(hackableMenuButton);
}

void HUD::onDialogOpen(EventCustom* event)
{
	DialogMenu::DialogOpenArgs* args = static_cast<DialogMenu::DialogOpenArgs*>(event->getUserData());

	this->dialogNode->removeAllChildren();
	this->dialogNode->addChild(args->dialogMenu);
}
