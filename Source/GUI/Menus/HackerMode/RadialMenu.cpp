#include "RadialMenu.h"

const float RadialMenu::radialMenuRadius = 192.0f;
const float RadialMenu::iconRadius = 36.0f;
const float RadialMenu::lineWidth = 2.0f;
const Color4F RadialMenu::dataColor = Color4F(Color4B(86, 214, 156, 96));
const Color4F RadialMenu::codeColor = Color4F(Color4B(173, 90, 173, 96));

RadialMenu* RadialMenu::create(std::function<void()> onCloseCallback)
{
	RadialMenu* instance = new RadialMenu(onCloseCallback);

	instance->autorelease();

	return instance;
}

RadialMenu::RadialMenu(std::function<void()> onCloseCallback)
{
	this->activeHackableObject = nullptr;
	this->onRadialMenuCloseCallback = onCloseCallback;

	this->radialMenuItems = Node::create();
	this->layerColor = LayerColor::create(Color4B(0, 0, 0, 48));

	this->codeEditor = CodeEditor::create();

	this->codeEditor->setVisible(false);

	this->addChild(this->layerColor);
	this->addChild(this->radialMenuItems);
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

	this->radialMenuItems->removeAllChildren();

	float dataAngleStep = (3.14159f * 2.0f) / (float)this->activeHackableObject->dataList->size();
	float currentDataAngle = 0.0f;

	Node* rootNode = Node::create();
	Vec2 rootLocation = args->sourceLocation - Director::getInstance()->getVisibleSize() / 2.0f;
	rootNode->setPosition(rootLocation);

	Node* returnRadialNode = this->createRadialNode(Resources::Menus_HackerModeMenu_Icons_Cross, -rootLocation, RadialMenu::dataColor, CC_CALLBACK_1(RadialMenu::onClose, this), 0);
	
	rootNode->addChild(returnRadialNode);

	for (auto it = this->activeHackableObject->dataList->begin(); it != this->activeHackableObject->dataList->end(); it++)
	{
		HackableData* hackableData = *it;

		float codeAngleStep = hackableData->codeList->size() <= 1 ? 0.0f : ((3.14159f * 2.0f) / ((float)(hackableData->codeList->size() - 1))) / 3.0f;
		float currentCodeAngle = currentDataAngle - (3.14159f / 3.0f);

		Vec2 nextDataIconPosition = Vec2(sin(currentDataAngle) * RadialMenu::radialMenuRadius, cos(currentDataAngle) * RadialMenu::radialMenuRadius);
		Node* dataNode = this->createRadialNode(hackableData->iconResource, nextDataIconPosition, RadialMenu::dataColor, CC_CALLBACK_1(RadialMenu::onHackableAttributeClick, this), (int)hackableData);

		// Draw code icons
		for (auto it = hackableData->codeList->begin(); it != hackableData->codeList->end(); it++)
		{
			HackableCode* hackableCode = *it;
			Vec2 codeNodePosition = Vec2(sin(currentCodeAngle) * RadialMenu::radialMenuRadius, cos(currentCodeAngle) * RadialMenu::radialMenuRadius);
			Node* codeNode = this->createRadialNode(hackableCode->iconResource, codeNodePosition, RadialMenu::codeColor, CC_CALLBACK_1(RadialMenu::onHackableAttributeClick, this), (int)hackableCode);

			dataNode->addChild(codeNode);
			currentCodeAngle += codeAngleStep;
		}

		returnRadialNode->addChild(dataNode);
		currentDataAngle += dataAngleStep;
	}

	this->radialMenuItems->addChild(rootNode);

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

	this->radialMenuItems->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
}

void RadialMenu::initializeListeners()
{
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
	GameUtils::focus(this->getParent());

	if (this->onRadialMenuCloseCallback != nullptr)
	{
		this->onRadialMenuCloseCallback();
	}
}

Node* RadialMenu::createRadialNode(std::string iconResource, Vec2 nodePosition, Color4F color, std::function<void(MenuSprite*, EventMouse* args)> callback, int tag)
{
	DrawNode* radialNode = DrawNode::create(RadialMenu::lineWidth);
	DrawNode* line = DrawNode::create();
	Sprite* radialNodeIcon = Sprite::create(iconResource);
	Node* clickableNode = Node::create();
	clickableNode->setContentSize(Size(RadialMenu::iconRadius * 2.0f, RadialMenu::iconRadius * 2.0f));
	MenuSprite* radialNodeClickableSprite = MenuSprite::create(clickableNode, Node::create(), Node::create());

	line->drawLine(Vec2::ZERO, -nodePosition, color);
	radialNode->drawCircle(Vec2::ZERO, RadialMenu::iconRadius, 0.0f, 64, false, color);
	radialNodeClickableSprite->setTag(tag);
	radialNodeClickableSprite->setClickCallback(callback);

	radialNode->setPosition(nodePosition);
	radialNode->addChild(radialNodeIcon);
	radialNode->addChild(radialNodeClickableSprite);
	radialNode->addChild(line);

	return radialNode;
}
