#include "PowerWarpGateBP.h"

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

const std::string PowerWarpGateBP::MapKeyQuest = "power-warp-gate-bp";

PowerWarpGateBP* PowerWarpGateBP::create(GameObject* owner, QuestLine* questLine)
{
	PowerWarpGateBP* instance = new PowerWarpGateBP(owner, questLine);

	instance->autorelease();

	return instance;
}

PowerWarpGateBP::PowerWarpGateBP(GameObject* owner, QuestLine* questLine) : super(owner, questLine, PowerWarpGateBP::MapKeyQuest, false)
{
	this->portal = dynamic_cast<Portal*>(owner);
	this->trigger = dynamic_cast<Trigger*>(owner);
	this->mage = dynamic_cast<PlatformerEntity*>(owner);
}

PowerWarpGateBP::~PowerWarpGateBP()
{
}

void PowerWarpGateBP::onLoad(QuestState questState)
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

	if (map != nullptr && map->getTransition() == "bp")
	{
		this->complete();
	}
}

void PowerWarpGateBP::onActivate(bool isActiveThroughSkippable, bool isInitialActivation)
{
}

void PowerWarpGateBP::onComplete()
{
	if (this->portal != nullptr)
	{
		this->portal->unlock(true);
	}
}

void PowerWarpGateBP::onSkipped()
{
	if (this->portal != nullptr)
	{
		this->portal->unlock(true);
	}
}
