#include "EntityCinematicHijackBehavior.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/EntityResources.h"

using namespace cocos2d;

const std::string EntityCinematicHijackBehavior::MapKeyAttachedBehavior = "entity-cinematic-hijack";

EntityCinematicHijackBehavior* EntityCinematicHijackBehavior::create(GameObject* owner, std::string attachedBehaviorArgs)
{
	EntityCinematicHijackBehavior* instance = new EntityCinematicHijackBehavior(owner, attachedBehaviorArgs);

	instance->autorelease();

	return instance;
}

EntityCinematicHijackBehavior::EntityCinematicHijackBehavior(GameObject* owner, std::string attachedBehaviorArgs) : super(owner, attachedBehaviorArgs)
{
	this->entity = static_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
}

EntityCinematicHijackBehavior::~EntityCinematicHijackBehavior()
{
}

void EntityCinematicHijackBehavior::onLoad()
{
	this->addEventListener(EventListenerCustom::create(PlatformerEvents::EventCinematicHijack, [=](EventCustom*)
	{
		this->entity->setState(StateKeys::CinematicHijacked, Value(true));
	}));

	this->addEventListener(EventListenerCustom::create(PlatformerEvents::EventCinematicRestore, [=](EventCustom*)
	{
		this->entity->setState(StateKeys::CinematicHijacked, Value(false));
	}));
}
