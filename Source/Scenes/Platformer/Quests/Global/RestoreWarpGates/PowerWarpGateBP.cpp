#include "PowerWarpGateBP.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"

#include "Engine/Events/ObjectEvents.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Objects/Platformer/Interactables/Doors/Portal.h"
#include "Objects/Platformer/Switches/Trigger.h"

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

	if (questState != QuestState::Complete)
	{
		if (this->mage != nullptr)
		{
			this->mage->setOpacity(0);

			this->listenForMapEventOnce(PowerWarpGateBP::MapKeyQuest, [=](ValueMap)
			{
				this->mage->runAction(FadeTo::create(0.5f, 255));
				this->complete();
			});
		}

		if (this->trigger != nullptr)
		{
			this->listenForMapEventOnce(PowerWarpGateBP::MapKeyQuest, [=](ValueMap)
			{
				this->complete();
			});
		}
	}
}

void PowerWarpGateBP::onActivate(bool isActiveThroughSkippable)
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
