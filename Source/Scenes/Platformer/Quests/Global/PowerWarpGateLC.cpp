#include "PowerWarpGateLC.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"

#include "Engine/Events/ObjectEvents.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Objects/Platformer/Interactables/Doors/Portal.h"
#include "Objects/Platformer/Switches/Trigger.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string PowerWarpGateLC::MapKeyQuest = "power-warp-gate-lc";

PowerWarpGateLC* PowerWarpGateLC::create(GameObject* owner, QuestLine* questLine)
{
	PowerWarpGateLC* instance = new PowerWarpGateLC(owner, questLine);

	instance->autorelease();

	return instance;
}

PowerWarpGateLC::PowerWarpGateLC(GameObject* owner, QuestLine* questLine) : super(owner, questLine, PowerWarpGateLC::MapKeyQuest, false)
{
	this->portal = dynamic_cast<Portal*>(owner);
	this->trigger = dynamic_cast<Trigger*>(owner);
	this->mage = dynamic_cast<PlatformerEntity*>(owner);
}

PowerWarpGateLC::~PowerWarpGateLC()
{
}

void PowerWarpGateLC::onLoad(QuestState questState)
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

	if (questState != QuestState::Complete)
	{
		if (this->mage != nullptr)
		{
			this->mage->setOpacity(0);

			this->listenForMapEventOnce(PowerWarpGateLC::MapKeyQuest, [=](ValueMap)
			{
				this->mage->runAction(FadeTo::create(0.5f, 255));
				this->complete();
			});
		}

		if (this->trigger != nullptr)
		{
			this->listenForMapEventOnce(PowerWarpGateLC::MapKeyQuest, [=](ValueMap)
			{
				this->complete();
			});
		}
	}
}

void PowerWarpGateLC::onActivate(bool isActiveThroughSkippable)
{
}

void PowerWarpGateLC::onComplete()
{
	if (this->portal != nullptr)
	{
		this->portal->unlock(true);
	}
}

void PowerWarpGateLC::onSkipped()
{
	if (this->portal != nullptr)
	{
		this->portal->unlock(true);
	}
}
