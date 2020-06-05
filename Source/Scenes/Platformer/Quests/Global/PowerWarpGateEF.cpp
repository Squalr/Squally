#include "PowerWarpGateEF.h"

#include "Engine/Events/ObjectEvents.h"
#include "Objects/Platformer/Interactables/Doors/Portal.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string PowerWarpGateEF::MapKeyQuest = "power-warp-gate-ef";

PowerWarpGateEF* PowerWarpGateEF::create(GameObject* owner, QuestLine* questLine)
{
	PowerWarpGateEF* instance = new PowerWarpGateEF(owner, questLine);

	instance->autorelease();

	return instance;
}

PowerWarpGateEF::PowerWarpGateEF(GameObject* owner, QuestLine* questLine) : super(owner, questLine, PowerWarpGateEF::MapKeyQuest, false)
{
	this->portal = dynamic_cast<Portal*>(owner);
}

PowerWarpGateEF::~PowerWarpGateEF()
{
}

void PowerWarpGateEF::onLoad(QuestState questState)
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

void PowerWarpGateEF::onActivate(bool isActiveThroughSkippable)
{
}

void PowerWarpGateEF::onComplete()
{
}

void PowerWarpGateEF::onSkipped()
{
}
