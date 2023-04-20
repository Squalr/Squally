#include "MeetGrim.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Quests/QuestLine.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/Helpers/CastleValgrind/Grim.h"
#include "Entities/Platformer/Helpers/EndianForest/Guano.h"
#include "Entities/Platformer/Helpers/EndianForest/Scrappy.h"
#include "Entities/Platformer/Helpers/DataMines/Gecky.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/NotificationEvents.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Cinematic/CinematicMarker.h"
#include "Objects/Platformer/Interactables/Doors/Portal.h"
#include "Scenes/Platformer/Components/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/Components/Entities/Movement/EntityMovementBehavior.h"
#include "Scenes/Platformer/Components/Entities/Visual/EntityQuestVisualBehavior.h"
#include "Scenes/Platformer/Components/Objects/Illusions/DispelIllusionBehavior.h"
#include "Scenes/Platformer/Dialogue/Voices.h"
#include "Scenes/Platformer/Objectives/ObjectiveKeys.h"
#include "Scenes/Platformer/Objectives/Objectives.h"
#include "Scenes/Platformer/Quests/CastleValgrind/CureKingLine/UnhauntCastle.h"
#include "Scenes/Platformer/Save/SaveKeys.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string MeetGrim::MapKeyQuest = "meet-grim";
const std::string MeetGrim::MapEventMeetGrim = "meet-grim";
const std::string MeetGrim::MapTagCinematicGrim = "cinematic-grim";

MeetGrim* MeetGrim::create(GameObject* owner, QuestLine* questLine)
{
	MeetGrim* instance = new MeetGrim(owner, questLine);

	instance->autorelease();

	return instance;
}

MeetGrim::MeetGrim(GameObject* owner, QuestLine* questLine) : super(owner, questLine, MeetGrim::MapKeyQuest, false)
{
}

MeetGrim::~MeetGrim()
{
}

void MeetGrim::onLoad(QuestState questState)
{
	ObjectEvents::WatchForObject<Guano>(this, [=](Guano* guano)
	{
		this->guano = guano;
	}, Guano::MapKey);

	ObjectEvents::WatchForObject<Gecky>(this, [=](Gecky* gecky)
	{
		this->gecky = gecky;
	}, Gecky::MapKey);

	ObjectEvents::WatchForObject<Scrappy>(this, [=](Scrappy* scrappy)
	{
		this->scrappy = scrappy;
	}, Scrappy::MapKey);

	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKey);

	ObjectEvents::WatchForObject<Grim>(this, [=](Grim* grim)
	{
		this->grim = grim;
		
		if (questState != QuestState::Active && questState != QuestState::ActiveThroughSkippable)
		{
			this->grim->despawn();
		}

		// Disable grim from appearing on party menu
		this->grim->setQueryable(false);
	}, MeetGrim::MapTagCinematicGrim);
}

void MeetGrim::onActivate(bool isActiveThroughSkippable)
{
	this->listenForMapEventOnce(MeetGrim::MapEventMeetGrim, [=](ValueMap)
	{
		this->runCinematicSequencePt1();
	});

}

void MeetGrim::onComplete()
{
	this->removeAllListeners();
}

void MeetGrim::onSkipped()
{
	this->removeAllListeners();
}

void MeetGrim::runCinematicSequencePt1()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_CastleValgrind_CureKing_Grim_A_HelpYou::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Left,
			DialogueEvents::BuildPreviewNode(&this->grim, false),
			DialogueEvents::BuildPreviewNode(&this->squally, true)
		),
		[=]()
		{
			this->runCinematicSequencePt2();
		},
		Voices::GetNextVoiceMedium(),
		false
	));
}

void MeetGrim::runCinematicSequencePt2()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_CastleValgrind_CureKing_Grim_B_Translation::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Left,
			DialogueEvents::BuildPreviewNode(&this->scrappy, false),
			DialogueEvents::BuildPreviewNode(&this->squally, true)
		),
		[=]()
		{
			this->runCinematicSequencePt3();
		},
		Voices::GetNextVoiceMedium(),
		false
	));
}

void MeetGrim::runCinematicSequencePt3()
{
	if (this->gecky != nullptr)
	{
		DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_CastleValgrind_CureKing_Grim_C_Gecky_Later::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Left,
				DialogueEvents::BuildPreviewNode(&this->gecky, false),
				DialogueEvents::BuildPreviewNode(&this->squally, true)
			),
			[=]()
			{
				this->runCinematicSequencePt4();
			},
			Voices::GetNextVoiceMedium(),
			false
		));
	}
	else
	{
		DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_CastleValgrind_CureKing_Grim_C_Guano_Later::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Left,
				DialogueEvents::BuildPreviewNode(&this->guano, false),
				DialogueEvents::BuildPreviewNode(&this->squally, true)
			),
			[=]()
			{
				this->runCinematicSequencePt4();
			},
			Voices::GetNextVoiceMedium(),
			false
		));
	}
}

void MeetGrim::runCinematicSequencePt4()
{
	SaveManager::SoftSaveProfileData(SaveKeys::SaveKeyGrimFound, Value(true));
	this->squally->setState(StateKeys::CurrentHelper, Value(Grim::MapKey));

	// Despawn cinematic Grim
	if (this->grim != nullptr)
	{
		this->grim->despawn();
	}

	LocalizedString* hintString = Strings::Platformer_Help_HelpTotemGrim::create();
	LocalizedString* helperNameString = Strings::Platformer_Entities_Names_Helpers_CastleValgrind_Grim::create();
	LocalizedString* bracketString1 = Strings::Common_Brackets::create();
	LocalizedString* shiftString = Strings::Input_Shift::create();

	bracketString1->setStringReplacementVariables(shiftString);
	hintString->setStringReplacementVariables({ helperNameString, bracketString1 });

	NotificationEvents::TriggerNotificationTakeover(NotificationEvents::NotificationTakeoverArgs(
		Strings::Platformer_Notifications_Party_HelperJoinedParty::create()->setStringReplacementVariables(Strings::Platformer_Entities_Names_Helpers_CastleValgrind_Grim::create()),
		hintString,
		SoundResources::Notifications_NotificationGood1
	));

	PlatformerEvents::TriggerCinematicRestore();
	this->complete();
}
