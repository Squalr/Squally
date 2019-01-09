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
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Utils/GameUtils.h"
#include "Menus/HackerMode/CodeEditor.h"

#include "Resources/UIResources.h"

#include "Strings/Menus/Exit.h"
#include "Engine/Utils/MathUtils.h"

using namespace cocos2d;

const float RadialMenu::DataRadius = 192.0f;
const float RadialMenu::CodeRadius = 320.0f;
const float RadialMenu::IconRadius = 36.0f;
const float RadialMenu::LineWidth = 3.0f;
const Color4F RadialMenu::DataColorFill = Color4F(Color4B(25, 242, 51, 96));
const Color4F RadialMenu::CodeColorFill = Color4F(Color4B(25, 242, 51, 96));
const Color4F RadialMenu::DataColor = Color4F(Color4B(25, 242, 51, 255));
const Color4F RadialMenu::CodeColor = Color4F(Color4B(25, 242, 51, 255));

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

	// +1 from the exit node, which is always present
	float angleStep = (3.14159f * 2.0f) / ((float)(this->activeHackableObject->dataList.size() + this->activeHackableObject->codeList.size() + 1));
	float currentAngle = 3.0f * M_PI / 2.0f;

	Node* rootNode = Node::create();
	Node* centralNode = Node::create();
	Vec2 rootLocation = args->sourceLocation - Director::getInstance()->getVisibleSize() / 2.0f;

	rootNode->setPosition(rootLocation);
	centralNode->setPosition(-rootLocation);

	rootNode->addChild(centralNode);

	// Draw rings
	DrawNode* dataRing = DrawNode::create(RadialMenu::LineWidth);
	DrawNode* codeRing = DrawNode::create(RadialMenu::LineWidth);

	// SmartAnimationSequenceNode* radialBackground = SmartAnimationSequenceNode::create(UIResources::Menus_HackerModeMenu_Radial_RadialEye);

	// radialBackground->playAnimationRepeat(UIResources::Menus_HackerModeMenu_Radial_images_RadialAnimation_01, 0.05f, 0.0f);

	//dataRing->drawCircle(Vec2::ZERO, RadialMenu::DataRadius, 0.0f, 64, false, RadialMenu::DataColor);
	codeRing->drawSolidCircle(Vec2::ZERO, RadialMenu::CodeRadius, 0.0f, 64, RadialMenu::CodeColorFill);
	codeRing->drawCircle(Vec2::ZERO, RadialMenu::CodeRadius, 0.0f, 64, false, RadialMenu::CodeColor);

	// Create return button
	Vec2 nextDataIconPosition = Vec2(std::cos(currentAngle) * RadialMenu::CodeRadius, std::sin(currentAngle) * RadialMenu::CodeRadius);
	Node* returnRadialNode = this->createRadialNode(UIResources::Menus_Icons_Cross, nextDataIconPosition, currentAngle, Strings::Menus_Exit::create(), RadialMenu::DataColor, false, [=]() { this->close(); });
	currentAngle = MathUtils::wrappingNormalize(currentAngle + angleStep, 0.0f, 2.0f * M_PI);

	// returnRadialNode->addChild(radialBackground);
	centralNode->addChild(dataRing);
	centralNode->addChild(codeRing);
	centralNode->addChild(returnRadialNode);


	// Draw data icons
	for (auto it = this->activeHackableObject->hackableList.begin(); it != this->activeHackableObject->hackableList.end(); it++)
	{
		HackableAttribute* hackable = *it;

		nextDataIconPosition = Vec2(std::cos(currentAngle) * RadialMenu::CodeRadius, std::sin(currentAngle) * RadialMenu::CodeRadius);

		if (dynamic_cast<HackableData*>(hackable) != nullptr)
		{
			Node* dataNode = this->createRadialNode(hackable->getIconResource(), nextDataIconPosition, currentAngle, hackable->getName(), RadialMenu::DataColor, false, [=]() { this->onHackableDataClick((HackableData*)hackable); });
			centralNode->addChild(dataNode);
		}
		else
		{
			Node* codeNode = this->createRadialNode(hackable->getIconResource(), nextDataIconPosition, currentAngle, hackable->getName(), RadialMenu::DataColor, false, [=]() { this->onHackableCodeClick((HackableCode*)hackable); });
			centralNode->addChild(codeNode);
		}

		currentAngle = MathUtils::wrappingNormalize(currentAngle + angleStep, 0.0f, 2.0f * M_PI);
	}

	this->radialMenuItems->addChild(rootNode);
}

