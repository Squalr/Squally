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

EntityCinematicHijackBehavior* EntityCinematicHijackBehavior::create(GameObject* owner)
{
	EntityCinematicHijackBehavior* instance = new EntityCinematicHijackBehavior(owner);

	instance->autorelease();

	return instance;
}

EntityCinematicHijackBehavior::EntityCinematicHijackBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);

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
	this->addEventListenerIgnorePause(EventListenerCustom::create(PlatformerEvents::EventCinematicHijack, [=](EventCustom*)
	{
		this->entity->setState(StateKeys::CinematicHijacked, Value(true));
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(PlatformerEvents::EventCinematicRestore, [=](EventCustom*)
	{
		this->entity->setState(StateKeys::CinematicHijacked, Value(false));
	}));
}
