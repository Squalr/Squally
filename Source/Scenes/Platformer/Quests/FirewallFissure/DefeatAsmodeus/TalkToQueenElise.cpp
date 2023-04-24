#include "TalkToQueenElise.h"

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
#include "Entities/Platformer/Npcs/FirewallFissure/QueenElise.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/NotificationEvents.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Interactables/Doors/Portal.h"
#include "Scenes/Platformer/Components/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/Components/Entities/Visual/EntityQuestVisualBehavior.h"
#include "Scenes/Platformer/Dialogue/Voices.h"
#include "Scenes/Platformer/Hackables/HackFlags.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"
#include "Scenes/Platformer/Objectives/ObjectiveKeys.h"
#include "Scenes/Platformer/Objectives/Objectives.h"
#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/EntityResources.h"
#include "Resources/ItemResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string TalkToQueenElise::MapKeyQuest = "talk-to-queen-elise";
const std::string TalkToQueenElise::MapEventTalkToQueenElise = "talk-to-queen-elise";

TalkToQueenElise* TalkToQueenElise::create(GameObject* owner, QuestLine* questLine)
{
	TalkToQueenElise* instance = new TalkToQueenElise(owner, questLine);

	instance->autorelease();

	return instance;
}

TalkToQueenElise::TalkToQueenElise(GameObject* owner, QuestLine* questLine) : super(owner, questLine, TalkToQueenElise::MapKeyQuest, false)
{
}

TalkToQueenElise::~TalkToQueenElise()
{
}

void TalkToQueenElise::onLoad(QuestState questState)
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

	ObjectEvents::WatchForObject<QueenElise>(this, [=](QueenElise* queenElise)
	{
		this->queenElise = queenElise;
	});

	if (questState == QuestState::Active || questState == QuestState::ActiveThroughSkippable)
	{
		this->listenForMapEventOnce(TalkToQueenElise::MapEventTalkToQueenElise, [=](ValueMap)
		{
			this->runCinematicSequencePt1();
		});
	}
}

void TalkToQueenElise::onActivate(bool isActiveThroughSkippable)
{
}

void TalkToQueenElise::onComplete()
{	
	Objectives::SetCurrentObjective(ObjectiveKeys::FFCraftBomb);
	PlatformerEvents::TriggerGiveItems(PlatformerEvents::GiveItemsArgs({ UnstableConcoction::create(), UnstableElement::create() }));
}

void TalkToQueenElise::onSkipped()
{
	this->removeAllListeners();
}

void TalkToQueenElise::runCinematicSequencePt1()
{
	PlatformerEvents::TriggerCinematicHijack();

	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_FirewallFissure_DefeatAsmodeus_A_HowToLeaveVolcano::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Right,
			DialogueEvents::BuildPreviewNode(&this->queenElise, false),
			DialogueEvents::BuildPreviewNode(&this->scrappy, true)
		),
		[=]()
		{
			this->runCinematicSequencePt2();
		},
		Voices::GetNextVoiceMedium(Voices::VoiceType::Droid),
		false
	));
}

void TalkToQueenElise::runCinematicSequencePt2()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_FirewallFissure_DefeatAsmodeus_B_AsmodeusBlocking::create()
			->setStringReplacementVariables(Strings::Platformer_Entities_Names_Enemies_FirewallFissure_Asmodeus::create()),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Left,
			DialogueEvents::BuildPreviewNode(&this->queenElise, false),
			DialogueEvents::BuildPreviewNode(&this->scrappy, true)
		),
		[=]()
		{
			this->runCinematicSequencePt3();
		},
		Voices::GetNextVoiceLong(Voices::VoiceType::Human),
		false
	));
}

void TalkToQueenElise::runCinematicSequencePt3()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_FirewallFissure_DefeatAsmodeus_C_CraftABomb::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Left,
			DialogueEvents::BuildPreviewNode(&this->queenElise, false),
			DialogueEvents::BuildPreviewNode(&this->scrappy, true)
		),
		[=]()
		{
			this->runCinematicSequencePt4();
		},
		Voices::GetNextVoiceLong(Voices::VoiceType::Human),
		false
	));
}

void TalkToQueenElise::runCinematicSequencePt4()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_FirewallFissure_DefeatAsmodeus_D_GoToAlchLab::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Left,
			DialogueEvents::BuildPreviewNode(&this->queenElise, false),
			DialogueEvents::BuildPreviewNode(&this->scrappy, true)
		),
		[=]()
		{
			this->runCinematicSequencePt5();
		},
		Voices::GetNextVoiceLong(Voices::VoiceType::Human),
		false
	));
}

void TalkToQueenElise::runCinematicSequencePt5()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_FirewallFissure_DefeatAsmodeus_E_Acknowledged::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Right,
			DialogueEvents::BuildPreviewNode(&this->queenElise, false),
			DialogueEvents::BuildPreviewNode(&this->scrappy, true)
		),
		[=]()
		{
			this->complete();
		},
		Voices::GetNextVoiceShort(Voices::VoiceType::Droid),
		true
	));
}