Node* RadialMenu::createRadialNode(std::string iconResource, Vec2 nodePosition, float angle, LocalizedString* text, Color4F color, bool drawLine, std::function<void()> clickCallback)
{
	const Size padding = Size(4.0f, 4.0f);
	DrawNode* radialNode = DrawNode::create(RadialMenu::LineWidth);
	Sprite* radialNodeIcon = Sprite::create(iconResource);
	ClickableNode* clickableNode = ClickableNode::create(Node::create(), Node::create());
	Node* labelNode = Node::create();
	LocalizedLabel* label = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, text);
	LayerColor* labelBackground = LayerColor::create(Color4B(0, 0, 0, 196), label->getContentSize().width + padding.width * 2.0f, label->getContentSize().height + padding.height * 2.0f);

	labelBackground->setPosition(Vec2(-label->getContentSize().width / 2.0f - padding.width, -label->getContentSize().height / 2.0f - padding.height));

	clickableNode->setContentSize(Size(RadialMenu::IconRadius * 2.0f, RadialMenu::IconRadius * 2.0f));
	//ClickableNode* radialNodeClickableSprite = ClickableNode::create(UIResources::Menus_HackerModeMenu_Radial_LanternDark, UIResources::Menus_HackerModeMenu_Radial_Lantern);

	// radialNode->drawCircle(Vec2::ZERO, RadialMenu::IconRadius, 0.0f, 64, false, color);
	clickableNode->setClickCallback([=](ClickableNode* menuSprite, MouseEvents::MouseEventArgs* args)
	{
		clickCallback();
	});

	clickableNode->setMouseOverCallback([=](ClickableNode* menuSprite, MouseEvents::MouseEventArgs* args)
	{
		label->setTextColor(Color4B::YELLOW);
	});

	clickableNode->setMouseOutCallback([=](ClickableNode* menuSprite, MouseEvents::MouseEventArgs* args)
	{
		label->setTextColor(Color4B::WHITE);
	});

	const float tolerance = M_PI / 64.0f;
	const float offset = 48.0f;

	// Handle the main cardinal directions
	if (MathUtils::fuzzyEquals(angle, M_PI / 2.0f, tolerance))
	{
		labelNode->setPosition(Vec2(0.0f, offset));
	}
	else if (MathUtils::fuzzyEquals(angle, 3.0f * M_PI / 2.0f, tolerance))
	{
		labelNode->setPosition(Vec2(0.0f, -offset));
	}
	else if (MathUtils::fuzzyEquals(angle, M_PI, tolerance))
	{
		labelNode->setPosition(Vec2(-offset, 0.0f));
		label->setAnchorPoint(Vec2(1.0f, 0.5f));
	}
	else if (MathUtils::fuzzyEquals(angle, 2.0f * M_PI, tolerance) || MathUtils::fuzzyEquals(angle, 0.0f, tolerance))
	{
		labelNode->setPosition(Vec2(offset, 0.0f));
		label->setAnchorPoint(Vec2(0.0f, 0.5f));
	}
	// Generic cases
	else if (angle < M_PI / 2.0f)
	{
		labelNode->setPosition(Vec2(offset, 0.0f));
		label->setAnchorPoint(Vec2(0.0f, 0.5f));
	}
	else if (angle < M_PI)
	{
		labelNode->setPosition(Vec2(-offset, 0.0f));
		label->setAnchorPoint(Vec2(1.0f, 0.5f));
	}
	else if (angle < M_PI)
	{
		labelNode->setPosition(Vec2(-offset, 0.0f));
		label->setAnchorPoint(Vec2(1.0f, 0.5f));
	}
	else
	{
		labelNode->setPosition(Vec2(offset, 0.0f));
		label->setAnchorPoint(Vec2(0.0f, 0.5f));
	}

	labelNode->addChild(labelBackground);
	labelNode->addChild(label);

	radialNode->setPosition(nodePosition);
	radialNode->addChild(clickableNode);
	radialNode->addChild(radialNodeIcon);
	radialNode->addChild(labelNode);

	if (drawLine)
	{
		DrawNode* line = DrawNode::create(RadialMenu::LineWidth);
		line->drawLine(Vec2::ZERO, -nodePosition, color);
		radialNode->addChild(line);
	}

	return radialNode;
}
