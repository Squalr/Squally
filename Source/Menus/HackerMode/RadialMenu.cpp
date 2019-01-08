#include "RadialMenu.h"

#include "cocos/2d/CCDrawNode.h"
#include "cocos/2d/CCLayer.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCEventListenerKeyboard.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Hackables/HackableAttribute.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Hackables/HackableData.h"
#include "Engine/Hackables/HackableObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Menus/HackerMode/CodeEditor.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const float RadialMenu::DataRadius = 192.0f;
const float RadialMenu::CodeRadius = 320.0f;
const float RadialMenu::IconRadius = 36.0f;
const float RadialMenu::LineWidth = 3.0f;
const Color4F RadialMenu::DataColorFill = Color4F(Color4B(86, 214, 156, 96));
const Color4F RadialMenu::CodeColorFill = Color4F(Color4B(86, 214, 156, 96));
const Color4F RadialMenu::DataColor = Color4F(Color4B(86, 214, 156, 255));
const Color4F RadialMenu::CodeColor = Color4F(Color4B(86, 214, 156, 255));

RadialMenu* RadialMenu::create(std::function<void()> onCloseCallback)
{
	RadialMenu* instance = new RadialMenu(onCloseCallback);

	instance->autorelease();

	return instance;
}

RadialMenu::RadialMenu(std::function<void()> onCloseCallback)
{
	this->onRadialMenuCloseCallback = onCloseCallback;
	this->activeHackableObject = nullptr;

	this->radialMenuItems = Node::create();
	this->layerColor = LayerColor::create(Color4B(0, 0, 0, 48));
	this->codeEditor = CodeEditor::create();

	this->codeEditor->setVisible(false);

	this->addChild(this->layerColor);
	this->addChild(this->radialMenuItems);
	this->addChild(this->codeEditor);
}

RadialMenu::~RadialMenu()
{
}

void RadialMenu::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->radialMenuItems->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
}

void RadialMenu::initializeListeners()
{
	super::initializeListeners();

	EventListenerCustom* hackableEditListener = EventListenerCustom::create(HackableEvents::HackableObjectEditEvent, CC_CALLBACK_1(RadialMenu::onHackableEdit, this));
	EventListenerKeyboard* keyboardListener = EventListenerKeyboard::create();

	keyboardListener->onKeyPressed = CC_CALLBACK_2(RadialMenu::onKeyPressed, this);

	this->addEventListener(hackableEditListener);
	this->addEventListener(keyboardListener);
}

void RadialMenu::onHackableEdit(EventCustom* eventArgs)
{
	HackableEvents::HackableObjectEditArgs* args = (HackableEvents::HackableObjectEditArgs*)(eventArgs->getUserData());

	this->setVisible(true);

	this->activeHackableObject = args->hackableObject;
	this->buildRadialMenu(args);

	GameUtils::focus(this);
}

void RadialMenu::onHackableCodeClick(HackableCode* hackableCode)
{
	this->codeEditor->open(hackableCode);
}

void RadialMenu::onHackableDataClick(HackableData* hackableData)
{
	// this->dataEditor->open(hackableData);
}

void RadialMenu::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (!GameUtils::isVisible(this))
	{
		return;
	}

	switch (keyCode)
	{
		case EventKeyboard::KeyCode::KEY_TAB:
		case EventKeyboard::KeyCode::KEY_ESCAPE:
		{
			this->close();
			event->stopPropagation();
			break;
		}
		default:
		{
			break;
		}
	}
}

void RadialMenu::close()
{
	this->setVisible(false);
	GameUtils::focus(this->getParent());
	HackableEvents::TriggerEditHackableDone();

	if (this->onRadialMenuCloseCallback != nullptr)
	{
		this->onRadialMenuCloseCallback();
	}
}

