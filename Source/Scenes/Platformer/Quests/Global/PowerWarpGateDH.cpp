#include "PowerWarpGateDH.h"

#include "Engine/Events/ObjectEvents.h"
#include "Objects/Platformer/Interactables/Doors/Portal.h"

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
	this->portal = static_cast<Portal*>(owner);
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
}

void PowerWarpGateDH::onActivate(bool isActiveThroughSkippable)
{
}

void PowerWarpGateDH::onComplete()
{
}

void PowerWarpGateDH::onSkipped()
{
}
