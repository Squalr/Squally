#include "TalkToZeus.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Camera/GameCamera.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Quests/QuestLine.h"
#include "Engine/Save/SaveManager.h"
#include "Entities/Platformer/Helpers/EndianForest/Guano.h"
#include "Entities/Platformer/Helpers/EndianForest/Scrappy.h"
#include "Entities/Platformer/Npcs/UnderflowRuins/Zeus.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/NotificationEvents.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Interactables/Doors/Portal.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Visual/EntityQuestVisualBehavior.h"
#include "Scenes/Platformer/Hackables/HackFlags.h"
#include "Scenes/Platformer/Inventory/Items/Misc/Keys/UnderflowRuins/MedusaMirror.h"
#include "Scenes/Platformer/Objectives/Objectives.h"
#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/EntityResources.h"
#include "Resources/ItemResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string TalkToZeus::MapKeyQuest = "talk-to-zeus";
const std::string TalkToZeus::TagTownCinematic = "town-cinematic";

TalkToZeus* TalkToZeus::create(GameObject* owner, QuestLine* questLine)
{
	TalkToZeus* instance = new TalkToZeus(owner, questLine);

	instance->autorelease();

	return instance;
}

TalkToZeus::TalkToZeus(GameObject* owner, QuestLine* questLine) : super(owner, questLine, TalkToZeus::MapKeyQuest, false)
{
	this->guano = nullptr;
	this->scrappy = nullptr;
	this->squally = nullptr;
	this->zeus = nullptr;
}

TalkToZeus::~TalkToZeus()
{
}

void TalkToZeus::onLoad(QuestState questState)
{
	ObjectEvents::WatchForObject<Guano>(this, [=](Guano* guano)
	{
		this->guano = guano;
	}, Guano::MapKey);

	ObjectEvents::WatchForObject<Scrappy>(this, [=](Scrappy* scrappy)
	{
		this->scrappy = scrappy;
	}, Scrappy::MapKey);

	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKey);

	ObjectEvents::WatchForObject<Zeus>(this, [=](Zeus* zeus)
	{
		this->zeus = zeus;
	});

	if (questState == QuestState::Active || questState == QuestState::ActiveThroughSkippable)
	{
		this->listenForMapEventOnce(TalkToZeus::MapKeyQuest, [=](ValueMap)
		{
			this->runCinematicSequencePt1();
		});
	}
}

void TalkToZeus::onActivate(bool isActiveThroughSkippable)
{
}

void TalkToZeus::onComplete()
{
	PlatformerEvents::TriggerGiveItem(PlatformerEvents::GiveItemArgs(MedusaMirror::create()));
	SaveManager::SaveProfileData(SaveKeys::SaveKeySpellBookLightning, Value(true));
	HackableObject::SetHackFlags(HackFlagUtils::GetCurrentHackFlags());
	
	NotificationEvents::TriggerNotification(NotificationEvents::NotificationArgs(
		Strings::Platformer_Spellbooks_SpellbookAcquired::create(),
		Strings::Platformer_Spellbooks_SpellbookLightning::create(),
		ItemResources::Spellbooks_SpellBookLightning,
		SoundResources::Notifications_NotificationGood1
	));
	Objectives::SetCurrentObjective(ObjectiveKeys::URHeadToTown);
}

void TalkToZeus::onSkipped()
{
	this->removeAllListeners();
}

void TalkToZeus::runCinematicSequencePt1()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_UnderflowRuins_CureTown_Zeus_A_WhoGoesThere::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Left,
			DialogueEvents::BuildPreviewNode(&this->zeus, false),
			DialogueEvents::BuildPreviewNode(&this->squally, true)
		),
		[=]()
		{
			this->runCinematicSequencePt2();
		},
		SoundResources::Platformer_Entities_Generic_ChatterMedium4,
		false
	));
}

void TalkToZeus::runCinematicSequencePt2()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Ellipses::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Right,
			DialogueEvents::BuildPreviewNode(&this->zeus, false),
			DialogueEvents::BuildPreviewNode(&this->squally, true),
			true
		),
		[=]()
		{
			this->runCinematicSequencePt3();
		},
		"",
		false
	));
}

void TalkToZeus::runCinematicSequencePt3()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_UnderflowRuins_CureTown_Zeus_B_SayNoMore::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Left,
			DialogueEvents::BuildPreviewNode(&this->zeus, false),
			DialogueEvents::BuildPreviewNode(&this->scrappy, true)
		),
		[=]()
		{
			this->complete();
		},
		SoundResources::Platformer_Entities_Generic_ChatterMedium2,
		true
	));
}
