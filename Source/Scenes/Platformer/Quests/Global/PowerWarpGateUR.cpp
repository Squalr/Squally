#include "PowerWarpGateUR.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"

#include "Engine/Dialogue/DialogueOption.h"
#include "Engine/Events/ObjectEvents.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Objects/Platformer/Interactables/Doors/Portal.h"
#include "Objects/Platformer/Switches/Trigger.h"
#include "Scenes/Platformer/Components/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/Dialogue/DialogueSet.h"
#include "Scenes/Platformer/Dialogue/Voices.h"

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
	this->squally = nullptr;
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

	if (questState != QuestState::Complete)
	{
		if (this->mage != nullptr)
		{
			this->mage->setOpacity(0);

			this->listenForMapEventOnce(PowerWarpGateUR::MapKeyQuest, [=](ValueMap)
			{
				this->mage->runAction(FadeTo::create(0.5f, 255));
				this->complete();
			});
		}

		if (this->trigger != nullptr)
		{
			this->listenForMapEventOnce(PowerWarpGateUR::MapKeyQuest, [=](ValueMap)
			{
				this->complete();
			});
		}
	}

	if (this->mage != nullptr)
	{
		this->runCinematicSequence();
	}
}

void PowerWarpGateUR::onActivate(bool isActiveThroughSkippable)
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

void PowerWarpGateUR::runCinematicSequence()
{
	this->mage->watchForComponent<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
	{
		interactionBehavior->getMainDialogueSet()->addDialogueOption(DialogueOption::create(
			Strings::Platformer_Quests_WarpGates_WhatIsThisPlace::create(),
			[=]()
			{
				DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
					Strings::Platformer_Quests_WarpGates_WarpGateDiscovered::create(),
					DialogueEvents::DialogueVisualArgs(
						DialogueBox::DialogueDock::Bottom,
						DialogueBox::DialogueAlignment::Right,
						DialogueEvents::BuildPreviewNode(&this->squally, false),
						DialogueEvents::BuildPreviewNode(&this->mage, true)
					),
					[=]()
					{
					},
					Voices::GetNextVoiceLong(),
					true
				));
			}),
			0.5f
		);
	});
}
