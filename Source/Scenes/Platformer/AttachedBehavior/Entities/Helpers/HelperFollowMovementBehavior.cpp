#include "HelperFollowMovementBehavior.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Maps/MapLayer.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Cinematic/CinematicMarker.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Movement/EntityMovementBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Squally/Movement/SquallyMovementBehavior.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/EntityResources.h"

using namespace cocos2d;

const std::string HelperFollowMovementBehavior::MapKey = "follow-movement";
const std::string HelperFollowMovementBehavior::MapEventMoveToRest = "helper-move-to-rest";
const std::string HelperFollowMovementBehavior::MapEventStopRest = "helper-stop-rest";
const float HelperFollowMovementBehavior::StopFollowRangeX = 128.0f;
const float HelperFollowMovementBehavior::TryJumpRangeY = 160.0f;
const float HelperFollowMovementBehavior::ResetRangeX = 2048.0f;
const float HelperFollowMovementBehavior::ResetRangeY = 1024.0f;

HelperFollowMovementBehavior* HelperFollowMovementBehavior::create(GameObject* owner)
{
	HelperFollowMovementBehavior* instance = new HelperFollowMovementBehavior(owner);

	instance->autorelease();

	return instance;
}

HelperFollowMovementBehavior::HelperFollowMovementBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);
	this->squally = nullptr;
	this->followEnabled = true;

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
}

HelperFollowMovementBehavior::~HelperFollowMovementBehavior()
{
}

void HelperFollowMovementBehavior::onLoad()
{
	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;

		// Listen for Squally warp
		this->addEventListener(EventListenerCustom::create(PlatformerEvents::EventAfterWarpPrefix + this->squally->getUniqueIdentifier(), [=](EventCustom* eventCustom)
		{
			PlatformerEvents::WarpObjectToLocationArgs* args = static_cast<PlatformerEvents::WarpObjectToLocationArgs*>(eventCustom->getData());
			
			if (args != nullptr)
			{
				this->warpToSqually();
			}
		}));
	}, Squally::MapKey);

	this->addEventListener(EventListenerCustom::create(PlatformerEvents::EventSquallySpawned, [=](EventCustom* eventCustom)
	{
		this->warpToSqually();
	}));
	
	this->entity->watchForAttachedBehavior<EntityMovementBehavior>([=](EntityMovementBehavior* entityMovementBehavior)
	{
		entityMovementBehavior->setMoveAcceleration(SquallyMovementBehavior::SquallyMovementAcceleration);
	});

	this->entity->listenForMapEvent(HelperFollowMovementBehavior::MapEventMoveToRest, [=](ValueMap)
	{
		ObjectEvents::WatchForObject<CinematicMarker>(this->entity, [=](CinematicMarker* rest)
		{
			this->entity->setState(StateKeys::PatrolHijacked, Value(true));
			this->entity->setState(StateKeys::PatrolDestinationX, Value(GameUtils::getWorldCoords(rest).x));
		}, "helper-rest");
	});

	this->entity->listenForMapEvent(HelperFollowMovementBehavior::MapEventStopRest, [=](ValueMap)
	{
		this->entity->clearState(StateKeys::PatrolHijacked);
		this->entity->clearState(StateKeys::PatrolDestinationX);
	});
	
	this->scheduleUpdate();

	this->defer([=]()
	{
		this->warpToSqually();
	});
}

void HelperFollowMovementBehavior::onDisable()
{
	super::onDisable();
}

void HelperFollowMovementBehavior::update(float dt)
{
	super::update(dt);

	if (this->squally == nullptr || this->entity == nullptr || !this->followEnabled)
	{
		return;
	}
	
	this->entity->setState(StateKeys::MovementY, Value(0.0f));

	if (this->entity->getRuntimeStateOrDefault(StateKeys::PatrolHijacked, Value(false)).asBool())
	{
		return;
	}

	if (this->entity->getRuntimeStateOrDefault(StateKeys::CinematicHijacked, Value(false)).asBool()
		|| this->entity->hasRuntimeState(StateKeys::CinematicDestinationX))
	{
		return;
	}

	Vec3 squallyPosition = GameUtils::getWorldCoords3D(this->squally);
	Vec3 entityPosition = GameUtils::getWorldCoords3D(this->entity);

	if (std::abs(squallyPosition.x - entityPosition.x) >= HelperFollowMovementBehavior::ResetRangeX ||
		std::abs(squallyPosition.y - entityPosition.y) >= HelperFollowMovementBehavior::ResetRangeY)
	{
		this->warpToSqually();
		return;
	}

	if (std::abs(squallyPosition.x - entityPosition.x) >= HelperFollowMovementBehavior::StopFollowRangeX)
	{
		this->entity->setState(StateKeys::PatrolDestinationX, Value(squallyPosition.x));
	}

	if (squallyPosition.y >= entityPosition.y + HelperFollowMovementBehavior::TryJumpRangeY)
	{
		this->entity->setState(StateKeys::MovementY, Value(1.0f));
	}
}

void HelperFollowMovementBehavior::warpToSqually()
{
	MapLayer* layer = GameUtils::getFirstParentOfType<MapLayer>(this->squally);

	if (layer != nullptr)
	{
		GameUtils::changeParent(this->entity, layer, true);
	}

	PlatformerEvents::TriggerWarpObjectToLocation(PlatformerEvents::WarpObjectToLocationArgs(this->entity, GameUtils::getWorldCoords3D(this->squally)));
}

void HelperFollowMovementBehavior::enableFollow()
{
	this->followEnabled = true;
}

void HelperFollowMovementBehavior::disableFollow()
{
	this->followEnabled = false;
}
