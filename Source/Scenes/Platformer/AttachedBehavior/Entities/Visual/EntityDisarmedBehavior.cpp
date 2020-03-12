#include "EntityDisarmedBehavior.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Animations/AnimationPart.h"
#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Entities/Platformer/PlatformerEntity.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string EntityDisarmedBehavior::MapKeyAttachedBehavior = "disarmed";

EntityDisarmedBehavior* EntityDisarmedBehavior::create(GameObject* owner)
{
	EntityDisarmedBehavior* instance = new EntityDisarmedBehavior(owner);

	instance->autorelease();

	return instance;
}

EntityDisarmedBehavior::EntityDisarmedBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
}

EntityDisarmedBehavior::~EntityDisarmedBehavior()
{
}

void EntityDisarmedBehavior::onLoad()
{
	AnimationPart* mainhand = this->entity->getAnimations()->getAnimationPart("mainhand");

	if (mainhand != nullptr)
	{
		mainhand->replaceSprite(UIResources::EmptyImage);
	}
}

void EntityDisarmedBehavior::onDisable()
{
	super::onDisable();
}
