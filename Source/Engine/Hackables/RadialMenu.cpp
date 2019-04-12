#include "RadialMenu.h"

#include "cocos/2d/CCDrawNode.h"
#include "cocos/2d/CCLayer.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCEventListenerKeyboard.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/GlobalDirector.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Hackables/HackableAttribute.h"
#include "Engine/Hackables/HackableObject.h"
#include "Engine/Hackables/HackablePreview.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"

#include "Resources/UIResources.h"

#include "Strings/Menus/Exit.h"

using namespace cocos2d;

const float RadialMenu::Radius = 372.0f;
const float RadialMenu::IconRadius = 36.0f;
RadialMenu* RadialMenu::instance = nullptr;

void RadialMenu::registerGlobalNode()
{
	if (RadialMenu::instance == nullptr)
	{
		RadialMenu::instance = new RadialMenu();

		RadialMenu::instance->autorelease();

		GlobalDirector::registerGlobalNode(RadialMenu::instance);
	}
}

RadialMenu::RadialMenu()
{
	this->activeHackableObject = nullptr;

	this->layerColor = LayerColor::create(Color4B(0, 0, 0, 48));
	this->background = Sprite::create(UIResources::Menus_HackerModeMenu_Radial_RadialEye);
	this->previewNode = Node::create();
	this->radialMenuItems = Node::create();

	this->setVisible(false);

	this->addChild(this->layerColor);
	this->addChild(this->background);
	this->addChild(this->previewNode);
	this->addChild(this->radialMenuItems);
}

RadialMenu::~RadialMenu()
{
}

void RadialMenu::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->background->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->previewNode->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->radialMenuItems->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
}

void RadialMenu::initializeListeners()
{
	super::initializeListeners();

	EventListenerCustom* hackableOpenListener = EventListenerCustom::create(HackableEvents::HackableObjectOpenEvent, CC_CALLBACK_1(RadialMenu::onHackableOpen, this));
	EventListenerCustom* hackableAttributeEditDoneListener = EventListenerCustom::create(HackableEvents::HackableAttributeEditDoneEvent, [=](EventCustom*) { this->onHackableAttributeEditDone(); });
	EventListenerKeyboard* keyboardListener = EventListenerKeyboard::create();

	keyboardListener->onKeyPressed = CC_CALLBACK_2(RadialMenu::onKeyPressed, this);

	this->addEventListenerIgnorePause(hackableOpenListener);
	this->addEventListenerIgnorePause(hackableAttributeEditDoneListener);
	this->addEventListener(keyboardListener);
}

void RadialMenu::onHackableOpen(EventCustom* eventArgs)
{
	HackableEvents::HackableObjectOpenArgs* args = (HackableEvents::HackableObjectOpenArgs*)(eventArgs->getUserData());

	this->setVisible(true);

	this->activeHackableObject = args->hackableObject;
	this->buildRadialMenu(args);

	GameUtils::focus(this);
}

void RadialMenu::onHackableAttributeEdit(HackableAttribute* attribute)
{
	HackableEvents::TriggerEditHackableAttribute(HackableEvents::HackableObjectEditArgs(attribute));

	this->setVisible(false);
}

void RadialMenu::onHackableAttributeEditDone()
{
	GameUtils::focus(this);

	// Just close out of this when finished editing an attribute
	this->close();
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

	HackableEvents::TriggerCloseHackable();
	HackableEvents::TriggerHackerModeDisable();
}

void RadialMenu::buildRadialMenu(HackableEvents::HackableObjectOpenArgs* args)
{
	this->previewNode->removeAllChildren();
	this->radialMenuItems->removeAllChildren();

	HackablePreview* preview = this->activeHackableObject->createDefaultPreview();

	if (preview != nullptr)
	{
		this->previewNode->addChild(preview);
	}

	// +1 from the exit node, which is always present
	float angleStep = (3.14159f * 2.0f) / ((float)(this->activeHackableObject->dataList.size() + this->activeHackableObject->codeList.size() + 1));
	float currentAngle = 3.0f * float(M_PI) / 2.0f;

	// Create return button
	Vec2 nextDataIconPosition = Vec2(std::cos(currentAngle) * RadialMenu::Radius, std::sin(currentAngle) * RadialMenu::Radius);
	Node* returnRadialNode = this->createRadialNode(UIResources::Menus_Icons_Cross, nextDataIconPosition, currentAngle, Strings::Menus_Exit::create(), [=]() { this->close(); });
	currentAngle = MathUtils::wrappingNormalize(currentAngle + angleStep, 0.0f, 2.0f * float(M_PI));

	this->radialMenuItems->addChild(returnRadialNode);

	// Draw data icons
	for (auto it = this->activeHackableObject->hackableList.begin(); it != this->activeHackableObject->hackableList.end(); it++)
	{
		HackableAttribute* hackable = *it;

		nextDataIconPosition = Vec2(std::cos(currentAngle) * RadialMenu::Radius, std::sin(currentAngle) * RadialMenu::Radius);

		Node* menuNode = this->createRadialNode(
			hackable->getIconResource(),
			nextDataIconPosition,
			currentAngle,
			hackable->getName()->clone(), 
			[=]() { this->onHackableAttributeEdit(hackable); }
		);

		this->radialMenuItems->addChild(menuNode);

		currentAngle = MathUtils::wrappingNormalize(currentAngle + angleStep, 0.0f, 2.0f * float(M_PI));
	}
}

