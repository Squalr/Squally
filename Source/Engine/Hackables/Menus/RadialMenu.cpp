#include "RadialMenu.h"

#include "cocos/2d/CCDrawNode.h"
#include "cocos/2d/CCLayer.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCInputEvents.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Events/HackableEvents.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Hackables/HackActivatedAbility.h"
#include "Engine/Hackables/HackableBase.h"
#include "Engine/Hackables/HackableObject.h"
#include "Engine/Hackables/Menus/HackablePreview.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Engine/Utils/StrUtils.h"

#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const float RadialMenu::Radius = 372.0f;
const float RadialMenu::IconRadius = 36.0f;

RadialMenu* RadialMenu::create()
{
	RadialMenu* instance = new RadialMenu();

	instance->autorelease();

	return instance;
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

	this->addEventListenerIgnorePause(EventListenerCustom::create(HackableEvents::EventHackableObjectOpen, [=](EventCustom* eventCustom)
	{
		HackableObjectOpenArgs* args = static_cast<HackableObjectOpenArgs*>(eventCustom->getData());

		if (args != nullptr)
		{
			this->setVisible(true);

			this->activeHackableObject = args->hackableObject;
			this->buildRadialMenu(args);

			GameUtils::focus(this);
		}
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(HackableEvents::EventHackableBaseEditDone, [=](EventCustom* EventCustom)
	{
		GameUtils::focus(this);

		// Just close out of this when finished editing an hackable
		this->close();
	}));

	this->whenKeyPressed({ InputEvents::KeyCode::KEY_TAB, InputEvents::KeyCode::KEY_ESCAPE }, [=](InputEvents::KeyboardEventArgs* args)
	{
		if (!GameUtils::isVisible(this))
		{
			return;
		}
		
		args->handle();

		this->close();
	});
}

void RadialMenu::onHackableEdit(HackableBase* hackable)
{
	if (dynamic_cast<HackActivatedAbility*>(hackable) != nullptr)
	{
		dynamic_cast<HackActivatedAbility*>(hackable)->activate();
		HackableEvents::TriggerEditHackableBaseDone();
	}
	else
	{
		HackableEvents::TriggerEditHackableBaseEdit(HackableObjectEditArgs(this->activeHackableObject, hackable));

		this->setVisible(false);
	}
}

void RadialMenu::close()
{
	this->setVisible(false);

	HackableEvents::TriggerCloseHackable();
	HackableEvents::TriggerHackerModeDisable();
}

void RadialMenu::buildRadialMenu(HackableObjectOpenArgs* args)
{
	this->previewNode->removeAllChildren();
	this->radialMenuItems->removeAllChildren();

	HackablePreview* preview = this->activeHackableObject->createDefaultPreview();
	std::vector<HackableBase*> filteredAttributes = std::vector<HackableBase*>();

	for (auto hackable : this->activeHackableObject->hackableList)
	{
		if ((hackable->getRequiredHackFlag() & HackableObject::GetHackFlags()) == hackable->getRequiredHackFlag())
		{
			filteredAttributes.push_back(hackable);
		}
	}
	
	if (preview != nullptr)
	{
		this->previewNode->addChild(preview);
	}

	// +1 from the exit node, which is always present
	float angleStep = (float(M_PI) * 2.0f) / ((float)(filteredAttributes.size() + 1));
	float currentAngle = 3.0f * float(M_PI) / 2.0f;

	// Create return button
	Vec2 nextDataIconPosition = Vec2(-std::cos(currentAngle) * RadialMenu::Radius, std::sin(currentAngle) * RadialMenu::Radius);
	Node* returnRadialNode = this->createRadialNode(UIResources::Menus_Icons_Cross, -1, nextDataIconPosition, currentAngle, Strings::Menus_Exit::create(), [=]() { this->close(); });
	currentAngle = MathUtils::wrappingNormalize(currentAngle + angleStep, 0.0f, 2.0f * float(M_PI));

	this->radialMenuItems->addChild(returnRadialNode);

	// Draw icons
	for (auto hackable : filteredAttributes)
	{
		LocalizedString* name = hackable->getName();

		nextDataIconPosition = Vec2(-std::cos(currentAngle) * RadialMenu::Radius, std::sin(currentAngle) * RadialMenu::Radius);

		ClickableNode* menuNode = this->createRadialNode(
			hackable->getIconResource(),
			hackable->getRequiredHackFlag(),
			nextDataIconPosition,
			currentAngle,
			name == nullptr ? nullptr : name->clone(), 
			[=]()
			{
				this->onHackableEdit(hackable);
			}
		);

		if (!hackable->isCooldownComplete())
		{
			menuNode->disableInteraction(127);
		}

		this->radialMenuItems->addChild(menuNode);

		currentAngle = MathUtils::wrappingNormalize(currentAngle + angleStep, 0.0f, 2.0f * float(M_PI));
	}
}

ClickableNode* RadialMenu::createRadialNode(std::string iconResource, int requiredHackFlag, Vec2 nodePosition, float angle, LocalizedString* text, std::function<void()> clickCallback)
{
	const Size padding = Size(4.0f, 0.0f);

	Sprite* radialNodeIcon = Sprite::create(iconResource);
	ClickableNode* clickableNode = ClickableNode::create(Node::create(), Node::create());
	Node* labelNode = Node::create();
	LocalizedLabel* label = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, text);
	LayerColor* labelBackground = LayerColor::create(Color4B(0, 0, 0, 196), label->getContentSize().width + padding.width * 2.0f, label->getContentSize().height + padding.height * 2.0f);

	clickableNode->setContentSize(Size(RadialMenu::IconRadius * 2.0f, RadialMenu::IconRadius * 2.0f));

	clickableNode->setMouseClickCallback([=](InputEvents::MouseEventArgs*) {	clickCallback(); });
	clickableNode->setMouseOverCallback([=](InputEvents::MouseEventArgs*) {	label->setTextColor(Color4B::YELLOW); });
	clickableNode->setMouseOutCallback([=](InputEvents::MouseEventArgs*) {	label->setTextColor(Color4B::WHITE); });

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

	clickableNode->setPosition(nodePosition);

	labelNode->addChild(labelBackground);
	labelNode->addChild(label);

	clickableNode->addChild(radialNodeIcon);
	clickableNode->addChild(labelNode);
	
	/*
	if ((requiredHackFlag & this->hackFlags) != requiredHackFlag)
	{
		LocalizedLabel* requiredEqLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_Hacking_RadialMenu_RequiresEq::create());

		requiredEqLabel->setStringReplacementVariables(ConstantString::create(std::to_string(requiredHackFlag)));

		LayerColor* requiredEqBackground = LayerColor::create(Color4B(0, 0, 0, 196), requiredEqLabel->getContentSize().width + padding.width * 2.0f, requiredEqLabel->getContentSize().height + padding.height * 2.0f);

		requiredEqLabel->enableOutline(Color4B::BLACK, 2);
		requiredEqLabel->setTextColor(Color4B::RED);

		requiredEqBackground->setPosition(Vec2(-requiredEqLabel->getContentSize().width * requiredEqLabel->getAnchorPoint().x, -requiredEqLabel->getContentSize().height / 2.0f) - padding);

		clickableNode->addChild(requiredEqBackground);
		clickableNode->addChild(requiredEqLabel);
		

		clickableNode->disableInteraction();
	}*/

	return clickableNode;
}
