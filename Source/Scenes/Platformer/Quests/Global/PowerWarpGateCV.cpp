#include "PowerWarpGateCV.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"

#include "Engine/Events/ObjectEvents.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Objects/Platformer/Interactables/Doors/Portal.h"
#include "Objects/Platformer/Switches/Trigger.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string PowerWarpGateCV::MapKeyQuest = "power-warp-gate-cv";

PowerWarpGateCV* PowerWarpGateCV::create(GameObject* owner, QuestLine* questLine)
{
	PowerWarpGateCV* instance = new PowerWarpGateCV(owner, questLine);

	instance->autorelease();

	return instance;
}

PowerWarpGateCV::PowerWarpGateCV(GameObject* owner, QuestLine* questLine) : super(owner, questLine, PowerWarpGateCV::MapKeyQuest, false)
{
	this->portal = dynamic_cast<Portal*>(owner);
	this->trigger = dynamic_cast<Trigger*>(owner);
	this->mage = dynamic_cast<PlatformerEntity*>(owner);
}

PowerWarpGateCV::~PowerWarpGateCV()
{
}

void PowerWarpGateCV::onLoad(QuestState questState)
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

			this->listenForMapEventOnce(PowerWarpGateCV::MapKeyQuest, [=](ValueMap)
			{
				this->mage->runAction(FadeTo::create(0.5f, 255));
				this->complete();
			});
		}

		if (this->trigger != nullptr)
		{
			this->listenForMapEventOnce(PowerWarpGateCV::MapKeyQuest, [=](ValueMap)
			{
				this->complete();
			});
		}
	}
}

void PowerWarpGateCV::onActivate(bool isActiveThroughSkippable)
{
}

void PowerWarpGateCV::onComplete()
{
	if (this->portal != nullptr)
	{
		this->portal->unlock(true);
	}
}

void PowerWarpGateCV::onSkipped()
{
	if (this->portal != nullptr)
	{
		this->portal->unlock(true);
	}
}
