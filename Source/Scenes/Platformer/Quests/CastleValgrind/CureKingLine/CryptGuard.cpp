#include "CryptGuard.h"

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
#include "Entities/Platformer/Npcs/CastleValgrind/Zana.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/DialogueEvents.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/Components/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/Dialogue/DialogueSet.h"
#include "Scenes/Platformer/Dialogue/Voices.h"
#include "Scenes/Platformer/Level/Physics/PlatformerPhysicsTypes.h"

#include "Resources/EntityResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string CryptGuard::MapKeyQuest = "crypt-guard";

CryptGuard* CryptGuard::create(GameObject* owner, QuestLine* questLine)
{
	CryptGuard* instance = new CryptGuard(owner, questLine);

	instance->autorelease();

	return instance;
}

CryptGuard::CryptGuard(GameObject* owner, QuestLine* questLine) : super(owner, questLine, CryptGuard::MapKeyQuest, false)
{
}

CryptGuard::~CryptGuard()
{
}

void CryptGuard::onEnter()
{
	super::onEnter();
}

void CryptGuard::onLoad(QuestState questState)
{
	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKey);

	ObjectEvents::WatchForObject<Zana>(this, [=](Zana* zana)
	{
		this->zana = zana;

		this->attachZanaBehavior();
	}, Zana::MapKey);

	ObjectEvents::WatchForObject<Portal>(this, [=](Portal* portal)
	{
		this->cryptDoor = portal;
	}, "crypt-door");
}

void CryptGuard::onActivate(bool isActiveThroughSkippable, bool isInitialActivation)
{
}

void CryptGuard::attachZanaBehavior()
{
	if (this->zana == nullptr)
	{
		return;
	}

	this->zana->watchForComponent<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
	{
		interactionBehavior->getMainDialogueSet()->addDialogueOption(DialogueOption::create(
			Strings::Platformer_Quests_CastleValgrind_CureKing_Zana_A_WhatIsThisPlace::create(),
			[=]()
			{
				DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
					Strings::Platformer_Quests_CastleValgrind_CureKing_Zana_B_AncientCrypt::create()
						->setStringReplacementVariables(Strings::Platformer_MapNames_LambdaCrypts_LambdaCrypts::create()),
					DialogueEvents::DialogueVisualArgs(
						DialogueBox::DialogueDock::Bottom,
						DialogueBox::DialogueAlignment::Right,
						DialogueEvents::BuildPreviewNode(&this->squally, false),
						DialogueEvents::BuildPreviewNode(&this->zana, true)
					),
					[=]()
					{
						if (this->cryptDoor != nullptr && this->cryptDoor->getIsLocked())
						{
							DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
								Strings::Platformer_Quests_CastleValgrind_CureKing_Zana_C_Locked::create()
									->setStringReplacementVariables(
									{
										Strings::Platformer_Entities_Names_Npcs_CastleValgrind_KingRedsong::create(),
										Strings::Platformer_MapNames_CastleValgrind_CastleValgrind::create()
									}),
								DialogueEvents::DialogueVisualArgs(
									DialogueBox::DialogueDock::Bottom,
									DialogueBox::DialogueAlignment::Right,
									DialogueEvents::BuildPreviewNode(&this->squally, false),
									DialogueEvents::BuildPreviewNode(&this->zana, true)
								),
								[=]()
								{
								},
								Voices::GetNextVoiceLong()
							));
						}
					},
					Voices::GetNextVoiceLong()
				));
			}),
			1.0f
		);
	});
}

void CryptGuard::onComplete()
{
}

void CryptGuard::onSkipped()
{
	this->removeAllListeners();
}
