#include "PowerWarpGateDM.h"

#include "Engine/Events/ObjectEvents.h"
#include "Objects/Platformer/Interactables/Doors/Portal.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string PowerWarpGateDM::MapKeyQuest = "power-warp-gate-dm";

PowerWarpGateDM* PowerWarpGateDM::create(GameObject* owner, QuestLine* questLine)
{
	PowerWarpGateDM* instance = new PowerWarpGateDM(owner, questLine);

	instance->autorelease();

	return instance;
}

PowerWarpGateDM::PowerWarpGateDM(GameObject* owner, QuestLine* questLine) : super(owner, questLine, PowerWarpGateDM::MapKeyQuest, false)
{
	this->portal = static_cast<Portal*>(owner);
}

PowerWarpGateDM::~PowerWarpGateDM()
{
}

void PowerWarpGateDM::onLoad(QuestState questState)
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

void PowerWarpGateDM::onActivate(bool isActiveThroughSkippable)
{
}

void PowerWarpGateDM::onComplete()
{
}

void PowerWarpGateDM::onSkipped()
{
}
