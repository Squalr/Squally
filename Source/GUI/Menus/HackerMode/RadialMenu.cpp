#include "RadialMenu.h"

const int RadialMenu::radialMenuRadius = 256;
const Size RadialMenu::maxPreviewSize = Size(340.0f, 340.0f);

RadialMenu* RadialMenu::create(std::function<void()> onCloseCallback)
{
	RadialMenu* radialMenu = new RadialMenu(onCloseCallback);

	radialMenu->autorelease();

	return radialMenu;
}

RadialMenu::RadialMenu(std::function<void()> onCloseCallback)
{
	this->activeHackableObject = nullptr;
	this->onRadialMenuCloseCallback = onCloseCallback;

	this->radialNode = Node::create();
	this->layerColor = LayerColor::create(Color4B(0, 0, 0, 48));
	this->returnButton = MenuSprite::create(Resources::Menus_HackerModeMenu_Return, Resources::Menus_HackerModeMenu_ReturnHover, Resources::Menus_HackerModeMenu_ReturnClick);

	this->codeEditor = CodeEditor::create();
	this->dataMenu = DataMenu::create();

	this->returnButton->setScale(0.5f);
	this->codeEditor->setVisible(false);
	this->dataMenu->setVisible(false);

	this->addChild(this->layerColor);
	this->addChild(this->returnButton);
	this->addChild(this->radialNode);
	this->addChild(this->codeEditor);
	this->addChild(this->dataMenu);

	this->initializePositions();
	this->initializeListeners();
}

RadialMenu::~RadialMenu()
{
}

void RadialMenu::onHackableEdit(EventCustom* eventArgs)
{
	this->setVisible(true);

	HackableEvents::HackableObjectEditArgs* args = (HackableEvents::HackableObjectEditArgs*)(eventArgs->getUserData());

	// Set target hackable object
	this->activeHackableObject = args->hackableObject;

	DrawNode* line = DrawNode::create(2.0f);

	line->drawLine(args->sourceLocation - Director::getInstance()->getVisibleSize() / 2.0f, Vec2::ZERO, Color4F(Color4B(86, 214, 156, 96)));
	
	this->radialNode->addChild(line);

	std::vector<HackableAttribute*> hackables = std::vector<HackableAttribute*>();

	for (auto it = this->activeHackableObject->dataList->begin(); it != this->activeHackableObject->dataList->end(); it++)
	{
		hackables.push_back(*it);
	}

	for (auto it = this->activeHackableObject->codeList->begin(); it != this->activeHackableObject->codeList->end(); it++)
	{
		hackables.push_back(*it);
	}

	int hackableCount = this->activeHackableObject->dataList->size() + this->activeHackableObject->codeList->size();
	float step = (3.14159f * 2.0f) / (float)hackableCount;
	float current = 0.0f;

	for (auto it = hackables.begin(); it != hackables.end(); it++)
	{
		HackableAttribute* hackableAttribute = *it;

		Vec2 position = Vec2(sin(current) * (float)RadialMenu::radialMenuRadius, cos(current) * (float)RadialMenu::radialMenuRadius);
		DrawNode* nextLine = DrawNode::create(2.0f);
		Sprite* nextBack = Sprite::create(hackableAttribute->iconBackResource);
		Sprite* next = Sprite::create(hackableAttribute->iconResource);
		Node* clickableNode = Node::create();
		clickableNode->setContentSize(nextBack->getContentSize());
		MenuSprite* nextMenuSprite = MenuSprite::create(clickableNode, Node::create(), Node::create());

		nextLine->drawLine(Vec2::ZERO, position, Color4F(Color4B(86, 214, 156, 96)));
		nextBack->setPosition(position);
		next->setPosition(position);
		nextMenuSprite->setPosition(position);

		nextMenuSprite->setTag((int)hackableAttribute);
		nextMenuSprite->setClickCallback(CC_CALLBACK_1(RadialMenu::onHackableAttributeClick, this));

		this->radialNode->addChild(nextLine);
		this->radialNode->addChild(nextBack);
		this->radialNode->addChild(next);
		this->radialNode->addChild(nextMenuSprite);

		current += step;
	}

	GameUtils::focus(this);
}

void RadialMenu::onHackableAttributeClick(MenuSprite* menuSprite)
{
	HackableAttribute* hackableAttribute = (HackableAttribute*)menuSprite->getTag();

	if (dynamic_cast<HackableCode*>(hackableAttribute) != nullptr)
	{
		this->codeEditor->open((HackableCode*)hackableAttribute);
	}

	if (dynamic_cast<HackableData*>(hackableAttribute) != nullptr)
	{
		// this->dataEditor->open((HackableData*)hackableAttribute);
	}
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
		this->close();
		event->stopPropagation();
		break;
	}
}

void RadialMenu::onClose(MenuSprite* menuSprite)
{
	this->close();
}

void RadialMenu::close()
{
	this->setVisible(false);
	this->radialNode->removeAllChildren();
	GameUtils::focus(this->getParent());

	if (this->onRadialMenuCloseCallback != nullptr)
	{
		this->onRadialMenuCloseCallback();
	}
}
