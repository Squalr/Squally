#include "BossExitUnlocked.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Dialogue/DialogueOption.h"
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

const std::string BossExitUnlocked::MapKeyQuest = "boss-exit-unlocked";

BossExitUnlocked* BossExitUnlocked::create(GameObject* owner, QuestLine* questLine)
{
	BossExitUnlocked* instance = new BossExitUnlocked(owner, questLine);

	instance->autorelease();

	return instance;
}

BossExitUnlocked::BossExitUnlocked(GameObject* owner, QuestLine* questLine) : super(owner, questLine, BossExitUnlocked::MapKeyQuest, false)
{
	this->portal = dynamic_cast<Portal*>(owner);
}

BossExitUnlocked::~BossExitUnlocked()
{
}

void BossExitUnlocked::onLoad(QuestState questState)
{
	if (this->portal != nullptr)
	{
		switch(questState)
		{
			case QuestState::Complete:
			case QuestState::Active:
			case QuestState::ActiveThroughSkippable:
			{
				this->portal->unlock(false);
				break;
			}
			default:
			{
				this->portal->lock(false);
				break;
			}
		}
	}
}

void BossExitUnlocked::onActivate(bool isActiveThroughSkippable)
{
}

void BossExitUnlocked::onComplete()
{
}

void BossExitUnlocked::onSkipped()
{
}