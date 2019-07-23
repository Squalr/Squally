#include "PortalSpawn.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Utils/GameUtils.h"
#include "Events/PlatformerEvents.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string PortalSpawn::MapKeyPortalSpawn = "spawn";
const std::string PortalSpawn::MapKeyPortalSpawnTransition = "transition";

PortalSpawn* PortalSpawn::create(ValueMap& initProperties)
{
	PortalSpawn* instance = new PortalSpawn(initProperties);

	instance->autorelease();

	return instance;
}

PortalSpawn::PortalSpawn(ValueMap& initProperties) : super(initProperties)
{
	this->transition = GameUtils::getKeyOrDefault(this->properties, PortalSpawn::MapKeyPortalSpawnTransition, Value("")).asString();
}

PortalSpawn::~PortalSpawn()
{
}

void PortalSpawn::onEnter()
{
	super::onEnter();
}

void PortalSpawn::initializePositions()
{
	super::initializePositions();
}

void PortalSpawn::initializeListeners()
{
	super::initializeListeners();

	this->addEventListener(EventListenerCustom::create(PlatformerEvents::EventSpawnToTransitionLocation, [=](EventCustom* eventCustom)
	{
		PlatformerEvents::TransitionArgs* args = static_cast<PlatformerEvents::TransitionArgs*>(eventCustom->getUserData());
		
		if (args != nullptr)
		{
			PlatformerEvents::TriggerWarpToLocation(PlatformerEvents::WarpArgs(GameUtils::getWorldCoords(this)));
		}
	}));
}

