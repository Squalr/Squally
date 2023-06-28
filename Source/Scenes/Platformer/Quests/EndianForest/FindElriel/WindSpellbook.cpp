#include "WindSpellbook.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Dialogue/SpeechBubble.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Events/QuestEvents.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/Helpers/EndianForest/Guano.h"
#include "Entities/Platformer/Helpers/EndianForest/Scrappy.h"
#include "Entities/Platformer/Npcs/EndianForest/QueenLiana.h"
#include "Entities/Platformer/Npcs/Mages/Marcel.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/NotificationEvents.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Cinematic/CinematicMarker.h"
#include "Scenes/Platformer/Components/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/Components/Entities/Visual/EntityQuestVisualBehavior.h"
#include "Scenes/Platformer/Dialogue/DialogueSet.h"
#include "Scenes/Platformer/Dialogue/Voices.h"
#include "Scenes/Platformer/Hackables/HackFlags.h"
#include "Scenes/Platformer/Objectives/ObjectiveKeys.h"
#include "Scenes/Platformer/Objectives/Objectives.h"
#include "Scenes/Platformer/Save/SaveKeys.h"
#include "Scenes/Platformer/State/StateKeys.h"

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
}

WindSpellbook::~WindSpellbook()
{
}

void WindSpellbook::onLoad(QuestState questState)
{
	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKey);

	ObjectEvents::WatchForObject<Guano>(this, [=](Guano* guano)
	{
		this->guano = guano;
	}, Guano::MapKey);

	ObjectEvents::WatchForObject<Scrappy>(this, [=](Scrappy* scrappy)
	{
		this->scrappy = scrappy;
	}, Scrappy::MapKey);
	
	ObjectEvents::WatchForObject<QueenLiana>(this, [=](QueenLiana* queenLiana)
	{
		this->queenLiana = queenLiana;
	}, QueenLiana::MapKey);

	ObjectEvents::WatchForObject<CinematicMarker>(this, [=](CinematicMarker* cinematicMarker)
	{
		this->marcelLeave = cinematicMarker;
	}, "marcel-leave");

	ObjectEvents::WatchForObject<CinematicMarker>(this, [=](CinematicMarker* cinematicMarker)
	{
		this->marcelArrive = cinematicMarker;
	}, "marcel-arrive");

	ObjectEvents::WatchForObject<Marcel>(this, [=](Marcel* marcel)
	{
		this->marcel = marcel;
		this->marcel->setVisible(false);

		// Wait a frame for all objects to be guaranteed queried
		this->defer([=]()
		{
			if (questState == QuestState::Active || questState == QuestState::ActiveThroughSkippable)
			{
				// Interrupted by a map reload or game quit, just start the next segment
				this->runCinematicSequencePart1();
			}
			else
			{
				// Normal flow, wait for the event triggered by previous quest completion
				this->marcel->listenForMapEventOnce(Marcel::MapKey, [=](ValueMap)
				{
					this->runCinematicSequencePart1();
				});
			}
		});
	}, Marcel::MapKey);
}

void WindSpellbook::onActivate(bool isActiveThroughSkippable, bool isInitialActivation)
{
}

void WindSpellbook::onComplete()
{
	SaveManager::SaveProfileData(SaveKeys::SaveKeySpellBookWind, Value(true));
	HackableObject::SetHackFlags(HackFlagUtils::GetCurrentHackFlags());
	Objectives::SetCurrentObjective(ObjectiveKeys::EFHeadNorth);
	
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

void WindSpellbook::runCinematicSequencePart1()
{
	if (this->marcel != nullptr)
	{
		this->marcel->setVisible(true);
		this->marcel->setState(StateKeys::CinematicHijacked, Value(true));
		this->marcel->setState(StateKeys::CinematicSourceX, Value(GameUtils::getWorldCoords(this->marcel).x));
		this->marcel->setState(StateKeys::CinematicDestinationX, Value(GameUtils::getWorldCoords(this->marcelArrive).x));
	}
	
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_EndianForest_FindElriel_Lianna_T_MoreOrcs::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Left,
			DialogueEvents::BuildPreviewNode(&this->marcel, false),
			DialogueEvents::BuildPreviewNode(&this->squally, true)
		),
		[=]()
		{
			this->runCinematicSequencePart2();
		},
		Voices::GetNextVoiceMedium(),
		false
	));
}

void WindSpellbook::runCinematicSequencePart2()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_EndianForest_FindElriel_Lianna_U_SquallyCallUpon::create()
			->setStringReplacementVariables(Strings::Common_Squally::create()),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Left,
			DialogueEvents::BuildPreviewNode(&this->marcel, false),
			DialogueEvents::BuildPreviewNode(&this->squally, true)
		),
		[=]()
		{
			this->runCinematicSequencePart3();
		},
		Voices::GetNextVoiceMedium(),
		false
	));
}

void WindSpellbook::runCinematicSequencePart3()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_EndianForest_FindElriel_Lianna_V_NoChoice::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Right,
			DialogueEvents::BuildPreviewNode(&this->marcel, false),
			DialogueEvents::BuildPreviewNode(&this->guano, true)
		),
		[=]()
		{
			this->runCinematicSequencePart4();
		},
		Voices::GetNextVoiceMedium(),
		false
	));
}

void WindSpellbook::runCinematicSequencePart4()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_EndianForest_FindElriel_Lianna_W_Ships::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Right,
			DialogueEvents::BuildPreviewNode(&this->squally, false),
			DialogueEvents::BuildPreviewNode(&this->queenLiana, true)
		),
		[=]()
		{
			this->runCinematicSequencePart5();
		},
		Voices::GetNextVoiceLong(),
		false
	));
}

void WindSpellbook::runCinematicSequencePart5()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_EndianForest_FindElriel_Lianna_X_VisitShops::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Right,
			DialogueEvents::BuildPreviewNode(&this->squally, false),
			DialogueEvents::BuildPreviewNode(&this->queenLiana, true)
		),
		[=]()
		{
			this->runCinematicSequencePart6();
		},
		Voices::GetNextVoiceMedium(),
		false
	));
}

void WindSpellbook::runCinematicSequencePart6()
{
	if (this->marcel != nullptr)
	{
		this->marcel->setState(StateKeys::CinematicHijacked, Value(true));
		this->marcel->setState(StateKeys::CinematicSourceX, Value(GameUtils::getWorldCoords(this->marcel).x));
		this->marcel->setState(StateKeys::CinematicDestinationX, Value(GameUtils::getWorldCoords(this->marcelLeave).x));

		this->marcel->listenForStateWriteOnce(StateKeys::CinematicDestinationReached, [=](Value value)
		{
			this->marcel->despawn();
		});
	}

	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_EndianForest_FindElriel_Lianna_Y_WindSpellbook::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Left,
			DialogueEvents::BuildPreviewNode(&this->marcel, false),
			DialogueEvents::BuildPreviewNode(&this->squally, true)
		),
		[=]()
		{
			// Ensure he remains hijacked so that he continue his cinematic walk
			this->marcel->setState(StateKeys::CinematicHijacked, Value(true));
			this->complete();
		},
		Voices::GetNextVoiceMedium(),
		true
	));
}
