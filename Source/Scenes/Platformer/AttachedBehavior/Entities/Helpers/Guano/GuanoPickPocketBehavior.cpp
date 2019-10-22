#include "GuanoPickPocketBehavior.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/EntityResources.h"

using namespace cocos2d;

const std::string GuanoPickPocketBehavior::MapKeyAttachedBehavior = "pick-pocketer";

GuanoPickPocketBehavior* GuanoPickPocketBehavior::create(GameObject* owner)
{
	GuanoPickPocketBehavior* instance = new GuanoPickPocketBehavior(owner);

	instance->autorelease();

	return instance;
}

GuanoPickPocketBehavior::GuanoPickPocketBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
}

GuanoPickPocketBehavior::~GuanoPickPocketBehavior()
{
}

void GuanoPickPocketBehavior::onLoad()
{
}
