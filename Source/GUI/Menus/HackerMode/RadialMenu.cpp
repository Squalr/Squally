#include "RadialMenu.h"

const int RadialMenu::radialMenuRadius = 256;
const Size RadialMenu::maxPreviewSize = Size(340.0f, 340.0f);

RadialMenu* RadialMenu::create()
{
	RadialMenu* radialMenu = new RadialMenu();

	radialMenu->autorelease();

	return radialMenu;
}

RadialMenu::RadialMenu()
{
	this->line = nullptr;
	this->activeHackableObject = nullptr;

	this->radialNode = Node::create();
	this->layerColor = LayerColor::create(Color4B(0, 0, 0, 48));
	this->returnButton = MenuSprite::create(Resources::Menus_HackerModeMenu_Return, Resources::Menus_HackerModeMenu_ReturnHover, Resources::Menus_HackerModeMenu_ReturnClick);

	this->codeMenu = CodeMenu::create();
	this->dataMenu = DataMenu::create();

	this->returnButton->setScale(0.5f);
	this->codeMenu->setVisible(false);
	this->dataMenu->setVisible(false);

	this->addChild(this->layerColor);
	this->addChild(this->returnButton);
	this->addChild(this->radialNode);
	this->addChild(this->codeMenu);
	this->addChild(this->dataMenu);

	this->initializePositions();
	this->initializeListeners();
}

RadialMenu::~RadialMenu()
{
}

void RadialMenu::onHackableEdit(EventCustom* eventArgs)
{
	HackableEvents::HackableObjectEditArgs* args = (HackableEvents::HackableObjectEditArgs*)(eventArgs->getUserData());

	// Set target hackable object
	this->activeHackableObject = args->hackableObject;

	if (this->line != nullptr)
	{
		this->removeChild(this->line);
	}

	this->line = DrawNode::create(2.0f);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	this->line->removeAllChildren();
	this->line->drawLine(args->sourceLocation, visibleSize / 2.0f, Color4F(Color4B(86, 214, 156, 96)));
	this->setVisible(true);

	int hackableCount = this->activeHackableObject->dataList->size() + this->activeHackableObject->codeList->size();
	float step = (3.14159f * 2.0f) / (float)hackableCount;
	float current = 0.0f;

	for (auto it = this->activeHackableObject->dataList->begin(); it != this->activeHackableObject->dataList->end(); it++)
	{
		HackableAttribute* hackableAttribute = *it;

		float x = sin(current) * (float)RadialMenu::radialMenuRadius;
		float y = cos(current) * (float)RadialMenu::radialMenuRadius;

		Sprite* next = Sprite::create(hackableAttribute->iconResource);
		next->setPosition(Vec2(x, y));
		this->radialNode->addChild(next);

		current += step;
	}

	this->addChild(this->line);

	GameUtils::focus(this);
}

void RadialMenu::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->radialNode->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->returnButton->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
}

void RadialMenu::initializeListeners()
{
	this->returnButton->setClickCallback(CC_CALLBACK_1(RadialMenu::onClose, this));

	EventListenerCustom* hackableEditListener = EventListenerCustom::create(HackableEvents::HackableObjectEditEvent, CC_CALLBACK_1(RadialMenu::onHackableEdit, this));
	EventListenerKeyboard* listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(RadialMenu::onKeyPressed, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(hackableEditListener, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void RadialMenu::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (!this->isVisible())
	{
		return;
	}

	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_ESCAPE:
		this->setVisible(false);
		GameUtils::focus(this->getParent());
		event->stopPropagation();
		break;
	}
}

void RadialMenu::onClose(MenuSprite* menuSprite)
{
	this->setVisible(false);
	GameUtils::focus(this->getParent());
}
