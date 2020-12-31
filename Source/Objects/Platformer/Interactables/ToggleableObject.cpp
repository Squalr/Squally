#include "ToggleableObject.h"

#include "cocos/base/CCDirector.h"
#include "cocos/base/CCValue.h"

#include "Engine/Utils/GameUtils.h"

using namespace cocos2d;

const std::string ToggleableObject::PropertyIsOn = "is-on";
const std::string ToggleableObject::PropertyIsOneUse = "is-one-use";
const std::string ToggleableObject::PropertyIsInteractable = "interactable";
const std::string ToggleableObject::PropertySaveKey = "save-key";

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
	this->saveKey = GameUtils::getKeyOrDefault(this->properties, ToggleableObject::PropertySaveKey, Value("")).asString();
	this->cullPadding = cullPadding;
	this->originalToggleValue = GameUtils::getKeyOrDefault(this->properties, ToggleableObject::PropertyIsOn, Value(true)).asBool();
	this->isToggledOn = this->originalToggleValue;
	this->isOneUse = GameUtils::getKeyOrDefault(this->properties, ToggleableObject::PropertyIsOneUse, Value(true)).asBool();
	this->isCulled = false;
	this->cooldown = 0.0f;

	if (GameUtils::getKeyOrDefault(this->properties, ToggleableObject::PropertyIsInteractable, Value(true)).asBool())
	{
		this->setInteractType(InteractType::Input);
	}

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

	// Overwrite default value if we have one saved
	if (!this->saveKey.empty())
	{
		this->isToggledOn = this->loadObjectStateOrDefault(this->saveKey, Value(this->isOn())).asBool();
	}
	
	// Run the events for enable/disable (passing in a flag indicating this is an initialization)
	if (this->isOn())
	{
		this->onEnable(true);
	}
	else
	{
		this->onDisable(true);
	}

	if (this->isOneUse && this->isOn() != this->originalToggleValue)
	{
		this->setInteractType(InteractType::None);
	}
	
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

	if (!this->saveKey.empty())
	{
		this->saveObjectState(this->saveKey, Value(this->isOn()));
	}

	if (this->isOneUse && this->isOn() != this->originalToggleValue)
	{
		this->setInteractType(InteractType::None);
	}
}

void ToggleableObject::onEnable(bool isInit)
{
	this->backOffNode->setVisible(false);
	this->offNode->setVisible(false);
	this->backOnNode->setVisible(true);
	this->onNode->setVisible(true);
}

void ToggleableObject::onDisable(bool isInit)
{
	this->backOffNode->setVisible(true);
	this->offNode->setVisible(true);
	this->backOnNode->setVisible(false);
	this->onNode->setVisible(false);
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

	this->onEnable(true);
}

void ToggleableObject::disable()
{
	if (!this->isToggledOn)
	{
		return;
	}

	this->isToggledOn = false;

	this->onDisable(true);
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
