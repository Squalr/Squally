#include "PowerWarpGateUR.h"

#include "Engine/Events/ObjectEvents.h"
#include "Objects/Platformer/Interactables/Doors/Portal.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string PowerWarpGateUR::MapKeyQuest = "power-warp-gate-ur";

PowerWarpGateUR* PowerWarpGateUR::create(GameObject* owner, QuestLine* questLine)
{
	PowerWarpGateUR* instance = new PowerWarpGateUR(owner, questLine);

	instance->autorelease();

	return instance;
}

PowerWarpGateUR::PowerWarpGateUR(GameObject* owner, QuestLine* questLine) : super(owner, questLine, PowerWarpGateUR::MapKeyQuest, false)
{
	this->portal = static_cast<Portal*>(owner);
}

PowerWarpGateUR::~PowerWarpGateUR()
{
}

void PowerWarpGateUR::onLoad(QuestState questState)
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

void PowerWarpGateUR::onActivate(bool isActiveThroughSkippable)
{
}

void PowerWarpGateUR::onComplete()
{
}

void PowerWarpGateUR::onSkipped()
{
}
