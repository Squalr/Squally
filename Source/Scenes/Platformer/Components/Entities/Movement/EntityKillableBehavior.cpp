#include "EntityKillableBehavior.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/AnimationPart.h"
#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/Components/Entities/Collision/EntityCollisionBehaviorBase.h"
#include "Scenes/Platformer/Level/Physics/PlatformerPhysicsTypes.h"
#include "Scenes/Platformer/Components/Entities/Stats/EntityHealthBehavior.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string EntityKillableBehavior::MapKey = "killable";

EntityKillableBehavior* EntityKillableBehavior::create(GameObject* owner)
{
	EntityKillableBehavior* instance = new EntityKillableBehavior(owner);

	instance->autorelease();
	
	return instance;
}

EntityKillableBehavior::EntityKillableBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
}

EntityKillableBehavior::~EntityKillableBehavior()
{
}

void EntityKillableBehavior::onLoad()
{
	this->entity->watchForComponent<EntityCollisionBehaviorBase>([=](EntityCollisionBehaviorBase* behavior)
	{
		behavior->entityCollision->whenCollidesWith({ (CollisionType)PlatformerCollisionType::Damage }, [=](CollisionData collisionData)
        {
            this->entity->getComponent<EntityHealthBehavior>([=](EntityHealthBehavior* healthBehavior)
            {
                healthBehavior->setHealth(0, true);
            });
            return CollisionResult::DoNothing;
        });
	});
}

void EntityKillableBehavior::onDisable()
{
	super::onDisable();
}
