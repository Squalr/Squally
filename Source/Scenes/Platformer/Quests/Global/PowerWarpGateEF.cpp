#include "PowerWarpGateEF.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"

#include "Engine/Dialogue/DialogueOption.h"
#include "Engine/Events/ObjectEvents.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Objects/Platformer/Interactables/Doors/Portal.h"
#include "Objects/Platformer/Switches/Trigger.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/Dialogue/DialogueSet.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string PowerWarpGateEF::MapKeyQuest = "power-warp-gate-ef";

PowerWarpGateEF* PowerWarpGateEF::create(GameObject* owner, QuestLine* questLine)
{
	PowerWarpGateEF* instance = new PowerWarpGateEF(owner, questLine);

	instance->autorelease();

	return instance;
}

PowerWarpGateEF::PowerWarpGateEF(GameObject* owner, QuestLine* questLine) : super(owner, questLine, PowerWarpGateEF::MapKeyQuest, false)
{
	this->portal = dynamic_cast<Portal*>(owner);
	this->trigger = dynamic_cast<Trigger*>(owner);
	this->mage = dynamic_cast<PlatformerEntity*>(owner);
	this->squally = nullptr;
}

PowerWarpGateEF::~PowerWarpGateEF()
{
}

void PowerWarpGateEF::onLoad(QuestState questState)
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

			this->listenForMapEventOnce(PowerWarpGateEF::MapKeyQuest, [=](ValueMap)
			{
				this->mage->runAction(FadeTo::create(0.5f, 255));
				this->complete();
			});
		}

		if (this->trigger != nullptr)
		{
			this->listenForMapEventOnce(PowerWarpGateEF::MapKeyQuest, [=](ValueMap)
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

void PowerWarpGateEF::onActivate(bool isActiveThroughSkippable)
{
}

void PowerWarpGateEF::onComplete()
{
	if (this->portal != nullptr)
	{
		this->portal->unlock(true);
	}
}

void PowerWarpGateEF::onSkipped()
{
	if (this->portal != nullptr)
	{
		this->portal->unlock(true);
	}
}

void PowerWarpGateEF::runCinematicSequence()
{
	this->mage->watchForAttachedBehavior<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
	{
		interactionBehavior->getMainDialogueSet()->addDialogueOption(DialogueOption::create(
			Strings::Platformer_Quests_WarpGates_WhatIsThisPlace::create(),
			[=]()
			{
				DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
					Strings::Platformer_Quests_WarpGates_WarpGateIntro::create(),
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
