#include "PowerWarpGateDH.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"

#include "Engine/Events/ObjectEvents.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Objects/Platformer/Interactables/Doors/Portal.h"
#include "Objects/Platformer/Switches/Trigger.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string PowerWarpGateDH::MapKeyQuest = "power-warp-gate-dh";

PowerWarpGateDH* PowerWarpGateDH::create(GameObject* owner, QuestLine* questLine)
{
	PowerWarpGateDH* instance = new PowerWarpGateDH(owner, questLine);

	instance->autorelease();

	return instance;
}

PowerWarpGateDH::PowerWarpGateDH(GameObject* owner, QuestLine* questLine) : super(owner, questLine, PowerWarpGateDH::MapKeyQuest, false)
{
	this->portal = dynamic_cast<Portal*>(owner);
	this->trigger = dynamic_cast<Trigger*>(owner);
	this->mage = dynamic_cast<PlatformerEntity*>(owner);
}

PowerWarpGateDH::~PowerWarpGateDH()
{
}

void PowerWarpGateDH::onLoad(QuestState questState)
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

			this->listenForMapEventOnce(PowerWarpGateDH::MapKeyQuest, [=](ValueMap)
			{
				this->mage->runAction(FadeTo::create(0.5f, 255));
				this->complete();
			});
		}

		if (this->trigger != nullptr)
		{
			this->listenForMapEventOnce(PowerWarpGateDH::MapKeyQuest, [=](ValueMap)
			{
				this->complete();
			});
		}
	}
}

void PowerWarpGateDH::onActivate(bool isActiveThroughSkippable)
{
}

void PowerWarpGateDH::onComplete()
{
	if (this->portal != nullptr)
	{
		this->portal->unlock(true);
	}
}

void PowerWarpGateDH::onSkipped()
{
	if (this->portal != nullptr)
	{
		this->portal->unlock(true);
	}
}
