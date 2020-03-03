#include "TalkToMages.h"

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
#include "Entities/Platformer/Npcs/SeaSharpCaverns/Sarude.h"
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

const std::string TalkToMages::MapKeyQuest = "talk-to-mages";

TalkToMages* TalkToMages::create(GameObject* owner, QuestLine* questLine)
{
	TalkToMages* instance = new TalkToMages(owner, questLine);

	instance->autorelease();

	return instance;
}

TalkToMages::TalkToMages(GameObject* owner, QuestLine* questLine) : super(owner, questLine, TalkToMages::MapKeyQuest, false)
{
	this->squally = nullptr;
	this->sarude = nullptr;
}

TalkToMages::~TalkToMages()
{
}

void TalkToMages::onLoad(QuestState questState)
{
	ObjectEvents::watchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKeySqually);

	ObjectEvents::watchForObject<Sarude>(this, [=](Sarude* sarude)
	{
		this->sarude = sarude;
	}, Sarude::MapKeySarude);
}

void TalkToMages::onActivate(bool isActiveThroughSkippable)
{
}

void TalkToMages::onComplete()
{
	SaveManager::SaveProfileData(SaveKeys::SaveKeyBlessingOfWind, Value(true));
	HackableObject::SetHackFlags(HackFlagUtils::GetCurrentHackFlags());
	
	NotificationEvents::TriggerNotification(NotificationEvents::NotificationArgs(
		Strings::Platformer_Blessings_BlessingGranted::create(),
		Strings::Platformer_Blessings_BlessingOfWind::create(),
		ObjectResources::Items_Misc_EssenceOfWind,
		SoundResources::Notifications_NotificationGood1
	));
}

void TalkToMages::onSkipped()
{
}

void TalkToMages::runCinematicSequence()
{
	if (this->sarude == nullptr)
	{
		return;
	}

	this->sarude->watchForAttachedBehavior<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
	{
		// Pre-text chain
		/*
		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_EndianForest_TalkToMages_Marcel_A_GoodUse::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Right,
				DialogueEvents::BuildPreviewNode(&this->sarude, false),
				DialogueEvents::BuildPreviewNode(&this->squally, true)
			),
			[=]()
			{
			},
			SoundResources::Platformer_Entities_Generic_ChatterQuestion1,
			false
		));

		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_EndianForest_TalkToMages_Marcel_B_Latent::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Right,
				DialogueEvents::BuildPreviewNode(&this->sarude, false),
				DialogueEvents::BuildPreviewNode(&this->squally, true)
			),
			[=]()
			{
				this->complete();
			},
			SoundResources::Platformer_Entities_Generic_ChatterQuestion1,
			true
		));
		*/
	});
}
