#include "RadialMenu.h"

const float RadialMenu::radialMenuRadius = 192.0f;
const float RadialMenu::iconRadius = 36.0f;
const float RadialMenu::lineWidth = 2.0f;
const Color4F RadialMenu::lineColor = Color4F(Color4B(86, 214, 156, 96));
const Color4F RadialMenu::dataColor = Color4F(Color4B(86, 214, 156, 96));
const Color4F RadialMenu::codeColor = Color4F(Color4B(181, 206, 168, 96));

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

	this->returnButton->setScale(0.5f);
	this->codeEditor->setVisible(false);

	this->addChild(this->layerColor);
	this->addChild(this->returnButton);
	this->addChild(this->radialNode);
	this->addChild(this->codeEditor);

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

	line->drawLine(args->sourceLocation - Director::getInstance()->getVisibleSize() / 2.0f, Vec2::ZERO, RadialMenu::lineColor);
	
	this->radialNode->addChild(line);

	float dataAngleStep = (3.14159f * 2.0f) / (float)this->activeHackableObject->dataList->size();
	float currentDataAngle = 0.0f;

	for (auto it = this->activeHackableObject->dataList->begin(); it != this->activeHackableObject->dataList->end(); it++)
	{
		HackableData* hackableData = *it;

		float codeAngleStep = hackableData->codeList->size() <= 1 ? 0.0f : ((3.14159f * 2.0f) / ((float)(hackableData->codeList->size() - 1))) / 3.0f;
		float currentCodeAngle = currentDataAngle - (3.14159f / 3.0f);

		Node* dataNode = Node::create();

		// Draw code icons
		for (auto it = hackableData->codeList->begin(); it != hackableData->codeList->end(); it++)
		{
			HackableCode* hackableCode = *it;

			Vec2 nextCodeIconPosition = Vec2(sin(currentCodeAngle) * RadialMenu::radialMenuRadius, cos(currentCodeAngle) * RadialMenu::radialMenuRadius);
			Vec2 nextCodeLineEndPosition = Vec2(sin(currentCodeAngle) * (RadialMenu::radialMenuRadius - RadialMenu::iconRadius), cos(currentCodeAngle) * (RadialMenu::radialMenuRadius - RadialMenu::iconRadius));
			DrawNode* nextCodeIconLine = DrawNode::create(RadialMenu::lineWidth);
			DrawNode* nextCodeIconBack = DrawNode::create(RadialMenu::lineWidth);
			nextCodeIconBack->drawCircle(Vec2::ZERO, RadialMenu::iconRadius, 0.0f, 48, false, RadialMenu::codeColor);

			Sprite* nextCodeIcon = Sprite::create(hackableCode->iconResource);
			Node* clickableNode = Node::create();
			clickableNode->setContentSize(Size(RadialMenu::iconRadius * 2.0f, RadialMenu::iconRadius * 2.0f));
			MenuSprite* nextCodeMenuSprite = MenuSprite::create(clickableNode, Node::create(), Node::create());

			nextCodeIconLine->drawLine(Vec2::ZERO, nextCodeLineEndPosition, RadialMenu::lineColor);
			nextCodeIconBack->setPosition(nextCodeIconPosition);
			nextCodeIcon->setPosition(nextCodeIconPosition);
			nextCodeMenuSprite->setPosition(nextCodeIconPosition);

			nextCodeMenuSprite->setTag((int)hackableCode);
			nextCodeMenuSprite->setClickCallback(CC_CALLBACK_1(RadialMenu::onHackableAttributeClick, this));

			dataNode->addChild(nextCodeIconLine);
			dataNode->addChild(nextCodeIconBack);
			dataNode->addChild(nextCodeIcon);
			dataNode->addChild(nextCodeMenuSprite);

			currentCodeAngle += codeAngleStep;
		}

		Vec2 nextDataIconPosition = Vec2(sin(currentDataAngle) * RadialMenu::radialMenuRadius, cos(currentDataAngle) * RadialMenu::radialMenuRadius);
		Vec2 nextDataLineEndPosition = Vec2(sin(currentDataAngle) * (RadialMenu::radialMenuRadius - RadialMenu::iconRadius), cos(currentDataAngle) * (RadialMenu::radialMenuRadius - RadialMenu::iconRadius));
		DrawNode* nextDataIconLine = DrawNode::create(RadialMenu::lineWidth);
		DrawNode* nextDataIconBack = DrawNode::create(RadialMenu::lineWidth);
		nextDataIconBack->drawCircle(Vec2::ZERO, RadialMenu::iconRadius, 0.0f, 48, false, RadialMenu::dataColor);

		Sprite* nextDataIcon = Sprite::create(hackableData->iconResource);
		Node* clickableNode = Node::create();
		clickableNode->setContentSize(Size(RadialMenu::iconRadius * 2.0f, RadialMenu::iconRadius * 2.0f));
		MenuSprite* nextDataMenuSprite = MenuSprite::create(clickableNode, Node::create(), Node::create());

		dataNode->setPosition(nextDataIconPosition);
		nextDataIconLine->drawLine(Vec2::ZERO, nextDataLineEndPosition, RadialMenu::lineColor);
		nextDataIconBack->setPosition(nextDataIconPosition);
		nextDataIcon->setPosition(nextDataIconPosition);
		nextDataMenuSprite->setPosition(nextDataIconPosition);

		nextDataMenuSprite->setTag((int)hackableData);
		nextDataMenuSprite->setClickCallback(CC_CALLBACK_1(RadialMenu::onHackableAttributeClick, this));

		this->radialNode->addChild(dataNode);
		this->radialNode->addChild(nextDataIconLine);
		this->radialNode->addChild(nextDataIconBack);
		this->radialNode->addChild(nextDataIcon);
		this->radialNode->addChild(nextDataMenuSprite);

		currentDataAngle += dataAngleStep;
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
