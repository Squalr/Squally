#include "PowerWarpGateUR.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Dialogue/DialogueOption.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Interactables/Doors/Portal.h"
#include "Objects/Platformer/Switches/Trigger.h"
#include "Scenes/Platformer/Components/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/Dialogue/DialogueSet.h"
#include "Scenes/Platformer/Dialogue/Voices.h"
#include "Scenes/Platformer/Level/PlatformerMap.h"

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
	this->portal = dynamic_cast<Portal*>(owner);
	this->trigger = dynamic_cast<Trigger*>(owner);
	this->mage = dynamic_cast<PlatformerEntity*>(owner);
}

PowerWarpGateUR::~PowerWarpGateUR()
{
}

void PowerWarpGateUR::onLoad(QuestState questState)
{
	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKey);

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
	
	PlatformerMap* map = GameUtils::GetFirstParentOfType<PlatformerMap>(this->owner);

	if (map != nullptr && map->getTransition() == "ur")
	{
		this->complete();
	}
}

void PowerWarpGateUR::onActivate(bool isActiveThroughSkippable, bool isInitialActivation)
{
}

void PowerWarpGateUR::onComplete()
{
	if (this->portal != nullptr)
	{
		this->portal->unlock(true);
	}
}

void PowerWarpGateUR::onSkipped()
{
	if (this->portal != nullptr)
	{
		this->portal->unlock(true);
	}
}
