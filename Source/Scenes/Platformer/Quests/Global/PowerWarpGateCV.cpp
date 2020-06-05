#include "PowerWarpGateCV.h"

#include "Engine/Events/ObjectEvents.h"
#include "Objects/Platformer/Interactables/Doors/Portal.h"

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
	this->portal = static_cast<Portal*>(owner);
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
}

void PowerWarpGateCV::onActivate(bool isActiveThroughSkippable)
{
}

void PowerWarpGateCV::onComplete()
{
}

void PowerWarpGateCV::onSkipped()
{
}
