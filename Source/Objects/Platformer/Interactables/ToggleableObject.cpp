#include "ToggleableObject.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Camera/GameCamera.h"
#include "Engine/Utils/GameUtils.h"

#include "Resources/FXResources.h"
#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string ToggleableObject::PropertyIsOn = "is-on";
const std::string ToggleableObject::PropertyIsInteractable = "interactable";

ToggleableObject::ToggleableObject(
	ValueMap& properties,
	InteractType interactType,
	Size size,
	Size cullPadding,
	Vec2 offset,
	LocalizedString* actionStr,
	InputEvents::KeyCode input,
	Color3B interactColor,
	Color4F debugColor,
	bool disableLockDebug) : super(properties, interactType, size, offset, actionStr, input, interactColor, debugColor)
{
	this->cullNode = Node::create();
	this->backOnNode = Node::create();
	this->backOffNode = Node::create();
	this->backNode = Node::create();
	this->onNode = Node::create();
	this->offNode = Node::create();
	this->frontNode = Node::create();

	this->cullPadding = cullPadding;
	this->isToggledOn = false;
	this->isCulled = false;
	this->cooldown = 0.0f;

	this->setContentSize(size);

	this->cullNode->addChild(this->backOnNode);
	this->cullNode->addChild(this->backOffNode);
	this->cullNode->addChild(this->backNode);
	this->cullNode->addChild(this->onNode);
	this->cullNode->addChild(this->offNode);
	this->cullNode->addChild(this->frontNode);
	this->contentNode->addChild(this->cullNode);
}

ToggleableObject::~ToggleableObject()
{
}

void ToggleableObject::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void ToggleableObject::update(float dt)
{
	super::update(dt);
	
	if (this->cooldown > 0.0f)
	{
		this->cooldown -= dt;
	}
	
	this->optimizationHideOffscreenToggleableObject();
}

void ToggleableObject::onInteract(PlatformerEntity* interactingEntity)
{
	super::onInteract(interactingEntity);
	
	if (this->cooldown > 0.0f)
	{
		return;
	}

	this->cooldown = 1.0f;

	this->onToggle();
}

void ToggleableObject::onToggle()
{
	if (this->isOn())
	{
		this->disable();
	}
	else
	{
		this->enable();
	}
}

void ToggleableObject::onEnable()
{
}

void ToggleableObject::onDisable()
{
}

bool ToggleableObject::isOn()
{
	return this->isToggledOn;
}

void ToggleableObject::enable()
{
	if (this->isToggledOn)
	{
		return;
	}

	this->isToggledOn = true;

	this->onEnable();
}

void ToggleableObject::disable()
{
	if (!this->isToggledOn)
	{
		return;
	}

	this->isToggledOn = false;

	this->onDisable();
}

void ToggleableObject::onOptimizationHide()
{
	this->cullNode->setVisible(false);
}

void ToggleableObject::onOptimizationShow()
{
	this->cullNode->setVisible(true);
}

void ToggleableObject::optimizationHideOffscreenToggleableObject()
{
	static const Rect CameraRect = Rect(Vec2::ZERO, Director::getInstance()->getVisibleSize());
	Rect thisRect = GameUtils::getScreenBounds(this, this->cullPadding);

	bool isNotOnScreen = !CameraRect.intersectsRect(thisRect);

	if (this->isCulled != isNotOnScreen)
	{
		this->isCulled = isNotOnScreen;

		if (this->isCulled)
		{
			this->onOptimizationHide();
		}
		else
		{
			this->onOptimizationShow();
		}
	}
}
