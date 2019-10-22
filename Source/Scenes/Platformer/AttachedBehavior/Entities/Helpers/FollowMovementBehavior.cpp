#include "FollowMovementBehavior.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/EntityResources.h"

using namespace cocos2d;

const std::string FollowMovementBehavior::MapKeyAttachedBehavior = "follow-movement";
const float FollowMovementBehavior::StopFollowRangeX = 64.0f;
const float FollowMovementBehavior::TryJumpRangeY = 96.0f;

FollowMovementBehavior* FollowMovementBehavior::create(GameObject* owner)
{
	FollowMovementBehavior* instance = new FollowMovementBehavior(owner);

	instance->autorelease();

	return instance;
}

FollowMovementBehavior::FollowMovementBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);
	this->squally = nullptr;

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
}

FollowMovementBehavior::~FollowMovementBehavior()
{
}

void FollowMovementBehavior::onLoad()
{
	ObjectEvents::watchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	});
}

void FollowMovementBehavior::update(float dt)
{
	super::update(dt);

	if (this->squally == nullptr || this->entity == nullptr)
	{
		return;
	}

	if (this->entity->hasState(StateKeys::CinematicHijacked) || this->entity->hasState(StateKeys::CinematicDestinationX))
	{
		return;
	}

	Vec2 squallyPosition = GameUtils::getWorldCoords(this->squally);
	Vec2 entityPosition = GameUtils::getWorldCoords(this->entity);

	if (std::abs(squallyPosition.x - entityPosition.x) >= FollowMovementBehavior::StopFollowRangeX)
	{
		this->entity->setState(StateKeys::CinematicDestinationX, Value(squallyPosition.x));
	}

	if (squallyPosition.y >= entityPosition.y + FollowMovementBehavior::TryJumpRangeY)
	{
		this->entity->setState(StateKeys::MovementY, Value(1.0f));
	}
}
