#include "BusinessHours.h"

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
#include "Scenes/Platformer/AttachedBehavior/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/Dialogue/DialogueSet.h"

#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string BusinessHours::MapKeyQuest = "business-hours";

BusinessHours* BusinessHours::create(GameObject* owner, QuestLine* questLine)
{
	BusinessHours* instance = new BusinessHours(owner, questLine);

	instance->autorelease();

	return instance;
}

BusinessHours::BusinessHours(GameObject* owner, QuestLine* questLine) : super(owner, questLine, BusinessHours::MapKeyQuest, false)
{
	this->portal = dynamic_cast<Portal*>(owner);
	this->squally = nullptr;
}

BusinessHours::~BusinessHours()
{
}

void BusinessHours::onLoad(QuestState questState)
{
	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKey);

	if (this->portal != nullptr)
	{
		this->portal->setInteractCallback([=]()
		{
			switch(questState)
			{
				case QuestState::Complete:
				case QuestState::Active:
				case QuestState::ActiveThroughSkippable:
				{
					return true;
				}
				default:
				{
					this->runCinematicSequence();

					return false;
				}
			}
		});
	}
}

void BusinessHours::onActivate(bool isActiveThroughSkippable)
{
}

void BusinessHours::onComplete()
{
}

void BusinessHours::onSkipped()
{
}

void BusinessHours::runCinematicSequence()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Objects_Doors_ClosedBusinessHours::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Center,
			DialogueEvents::BuildPreviewNode(nullptr, false),
			DialogueEvents::BuildPreviewNode(&this->squally, true)
		),
		[=]()
		{
		},
		"",
		true
	));
}