void RadialMenu::buildRadialMenu(HackableEvents::HackableObjectEditArgs* args)
{
	this->radialMenuItems->removeAllChildren();

	float dataAngleStep = (3.14159f * 2.0f) / (float)this->activeHackableObject->dataList.size();
	float codeAngleStep = (3.14159f * 2.0f) / (float)this->activeHackableObject->codeList.size();
	float currentCodeAngle = 0.0f;
	float currentDataAngle = 0.0f;

	// Create root node to hold everything else
	Node* rootNode = Node::create();
	Vec2 rootLocation = args->sourceLocation - Director::getInstance()->getVisibleSize() / 2.0f;
	
	rootNode->setPosition(rootLocation);

	// Create return button
	Node* returnRadialNode = this->createRadialNode(UIResources::Menus_Icons_Cross, -rootLocation, RadialMenu::DataColor, true, [=]() { this->close(); });

	rootNode->addChild(returnRadialNode);

	// Draw rings
	DrawNode* dataRing = DrawNode::create(RadialMenu::LineWidth);
	DrawNode* codeRing = DrawNode::create(RadialMenu::LineWidth);

	// SmartAnimationSequenceNode* radialBackground = SmartAnimationSequenceNode::create(UIResources::Menus_HackerModeMenu_Radial_RadialEye);

	// radialBackground->playAnimationRepeat(UIResources::Menus_HackerModeMenu_Radial_images_RadialAnimation_01, 0.05f, 0.0f);

	//dataRing->drawCircle(Vec2::ZERO, RadialMenu::DataRadius, 0.0f, 64, false, RadialMenu::DataColor);
	codeRing->drawSolidCircle(Vec2::ZERO, RadialMenu::CodeRadius, 0.0f, 64, RadialMenu::CodeColorFill);
	codeRing->drawCircle(Vec2::ZERO, RadialMenu::CodeRadius, 0.0f, 64, false, RadialMenu::CodeColor);

	// returnRadialNode->addChild(radialBackground);
	returnRadialNode->addChild(dataRing);
	returnRadialNode->addChild(codeRing);

	// Draw data icons
	for (auto it = this->activeHackableObject->dataList.begin(); it != this->activeHackableObject->dataList.end(); it++)
	{
		HackableData* hackableData = *it;

		Vec2 nextDataIconPosition = Vec2(std::sin(currentDataAngle) * RadialMenu::DataRadius, cos(currentDataAngle) * RadialMenu::DataRadius);
		Node* dataNode = this->createRadialNode(hackableData->getIconResource(), nextDataIconPosition, RadialMenu::DataColor, false, [=]() { this->onHackableDataClick(hackableData); });

		returnRadialNode->addChild(dataNode);
		currentDataAngle += dataAngleStep;
	}

	// Draw code icons
	for (auto it = this->activeHackableObject->codeList.begin(); it != this->activeHackableObject->codeList.end(); it++)
	{
		HackableCode* hackableCode = *it;
		Vec2 codeNodePosition = Vec2(std::sin(currentCodeAngle) * RadialMenu::CodeRadius, cos(currentCodeAngle) * RadialMenu::CodeRadius);
		Node* codeNode = this->createRadialNode(hackableCode->getIconResource(), codeNodePosition, RadialMenu::CodeColor, false, [=]() { this->onHackableCodeClick(hackableCode); });

		returnRadialNode->addChild(codeNode);
		currentDataAngle += codeAngleStep;
	}

	this->radialMenuItems->addChild(rootNode);
}

Node* RadialMenu::createRadialNode(std::string iconResource, Vec2 nodePosition, Color4F color, bool drawLine, std::function<void()> clickCallback)
{
	DrawNode* radialNode = DrawNode::create(RadialMenu::LineWidth);
	Sprite* radialNodeIcon = Sprite::create(iconResource);
	Node* clickableNode = Node::create();

	clickableNode->setContentSize(Size(RadialMenu::IconRadius * 2.0f, RadialMenu::IconRadius * 2.0f));
	ClickableNode* radialNodeClickableSprite = ClickableNode::create(UIResources::Menus_HackerModeMenu_Radial_LanternDark, UIResources::Menus_HackerModeMenu_Radial_Lantern);

	// radialNode->drawCircle(Vec2::ZERO, RadialMenu::IconRadius, 0.0f, 64, false, color);
	radialNodeClickableSprite->setClickCallback([=](ClickableNode* menuSprite, MouseEvents::MouseEventArgs* args)
	{
		clickCallback();
	});

	radialNode->setPosition(nodePosition);
	radialNode->addChild(radialNodeClickableSprite);
	radialNode->addChild(radialNodeIcon);

	if (drawLine)
	{
		DrawNode* line = DrawNode::create(RadialMenu::LineWidth);
		line->drawLine(Vec2::ZERO, -nodePosition, color);
		radialNode->addChild(line);
	}

	return radialNode;
}
