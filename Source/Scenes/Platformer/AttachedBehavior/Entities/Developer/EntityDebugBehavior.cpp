#include "EntityDebugBehavior.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Physics/EngineCollisionTypes.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Stats/EntityHealthBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Squally/Stats/SquallyHealthBehavior.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string EntityDebugBehavior::MapKeyAttachedBehavior = "entity-debug";

EntityDebugBehavior* EntityDebugBehavior::create(GameObject* owner, std::string attachedBehaviorArgs)
{
	EntityDebugBehavior* instance = new EntityDebugBehavior(owner, attachedBehaviorArgs);

	instance->autorelease();

	return instance;
}

EntityDebugBehavior::EntityDebugBehavior(GameObject* owner, std::string attachedBehaviorArgs) : super(owner, attachedBehaviorArgs)
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

EntityDebugBehavior::~EntityDebugBehavior()
{
}

void EntityDebugBehavior::initializePositions()
{
	super::initializePositions();
	
	this->killButton->setPosition(Vec2(-64.0f, this->entity->getEntitySize().height + this->entity->hoverHeight / 2.0f + 32.0f));
	this->resurrectButton->setPosition(Vec2(64.0f, this->entity->getEntitySize().height + this->entity->hoverHeight / 2.0f + 32.0f));
}

void EntityDebugBehavior::onDeveloperModeEnable()
{
	super::onDeveloperModeEnable();

	this->resurrectButton->setVisible(true);
	this->killButton->setVisible(true);
}

void EntityDebugBehavior::onDeveloperModeDisable()
{
	super::onDeveloperModeDisable();

	this->resurrectButton->setVisible(false);
	this->killButton->setVisible(false);
}

void EntityDebugBehavior::onLoad()
{
	this->resurrectButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		EntityHealthBehavior* health = this->entity->getAttachedBehavior<EntityHealthBehavior>();
		
		health->revive();
	});

	this->killButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		Squally* squally = dynamic_cast<Squally*>(this->entity);
		EntityHealthBehavior* health = this->entity->getAttachedBehavior<EntityHealthBehavior>();

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
