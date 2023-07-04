#include "OutsideThroneRoom.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Dialogue/DialogueOption.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Events/QuestEvents.h"
#include "Engine/Quests/QuestLine.h"
#include "Entities/Platformer/Npcs/CastleValgrind/Tyracius.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/DialogueEvents.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Interactables/Doors/Portal.h"
#include "Scenes/Platformer/Components/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/Dialogue/DialogueSet.h"
#include "Scenes/Platformer/Dialogue/Voices.h"
#include "Scenes/Platformer/Level/Physics/PlatformerPhysicsTypes.h"
#include "Scenes/Platformer/Quests/CastleValgrind/CureKingLine/DefeatAgnes.h"

#include "Resources/EntityResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string OutsideThroneRoom::MapKeyQuest = "outside-throne-room";

OutsideThroneRoom* OutsideThroneRoom::create(GameObject* owner, QuestLine* questLine)
{
	OutsideThroneRoom* instance = new OutsideThroneRoom(owner, questLine);

	instance->autorelease();

	return instance;
}

OutsideThroneRoom::OutsideThroneRoom(GameObject* owner, QuestLine* questLine) : super(owner, questLine, OutsideThroneRoom::MapKeyQuest, false)
{
}

OutsideThroneRoom::~OutsideThroneRoom()
{
}

void OutsideThroneRoom::onEnter()
{
	super::onEnter();
}

void OutsideThroneRoom::onLoad(QuestState questState)
{
	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKey);

	ObjectEvents::WatchForObject<Tyracius>(this, [=](Tyracius* tyracius)
	{
		this->tyracius = tyracius;

		this->attachTyraciusBehavior();
	}, Tyracius::MapKey);
}

void OutsideThroneRoom::onActivate(bool isActiveThroughSkippable, bool isInitialActivation)
{
}

void OutsideThroneRoom::attachTyraciusBehavior()
{
	if (this->tyracius == nullptr)
	{
		return;
	}

	this->tyracius->watchForComponent<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
	{
		interactionBehavior->getMainDialogueSet()->addDialogueOption(DialogueOption::create(
			Strings::Platformer_Quests_CastleValgrind_CureKing_Tyracius_A_WhatAreYouDoingHere::create(),
			[=]()
			{
				if (this->questLine->isCompleteUpToInclusive(DefeatAgnes::MapKeyQuest))
				{
					DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
						Strings::Platformer_Quests_CastleValgrind_CureKing_Tyracius_S_StayHidden::create(),
						DialogueEvents::DialogueVisualArgs(
							DialogueBox::DialogueDock::Bottom,
							DialogueBox::DialogueAlignment::Right,
							DialogueEvents::BuildPreviewNode(&this->squally, false),
							DialogueEvents::BuildPreviewNode(&this->tyracius, true)
						),
						[=]()
						{
						},
						Voices::GetNextVoiceLong()
					));
				}
				else
				{
					DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
						Strings::Platformer_Quests_CastleValgrind_CureKing_Tyracius_B_Coward::create(),
						DialogueEvents::DialogueVisualArgs(
							DialogueBox::DialogueDock::Bottom,
							DialogueBox::DialogueAlignment::Right,
							DialogueEvents::BuildPreviewNode(&this->squally, false),
							DialogueEvents::BuildPreviewNode(&this->tyracius, true)
						),
						[=]()
						{
						},
						Voices::GetNextVoiceLong()
					));
				}
			}),
			1.0f
		);
	});
}

void OutsideThroneRoom::onComplete()
{
}

void OutsideThroneRoom::onSkipped()
{
	this->removeAllListeners();
}
