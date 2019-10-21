#include "EntityPickPocketBehavior.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Physics/EngineCollisionTypes.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/EntitySelectionBehavior.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/EntityResources.h"

using namespace cocos2d;

const std::string EntityPickPocketBehavior::MapKeyAttachedBehavior = "pick-pocket";

EntityPickPocketBehavior* EntityPickPocketBehavior::create(GameObject* owner)
{
	EntityPickPocketBehavior* instance = new EntityPickPocketBehavior(owner);

	instance->autorelease();

	return instance;
}

EntityPickPocketBehavior::EntityPickPocketBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
}

EntityPickPocketBehavior::~EntityPickPocketBehavior()
{
}

void EntityPickPocketBehavior::onLoad()
{
	this->entity->watchForAttachedBehavior<EntitySelectionBehavior>([=](EntitySelectionBehavior* selectionBehavior)
	{
	});
}
