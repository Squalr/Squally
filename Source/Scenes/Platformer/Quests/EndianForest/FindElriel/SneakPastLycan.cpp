#include "SneakPastLycan.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Dialogue/DialogueOption.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Events/QuestEvents.h"
#include "Entities/Platformer/Npcs/EndianForest/Lycan.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/Dialogue/DialogueSet.h"

#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SneakPastLycan::MapKeyQuest = "sneak-past-lycan";

SneakPastLycan* SneakPastLycan::create(GameObject* owner, QuestLine* questLine)
{
	SneakPastLycan* instance = new SneakPastLycan(owner, questLine);

	instance->autorelease();

	return instance;
}

SneakPastLycan::SneakPastLycan(GameObject* owner, QuestLine* questLine) : super(owner, questLine, SneakPastLycan::MapKeyQuest, false)
{
	this->lycan = nullptr;
	this->squally = nullptr;
}

SneakPastLycan::~SneakPastLycan()
{
}

void SneakPastLycan::onLoad(QuestState questState)
{
	ObjectEvents::WatchForObject<Lycan>(this, [=](Lycan* lycan)
	{
		this->lycan = lycan;

		if (questState == QuestState::Complete)
		{
			this->lycan->despawn();
		}
		else
		{
			this->runCinematicSequence();
		}
	}, Lycan::MapKey);

	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKey);
}

void SneakPastLycan::onActivate(bool isActiveThroughSkippable)
{
}

void SneakPastLycan::onComplete()
{
}

void SneakPastLycan::onSkipped()
{
	this->removeAllListeners();
}

void SneakPastLycan::runCinematicSequence()
{
	if (this->lycan == nullptr)
	{
		return;
	}

	this->lycan->watchForAttachedBehavior<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
	{
		interactionBehavior->getMainDialogueSet()->addDialogueOption(DialogueOption::create(
			Strings::Platformer_Entities_EndianForest_Lycan_LetMeIntoTown::create(),
			[=]()
			{
				DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
					Strings::Platformer_Entities_EndianForest_Lycan_NobodyAllowedIntoTown::create(),
					DialogueEvents::DialogueVisualArgs(
						DialogueBox::DialogueDock::Bottom,
						DialogueBox::DialogueAlignment::Right,
						DialogueEvents::BuildPreviewNode(&this->squally, false),
						DialogueEvents::BuildPreviewNode(&this->lycan, true)
					),
					[=]()
					{
					},
					SoundResources::Platformer_Entities_Generic_ChatterShort2,
					true
				));
			}),
			0.5f
		);
	});
}
