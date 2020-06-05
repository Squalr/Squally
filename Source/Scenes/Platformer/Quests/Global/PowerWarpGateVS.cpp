#include "PowerWarpGateVS.h"

#include "Engine/Events/ObjectEvents.h"
#include "Objects/Platformer/Interactables/Doors/Portal.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string PowerWarpGateVS::MapKeyQuest = "power-warp-gate-vs";

PowerWarpGateVS* PowerWarpGateVS::create(GameObject* owner, QuestLine* questLine)
{
	PowerWarpGateVS* instance = new PowerWarpGateVS(owner, questLine);

	instance->autorelease();

	return instance;
}

PowerWarpGateVS::PowerWarpGateVS(GameObject* owner, QuestLine* questLine) : super(owner, questLine, PowerWarpGateVS::MapKeyQuest, false)
{
	this->portal = static_cast<Portal*>(owner);
}

PowerWarpGateVS::~PowerWarpGateVS()
{
}

void PowerWarpGateVS::onLoad(QuestState questState)
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

void PowerWarpGateVS::onActivate(bool isActiveThroughSkippable)
{
}

void PowerWarpGateVS::onComplete()
{
}

void PowerWarpGateVS::onSkipped()
{
}
