#include "LockedThroneRoom.h"

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

const std::string LockedThroneRoom::MapKeyQuest = "locked-throne-room";

LockedThroneRoom* LockedThroneRoom::create(GameObject* owner, QuestLine* questLine)
{
	LockedThroneRoom* instance = new LockedThroneRoom(owner, questLine);

	instance->autorelease();

	return instance;
}

LockedThroneRoom::LockedThroneRoom(GameObject* owner, QuestLine* questLine) : super(owner, questLine, LockedThroneRoom::MapKeyQuest, false)
{
	this->portal = dynamic_cast<Portal*>(owner);
	this->squally = nullptr;
}

LockedThroneRoom::~LockedThroneRoom()
{
}

void LockedThroneRoom::onLoad(QuestState questState)
{
	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKey);

	if (this->portal != nullptr)
	{
		if (questState != QuestState::Complete)
		{
			this->portal->lock();
		}
	}
}

void LockedThroneRoom::onActivate(bool isActiveThroughSkippable, bool isInitialActivation)
{
}

void LockedThroneRoom::onComplete()
{
}

void LockedThroneRoom::onSkipped()
{
}
