#include "WaterBlessing.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Dialogue/DialogueOption.h"
#include "Engine/Dialogue/DialogueSet.h"
#include "Engine/Dialogue/SpeechBubble.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Events/QuestEvents.h"
#include "Engine/Save/SaveManager.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/NotificationEvents.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/Hackables/HackFlags.h"
#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/ObjectResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string WaterBlessing::MapKeyQuest = "water-blessing";

WaterBlessing* WaterBlessing::create(GameObject* owner, QuestLine* questLine)
{
	WaterBlessing* instance = new WaterBlessing(owner, questLine);

	instance->autorelease();

	return instance;
}

WaterBlessing::WaterBlessing(GameObject* owner, QuestLine* questLine) : super(owner, questLine, WaterBlessing::MapKeyQuest, false)
{
	this->squally = nullptr;
	this->entity = static_cast<PlatformerEntity*>(owner);
}

WaterBlessing::~WaterBlessing()
{
}

void WaterBlessing::onLoad(QuestState questState)
{
	ObjectEvents::watchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
		this->squally->toggleAllowFx(true);
		
	}, Squally::MapKeySqually);

	if (questState == QuestState::Complete &&
		QuestTask::getQuestStateForTask(this->questLine, WaterBlessing::MapKeyQuest) == QuestState::None)
	{
		this->setPostText();
	}
}

void WaterBlessing::onActivate(bool isActiveThroughSkippable)
{
	this->runCinematicSequence();
}

void WaterBlessing::onComplete()
{
	SaveManager::SaveProfileData(SaveKeys::SaveKeyBlessingOfWater, Value(true));
	HackableObject::SetHackFlags(HackFlagUtils::GetCurrentHackFlags());
	
	NotificationEvents::TriggerNotification(NotificationEvents::NotificationArgs(
		Strings::Platformer_Blessings_BlessingGranted::create(),
		Strings::Platformer_Blessings_BlessingOfWater::create(),
		ObjectResources::Items_Misc_EssenceOfWater,
		SoundResources::Notifications_NotificationGood1
	));
}

void WaterBlessing::onSkipped()
{
}

void WaterBlessing::runCinematicSequence()
{
	if (this->entity == nullptr)
	{
		return;
	}

	this->entity->watchForAttachedBehavior<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
	{
		// Pre-text chain
		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_EndianForest_WaterBlessing_Merlin_A_ThankYou::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Left,
				DialogueEvents::BuildPreviewNode(&this->entity, false),
				DialogueEvents::BuildPreviewNode(&this->squally, true)
			),
			[=]()
			{
			},
			SoundResources::Platformer_Entities_Generic_ChatterMedium1,
			false
		));

		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_EndianForest_WaterBlessing_Merlin_B_GraspPowers::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Left,
				DialogueEvents::BuildPreviewNode(&this->entity, false),
				DialogueEvents::BuildPreviewNode(&this->squally, true)
			),
			[=]()
			{
			},
			SoundResources::Platformer_Entities_Generic_ChatterMedium2,
			false
		));

		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_EndianForest_WaterBlessing_Merlin_C_GrantBlessing::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Left,
				DialogueEvents::BuildPreviewNode(&this->entity, false),
				DialogueEvents::BuildPreviewNode(&this->squally, true)
			),
			[=]()
			{
			},
			SoundResources::Platformer_Entities_Generic_ChatterMedium3,
			false
		));

		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_EndianForest_WaterBlessing_Merlin_D_UseYourPowers::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Left,
				DialogueEvents::BuildPreviewNode(&this->entity, false),
				DialogueEvents::BuildPreviewNode(&this->squally, true)
			),
			[=]()
			{
				this->setPostText();
				this->complete();
			},
			SoundResources::Platformer_Entities_Generic_ChatterMedium4,
			true
		));
	});
}

void WaterBlessing::setPostText()
{
	this->defer([=]()
	{
		this->entity->watchForAttachedBehavior<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
		{
			interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_EndianForest_WaterBlessing_Merlin_D_UseYourPowers::create(),
				DialogueEvents::DialogueVisualArgs(
					DialogueBox::DialogueDock::Bottom,
					DialogueBox::DialogueAlignment::Left,
					DialogueEvents::BuildPreviewNode(&this->entity, false),
					DialogueEvents::BuildPreviewNode(&this->squally, true)
				),
				[=]()
				{
					this->setPostText();
				},
				SoundResources::Platformer_Entities_Generic_ChatterMedium2,
				true
			));
		});
	});
}
