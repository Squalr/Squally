#include "EntitySelectionBehavior.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Input/ClickableNode.h"
#include "Entities/Platformer/PlatformerEnemy.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/PlatformerFriendly.h"
#include "Events/CombatEvents.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string EntitySelectionBehavior::MapKeyAttachedBehavior = "entity-selection";

EntitySelectionBehavior* EntitySelectionBehavior::create(GameObject* owner, std::string attachedBehaviorArgs)
{
	EntitySelectionBehavior* instance = new EntitySelectionBehavior(owner, attachedBehaviorArgs);

	instance->autorelease();

	return instance;
}

EntitySelectionBehavior::EntitySelectionBehavior(GameObject* owner, std::string attachedBehaviorArgs) : super(owner, attachedBehaviorArgs)
{
	this->entity = static_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}

	this->clickHitbox = ClickableNode::create(UIResources::EmptyImage, UIResources::EmptyImage);

	this->clickHitbox->setContentSize(this->entity->getEntitySize());
	this->clickHitbox->setAnchorPoint(Vec2(0.5f, 0.0f));
	this->clickHitbox->disableInteraction();
	this->clickHitbox->setPosition(Vec2(this->entity->getMovementSize() / 2.0f));

	this->addChild(this->clickHitbox);
}

EntitySelectionBehavior::~EntitySelectionBehavior()
{
}

void EntitySelectionBehavior::initializePositions()
{
}

void EntitySelectionBehavior::onLoad()
{
}

void EntitySelectionBehavior::setEntityClickCallbacks(std::function<void()> onClick, std::function<void()> onMouseOver)
{
	this->clickHitbox->enableInteraction();
	this->clickHitbox->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		onClick();
	});
	this->clickHitbox->setMouseOverCallback([=](InputEvents::MouseEventArgs*)
	{
		onMouseOver();
	});
}

void EntitySelectionBehavior::clearEntityClickCallbacks()
{
	this->clickHitbox->disableInteraction();
	this->clickHitbox->setMouseClickCallback(nullptr);
	this->clickHitbox->setMouseOverCallback(nullptr);
}
