#include "MagesWarpLock.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Dialogue/SpeechBubble.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Events/QuestEvents.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Interactables/Doors/Portal.h"
#include "Scenes/Platformer/Components/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/Dialogue/DialogueSet.h"

#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string MagesWarpLock::MapKeyQuest = "mages-warp-lock";

MagesWarpLock* MagesWarpLock::create(GameObject* owner, QuestLine* questLine)
{
	MagesWarpLock* instance = new MagesWarpLock(owner, questLine);

	instance->autorelease();

	return instance;
}

MagesWarpLock::MagesWarpLock(GameObject* owner, QuestLine* questLine) : super(owner, questLine, MagesWarpLock::MapKeyQuest, false)
{
	this->portal = dynamic_cast<Portal*>(owner);
	this->squally = nullptr;
}

MagesWarpLock::~MagesWarpLock()
{
}

void MagesWarpLock::onLoad(QuestState questState)
{
	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKey);

	if (this->portal != nullptr)
	{
		switch(questState)
		{
			case QuestState::Complete:
			case QuestState::Active:
			case QuestState::ActiveThroughSkippable:
			{
				break;
			}
			default:
			{
				this->portal->lock();
				break;
			}
		}
	}
}

void MagesWarpLock::onActivate(bool isActiveThroughSkippable, bool isInitialActivation)
{
}

void MagesWarpLock::onComplete()
{
}

void MagesWarpLock::onSkipped()
{
}
