#include "PowerWarpGateBP.h"

#include "Engine/Events/ObjectEvents.h"
#include "Objects/Platformer/Interactables/Doors/Portal.h"

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
	this->portal = static_cast<Portal*>(owner);
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
}

void PowerWarpGateBP::onActivate(bool isActiveThroughSkippable)
{
}

void PowerWarpGateBP::onComplete()
{
}

void PowerWarpGateBP::onSkipped()
{
}
