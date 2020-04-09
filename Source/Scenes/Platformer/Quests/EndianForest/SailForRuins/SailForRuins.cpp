#include "SailForRuins.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Dialogue/DialogueOption.h"
#include "Engine/Dialogue/SpeechBubble.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Events/QuestEvents.h"
#include "Entities/Platformer/Npcs/EndianForest/Blackbeard.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Interactables/Doors/Portal.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Objects/DisabledPortal.h"
#include "Scenes/Platformer/Dialogue/DialogueSet.h"

#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SailForRuins::MapKeyQuest = "sail-for-ruins";
const std::string SailForRuins::QuestTagShipPortal = "ship-portal";

SailForRuins* SailForRuins::create(GameObject* owner, QuestLine* questLine)
{
	SailForRuins* instance = new SailForRuins(owner, questLine);

	instance->autorelease();

	return instance;
}

SailForRuins::SailForRuins(GameObject* owner, QuestLine* questLine) : super(owner, questLine, SailForRuins::MapKeyQuest, false)
{
	this->blackbeard = nullptr;
	this->squally = nullptr;
}

SailForRuins::~SailForRuins()
{
}

void SailForRuins::onLoad(QuestState questState)
{
	ObjectEvents::watchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKey);

	ObjectEvents::watchForObject<Portal>(this, [=](Portal* portal)
	{
		this->portal = portal;

		if (questState != QuestState::None)
		{
			this->portal->getAttachedBehavior<DisabledPortal>([=](DisabledPortal* disabledPortal)
			{
				disabledPortal->enablePortal();
			});

			this->complete();
		}

	}, SailForRuins::QuestTagShipPortal);

	ObjectEvents::watchForObject<Blackbeard>(this, [=](Blackbeard* blackbeard)
	{
		this->blackbeard = blackbeard;

		this->blackbeard->watchForAttachedBehavior<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
		{
			interactionBehavior->getMainDialogueSet()->addDialogueOption(DialogueOption::create(
				Strings::Platformer_Quests_EndianForest_SailForRuins_BlackBeard_CanWeBoard::create()->setStringReplacementVariables(Strings::Platformer_MapNames_Zones_UnderflowRuins::create()),
				[=]()
				{
					switch(questState)
					{
						case QuestState::Active:
						case QuestState::ActiveThroughSkippable:
						case QuestState::Complete:
						{
							this->runYesSequence();
							break;
						}
						case QuestState::None:
						{
							this->runNoSequence();
							break;
						}
					}
				}),
				0.5f
			);
		});
	}, Blackbeard::MapKey);
}

void SailForRuins::onActivate(bool isActiveThroughSkippable)
{
}

void SailForRuins::onComplete()
{
}

void SailForRuins::onSkipped()
{
}

void SailForRuins::runNoSequence()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_EndianForest_SailForRuins_BlackBeard_Nay::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Left,
			DialogueEvents::BuildPreviewNode(&this->blackbeard, false),
			DialogueEvents::BuildPreviewNode(&this->squally, true)
		),
		[=]()
		{
		},
		SoundResources::Platformer_Entities_Generic_ChatterMedium3,
		true
	));
}

void SailForRuins::runYesSequence()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_EndianForest_SailForRuins_BlackBeard_Aye::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Left,
			DialogueEvents::BuildPreviewNode(&this->blackbeard, false),
			DialogueEvents::BuildPreviewNode(&this->squally, true)
		),
		[=]()
		{
		},
		SoundResources::Platformer_Entities_Generic_ChatterMedium4,
		true
	));
}
