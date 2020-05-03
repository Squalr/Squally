#include "FollowMovementBehavior.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Movement/EntityMovementBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Squally/Movement/SquallyMovementBehavior.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/EntityResources.h"

using namespace cocos2d;

const std::string FollowMovementBehavior::MapKey = "follow-movement";
const float FollowMovementBehavior::StopFollowRangeX = 128.0f;
const float FollowMovementBehavior::TryJumpRangeY = 96.0f;
const float FollowMovementBehavior::ResetRangeX = 2048.0f;
const float FollowMovementBehavior::ResetRangeY = 1024.0f;

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
	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKey);
	
	this->entity->watchForAttachedBehavior<EntityMovementBehavior>([=](EntityMovementBehavior* entityMovementBehavior)
	{
		entityMovementBehavior->setMoveAcceleration(SquallyMovementBehavior::SquallyMovementAcceleration);
	});
	
	this->scheduleUpdate();
}

void FollowMovementBehavior::onDisable()
{
	super::onDisable();
}

void FollowMovementBehavior::update(float dt)
{
	super::update(dt);

	if (this->squally == nullptr || this->entity == nullptr)
	{
		return;
	}
	
	this->entity->setState(StateKeys::MovementY, Value(0.0f));

	if (this->entity->getStateOrDefault(StateKeys::PatrolHijacked, Value(false)).asBool())
	{
		return;
	}

	if (this->entity->getStateOrDefault(StateKeys::CinematicHijacked, Value(false)).asBool()
		|| this->entity->hasState(StateKeys::CinematicDestinationX))
	{
		return;
	}

	Vec3 squallyPosition = GameUtils::getWorldCoords3D(this->squally);
	Vec3 entityPosition = GameUtils::getWorldCoords3D(this->entity);

	if (std::abs(squallyPosition.x - entityPosition.x) >= FollowMovementBehavior::ResetRangeX ||
		std::abs(squallyPosition.y - entityPosition.y) >= FollowMovementBehavior::ResetRangeY)
	{
		PlatformerEvents::TriggerWarpObjectToLocation(PlatformerEvents::WarpObjectToLocationArgs(this->entity, squallyPosition));
		return;
	}

	if (std::abs(squallyPosition.x - entityPosition.x) >= FollowMovementBehavior::StopFollowRangeX)
	{
		this->entity->setState(StateKeys::PatrolDestinationX, Value(squallyPosition.x));
	}

	if (squallyPosition.y >= entityPosition.y + FollowMovementBehavior::TryJumpRangeY)
	{
		this->entity->setState(StateKeys::MovementY, Value(1.0f));
	}
}
