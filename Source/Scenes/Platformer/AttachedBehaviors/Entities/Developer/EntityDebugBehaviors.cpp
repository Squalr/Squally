#include "EntityDebugBehaviors.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Physics/EngineCollisionTypes.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Scenes/Platformer/AttachedBehaviors/Entities/Stats/EntityHealthBehaviorBase.h"
#include "Scenes/Platformer/AttachedBehaviors/Squally/Stats/SquallyHealthBehavior.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string EntityDebugBehaviors::MapKeyAttachedBehavior = "entity-debug";

EntityDebugBehaviors* EntityDebugBehaviors::create(GameObject* owner, std::string attachedBehaviorArgs)
{
	EntityDebugBehaviors* instance = new EntityDebugBehaviors(owner, attachedBehaviorArgs);

	instance->autorelease();

	return instance;
}

EntityDebugBehaviors::EntityDebugBehaviors(GameObject* owner, std::string attachedBehaviorArgs) : super(owner, attachedBehaviorArgs)
{
	this->entity = static_cast<PlatformerEntity*>(owner);
	this->resurrectButton = ClickableNode::create(UIResources::Menus_Icons_Heart, UIResources::Menus_Icons_Heart);
	this->killButton = ClickableNode::create(UIResources::Menus_Icons_Skull, UIResources::Menus_Icons_Skull);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
	
	this->resurrectButton->setVisible(false);
	this->killButton->setVisible(false);

	this->addChild(this->resurrectButton);
	this->addChild(this->killButton);
}

EntityDebugBehaviors::~EntityDebugBehaviors()
{
}

void EntityDebugBehaviors::initializePositions()
{
	super::initializePositions();
	
	this->killButton->setPosition(Vec2(-64.0f, this->entity->getEntitySize().height + this->entity->hoverHeight / 2.0f + 32.0f));
	this->resurrectButton->setPosition(Vec2(64.0f, this->entity->getEntitySize().height + this->entity->hoverHeight / 2.0f + 32.0f));
}

void EntityDebugBehaviors::onDeveloperModeEnable()
{
	super::onDeveloperModeEnable();

	this->resurrectButton->setVisible(true);
	this->killButton->setVisible(true);
}

void EntityDebugBehaviors::onDeveloperModeDisable()
{
	super::onDeveloperModeDisable();

	this->resurrectButton->setVisible(false);
	this->killButton->setVisible(false);
}

void EntityDebugBehaviors::onLoad()
{
	this->resurrectButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		EntityHealthBehaviorBase* health = this->entity->getAttachedBehavior<EntityHealthBehaviorBase>();
		
		health->revive();
	});

	this->killButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		Squally* squally = dynamic_cast<Squally*>(this->entity);
		EntityHealthBehaviorBase* health = this->entity->getAttachedBehavior<EntityHealthBehaviorBase>();

		if (health != nullptr)
		{
			if (squally != nullptr)
			{
				health->killAndRespawn();
			}
			else
			{
				health->kill();
			}
		}
	});
}
