#include "WindSpellbook.h"

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
#include "Engine/Save/SaveManager.h"
#include "Entities/Platformer/Npcs/EndianForest/Marcel.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/NotificationEvents.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/Dialogue/DialogueSet.h"
#include "Scenes/Platformer/Hackables/HackFlags.h"
#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/ItemResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string WindSpellbook::MapKeyQuest = "wind-spellbook";

WindSpellbook* WindSpellbook::create(GameObject* owner, QuestLine* questLine)
{
	WindSpellbook* instance = new WindSpellbook(owner, questLine);

	instance->autorelease();

	return instance;
}

WindSpellbook::WindSpellbook(GameObject* owner, QuestLine* questLine) : super(owner, questLine, WindSpellbook::MapKeyQuest, false)
{
	this->squally = nullptr;
	this->marcel = nullptr;
}

WindSpellbook::~WindSpellbook()
{
}

void WindSpellbook::onLoad(QuestState questState)
{
	ObjectEvents::watchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKey);

	ObjectEvents::watchForObject<Marcel>(this, [=](Marcel* marcel)
	{
		this->marcel = marcel;

		if (questState == QuestState::Active || questState == QuestState::ActiveThroughSkippable)
		{
			this->runCinematicSequence();
		}
	}, Marcel::MapKey);
}

void WindSpellbook::onActivate(bool isActiveThroughSkippable)
{
}

void WindSpellbook::onComplete()
{
	SaveManager::SaveProfileData(SaveKeys::SaveKeyBlessingOfWind, Value(true));
	HackableObject::SetHackFlags(HackFlagUtils::GetCurrentHackFlags());
	
	NotificationEvents::TriggerNotification(NotificationEvents::NotificationArgs(
		Strings::Platformer_Spellbooks_SpellbookAcquired::create(),
		Strings::Platformer_Spellbooks_SpellbookOfWind::create(),
		ItemResources::Spellbooks_SpellBookWind,
		SoundResources::Notifications_NotificationGood1
	));
}

void WindSpellbook::onSkipped()
{
}

void WindSpellbook::runCinematicSequence()
{
	if (this->marcel == nullptr)
	{
		return;
	}

	this->marcel->watchForAttachedBehavior<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
	{
		// Pre-text chain
		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_EndianForest_WindSpellbook_Marcel_A_GoodUse::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Right,
				DialogueEvents::BuildPreviewNode(&this->marcel, false),
				DialogueEvents::BuildPreviewNode(&this->squally, true)
			),
			[=]()
			{
			},
			SoundResources::Platformer_Entities_Generic_ChatterMedium4,
			false
		));

		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_EndianForest_WindSpellbook_Marcel_B_Latent::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Right,
				DialogueEvents::BuildPreviewNode(&this->marcel, false),
				DialogueEvents::BuildPreviewNode(&this->squally, true)
			),
			[=]()
			{
				this->complete();
			},
			SoundResources::Platformer_Entities_Generic_ChatterMedium2,
			true
		));
	});
}