Node* RadialMenu::createRadialNode(std::string iconResource, Vec2 nodePosition, float angle, LocalizedString* text, std::function<void()> clickCallback)
{
	const Size padding = Size(4.0f, 0.0f);

	Node* radialNode = Node::create();
	Sprite* radialNodeIcon = Sprite::create(iconResource);
	ClickableNode* clickableNode = ClickableNode::create(Node::create(), Node::create());
	Node* labelNode = Node::create();
	LocalizedLabel* label = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, text);
	LayerColor* labelBackground = LayerColor::create(Color4B(0, 0, 0, 196), label->getContentSize().width + padding.width * 2.0f, label->getContentSize().height + padding.height * 2.0f);

	clickableNode->setContentSize(Size(RadialMenu::IconRadius * 2.0f, RadialMenu::IconRadius * 2.0f));

	clickableNode->setMouseClickCallback([=](MouseEvents::MouseEventArgs*) {	clickCallback(); });
	clickableNode->setMouseOverCallback([=](MouseEvents::MouseEventArgs*) {	label->setTextColor(Color4B::YELLOW); });
	clickableNode->setMouseOutCallback([=](MouseEvents::MouseEventArgs*) {	label->setTextColor(Color4B::WHITE); });

	const float tolerance = float(M_PI) / 64.0f;
	const float offset = 64.0f;

	// Handle the main cardinal directions
	if (MathUtils::fuzzyEquals(angle, float(M_PI) / 2.0f, tolerance))
	{
		labelNode->setPosition(Vec2(0.0f, offset));
	}
	else if (MathUtils::fuzzyEquals(angle, 3.0f * float(M_PI) / 2.0f, tolerance))
	{
		labelNode->setPosition(Vec2(0.0f, -offset));
	}
	else if (MathUtils::fuzzyEquals(angle, float(M_PI), tolerance))
	{
		labelNode->setPosition(Vec2(-offset, 0.0f));
		label->setAnchorPoint(Vec2(1.0f, 0.5f));
	}
	else if (MathUtils::fuzzyEquals(angle, 2.0f * float(M_PI), tolerance) || MathUtils::fuzzyEquals(angle, 0.0f, tolerance))
	{
		labelNode->setPosition(Vec2(offset, 0.0f));
		label->setAnchorPoint(Vec2(0.0f, 0.5f));
	}
	// Generic cases
	else if (angle < float(M_PI) / 2.0f)
	{
		labelNode->setPosition(Vec2(offset, 0.0f));
		label->setAnchorPoint(Vec2(0.0f, 0.5f));
	}
	else if (angle < float(M_PI))
	{
		labelNode->setPosition(Vec2(-offset, 0.0f));
		label->setAnchorPoint(Vec2(1.0f, 0.5f));
	}
	else if (angle < float(M_PI))
	{
		labelNode->setPosition(Vec2(-offset, 0.0f));
		label->setAnchorPoint(Vec2(1.0f, 0.5f));
	}
	else
	{
		labelNode->setPosition(Vec2(offset, 0.0f));
		label->setAnchorPoint(Vec2(0.0f, 0.5f));
	}

	labelBackground->setPosition(Vec2(-label->getContentSize().width * label->getAnchorPoint().x, -label->getContentSize().height / 2.0f) - padding);

	labelNode->addChild(labelBackground);
	labelNode->addChild(label);

	radialNode->setPosition(nodePosition);
	radialNode->addChild(clickableNode);
	radialNode->addChild(radialNodeIcon);
	radialNode->addChild(labelNode);

	return radialNode;
}
