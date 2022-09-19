#include "ObjectSelectionBehavior.h"

#include "cocos/base/CCInputEvents.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEnemy.h"
#include "Entities/Platformer/PlatformerFriendly.h"
#include "Events/CombatEvents.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string ObjectSelectionBehavior::MapKey = "object-selection";

ObjectSelectionBehavior* ObjectSelectionBehavior::create(GameObject* owner)
{
	ObjectSelectionBehavior* instance = new ObjectSelectionBehavior(owner);

	instance->autorelease();

	return instance;
}

ObjectSelectionBehavior::ObjectSelectionBehavior(GameObject* owner) : super(owner)
{
	if (this->owner == nullptr)
	{
		this->invalidate();
	}

	this->clickHitbox = ClickableNode::create(UIResources::EmptyImage, UIResources::EmptyImage);
	
	this->clickHitbox->setContentSize(this->owner->getContentSize());
	this->clickHitbox->setAnchorPoint(Vec2(0.5f, 0.0f));
	this->clickHitbox->disableInteraction();
	this->clickHitbox->setPosition(Vec2(this->owner->getContentSize() / 2.0f));

	this->addChild(this->clickHitbox);
}

ObjectSelectionBehavior::~ObjectSelectionBehavior()
{
}

void ObjectSelectionBehavior::update(float dt)
{
	super::update(dt);

	Vec3 coords = GameUtils::getWorldCoords3D(this->owner, false);

	if (this->savedWorldCoords != coords)
	{
		this->savedWorldCoords = coords;

		InputEvents::TriggerMouseRequestRefresh();
	}

	if (this->canClickCallback != nullptr && this->clickHitbox != nullptr)
	{
		if (canClickCallback())
		{
			this->clickHitbox->enableInteraction();
		}
		else
		{
			this->clickHitbox->disableInteraction();
		}
	}
}

void ObjectSelectionBehavior::onLoad()
{
	this->scheduleUpdate();
}

void ObjectSelectionBehavior::onDisable()
{
	super::onDisable();
}

void ObjectSelectionBehavior::setObjectClickCallbacks(std::function<void()> onClick, std::function<void()> onMouseOver, std::function<void()> onMouseOut)
{
	this->clickHitbox->enableInteraction();
	this->clickHitbox->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		if (onClick != nullptr)
		{
			onClick();
		}
	});
	this->clickHitbox->setMouseOverCallback([=](InputEvents::MouseEventArgs*)
	{
		if (onMouseOver != nullptr)
		{
			onMouseOver();
		}
	});
	this->clickHitbox->setMouseOutCallback([=](InputEvents::MouseEventArgs*)
	{
		if (onMouseOut != nullptr)
		{
			onMouseOut();
		}
	});
}

void ObjectSelectionBehavior::setClickModifier(InputEvents::KeyCode modifier)
{
	this->clickHitbox->setClickModifier(modifier);
}

void ObjectSelectionBehavior::setClickableCallback(std::function<bool()> canClickCallback)
{
	this->canClickCallback = canClickCallback;
}

void ObjectSelectionBehavior::clearObjectClickCallbacks()
{
	this->clickHitbox->disableInteraction();
	this->clickHitbox->setMouseClickCallback(nullptr);
	this->clickHitbox->setMouseOverCallback(nullptr);
	this->clickHitbox->setMouseOutCallback(nullptr);
}

ClickableNode* ObjectSelectionBehavior::getHitbox()
{
	return this->clickHitbox;
}
