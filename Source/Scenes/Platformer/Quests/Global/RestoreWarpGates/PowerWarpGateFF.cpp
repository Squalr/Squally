#include "PowerWarpGateFF.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Events/ObjectEvents.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Interactables/Doors/Portal.h"
#include "Objects/Platformer/Switches/Trigger.h"
#include "Scenes/Platformer/Level/PlatformerMap.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string PowerWarpGateFF::MapKeyQuest = "power-warp-gate-ff";

PowerWarpGateFF* PowerWarpGateFF::create(GameObject* owner, QuestLine* questLine)
{
	PowerWarpGateFF* instance = new PowerWarpGateFF(owner, questLine);

	instance->autorelease();

	return instance;
}

PowerWarpGateFF::PowerWarpGateFF(GameObject* owner, QuestLine* questLine) : super(owner, questLine, PowerWarpGateFF::MapKeyQuest, false)
{
	this->portal = dynamic_cast<Portal*>(owner);
	this->trigger = dynamic_cast<Trigger*>(owner);
	this->mage = dynamic_cast<PlatformerEntity*>(owner);
}

PowerWarpGateFF::~PowerWarpGateFF()
{
}

void PowerWarpGateFF::onLoad(QuestState questState)
{
	if (this->portal != nullptr)
	{
		if (questState == QuestState::Complete)
		{
			this->portal->unlock(false);
		}
		else
		{
			this->portal->lock(false);
		}
	}

	
	PlatformerMap* map = GameUtils::GetFirstParentOfType<PlatformerMap>(this->owner);

	if (map != nullptr && map->getTransition() == "ff")
	{
		this->complete();
	}
}

void PowerWarpGateFF::onActivate(bool isActiveThroughSkippable, bool isInitialActivation)
{
}

void PowerWarpGateFF::onComplete()
{
	if (this->portal != nullptr)
	{
		this->portal->unlock(true);
	}
}

void PowerWarpGateFF::onSkipped()
{
	if (this->portal != nullptr)
	{
		this->portal->unlock(true);
	}
}
