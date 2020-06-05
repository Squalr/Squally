#include "PowerWarpGateLC.h"

#include "Engine/Events/ObjectEvents.h"
#include "Objects/Platformer/Interactables/Doors/Portal.h"

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
	this->portal = static_cast<Portal*>(owner);
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
}

void PowerWarpGateLC::onActivate(bool isActiveThroughSkippable)
{
}

void PowerWarpGateLC::onComplete()
{
}

void PowerWarpGateLC::onSkipped()
{
}
