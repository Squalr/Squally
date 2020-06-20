#include "LookAtSquallyBehavior.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/EntityResources.h"

using namespace cocos2d;

const std::string LookAtSquallyBehavior::MapKey = "face-squally";
const std::string LookAtSquallyBehavior::MapKeyAlias = "look-at-squally";

LookAtSquallyBehavior* LookAtSquallyBehavior::create(GameObject* owner)
{
	LookAtSquallyBehavior* instance = new LookAtSquallyBehavior(owner);

	instance->autorelease();

	return instance;
}

LookAtSquallyBehavior::LookAtSquallyBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}

	this->squally = nullptr;
}

LookAtSquallyBehavior::~LookAtSquallyBehavior()
{
}

void LookAtSquallyBehavior::onLoad()
{
	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKey);

	this->scheduleUpdate();
}

void LookAtSquallyBehavior::update(float dt)
{
	super::update(dt);

	if (this->squally == nullptr
		|| this->entity == nullptr
		|| !this->entity->getRuntimeStateOrDefaultBool(StateKeys::IsAlive, true)
		|| !this->entity->hasRuntimeState(StateKeys::PatrolDestinationX)
		|| !this->entity->hasRuntimeState(StateKeys::CinematicDestinationX)
		|| !this->entity->getRuntimeStateOrDefaultBool(StateKeys::CinematicHijacked, true))
	{
		return;
	}

	if (GameUtils::getWorldCoords(this->entity).x > GameUtils::getWorldCoords(this->squally).x)
	{
		this->entity->getAnimations()->setFlippedX(true);
	}
	else
	{
		this->entity->getAnimations()->setFlippedX(false);
	}
}
