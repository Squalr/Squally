#include "TalkToMabel.h"

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
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/Enemies/VoidStar/EvilEye.h"
#include "Entities/Platformer/Helpers/EndianForest/Guano.h"
#include "Entities/Platformer/Helpers/EndianForest/Scrappy.h"
#include "Entities/Platformer/Helpers/DataMines/Gecky.h"
#include "Entities/Platformer/Npcs/Mages/Mabel.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Camera/CameraStop.h"
#include "Objects/Platformer/Cinematic/CinematicMarker.h"
#include "Objects/Platformer/Interactables/Doors/Portal.h"
#include "Scenes/Platformer/Components/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/Components/Entities/Visual/EntityQuestVisualBehavior.h"
#include "Scenes/Platformer/Dialogue/Voices.h"
#include "Scenes/Platformer/Inventory/Items/Misc/Keys/CastleValgrind/StudyRoomKey.h"
#include "Scenes/Platformer/Objectives/ObjectiveKeys.h"
#include "Scenes/Platformer/Objectives/Objectives.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string TalkToMabel::MapKeyQuest = "talk-to-mabel";
const std::string TalkToMabel::MapEventMabelRevealed = "mabel-revealed";

TalkToMabel* TalkToMabel::create(GameObject* owner, QuestLine* questLine)
{
	TalkToMabel* instance = new TalkToMabel(owner, questLine);

	instance->autorelease();

	return instance;
}

TalkToMabel::TalkToMabel(GameObject* owner, QuestLine* questLine) : super(owner, questLine, TalkToMabel::MapKeyQuest, false)
{
}

TalkToMabel::~TalkToMabel()
{
}

void TalkToMabel::onLoad(QuestState questState)
{
	ObjectEvents::WatchForObject<EvilEye>(this, [=](EvilEye* evilEye)
	{
		this->evilEye = evilEye;
	}, EvilEye::MapKey);

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

	ObjectEvents::WatchForObject<Mabel>(this, [=](Mabel* mabel)
	{
		this->mabel = mabel;
	}, Mabel::MapKey);

	ObjectEvents::WatchForObject<CameraStop>(this, [=](CameraStop* cameraStop)
	{
		this->cameraStop = cameraStop;
		
		if (questState == QuestState::Complete)
		{
			this->cameraStop->disable();
		}
	}, "quest-camera-stop");

	ObjectEvents::WatchForObject<CollisionObject>(this, [=](CollisionObject* wall)
	{
		this->wall = wall;

		if (questState == QuestState::Complete)
		{
			this->wall->setPhysicsFlagEnabled(false);
		}
	}, "quest-solid-wall");
}

void TalkToMabel::onActivate(bool isActiveThroughSkippable)
{
	this->listenForMapEventOnce(TalkToMabel::MapEventMabelRevealed, [=](ValueMap valueMap)
	{
		this->runCinematicSequencePt1();
	});
}

void TalkToMabel::onComplete()
{
}

void TalkToMabel::onSkipped()
{
	this->removeAllListeners();
}

void TalkToMabel::runCinematicSequencePt1()
{
	if (this->mabel == nullptr)
	{
		return;
	}

	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_CastleValgrind_CureKing_Mabel_A_Ack::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Right,
			DialogueEvents::BuildPreviewNode(&this->squally, false),
			DialogueEvents::BuildPreviewNode(&this->mabel, true)
		),
		[=]()
		{
			if (this->cameraStop != nullptr)
			{
				this->cameraStop->disable();
			}

			if (this->wall != nullptr)
			{
				this->wall->setPhysicsFlagEnabled(false);
			}

			if (this->evilEye != nullptr)
			{
				ObjectEvents::WatchForObject<CinematicMarker>(this, [=](CinematicMarker* exit)
				{
					this->evilEye->setState(StateKeys::PatrolHijacked, Value(true));
					this->evilEye->setState(StateKeys::PatrolSourceX, Value(GameUtils::getWorldCoords(this->evilEye).x));
					this->evilEye->setState(StateKeys::PatrolDestinationX, Value(GameUtils::getWorldCoords(exit).x));
					
					this->evilEye->listenForStateWriteOnce(StateKeys::CinematicDestinationReached, [=](Value value)
					{
						this->evilEye->runAction(Sequence::create(
							FadeTo::create(0.5f, 0),
							CallFunc::create([=]()
							{
								this->evilEye->despawn();
								this->runCinematicSequencePt2();
							}),
							nullptr
						));
					});
				}, "exit");
			}
			else
			{
				this->runCinematicSequencePt2();
			}
		},
		Voices::GetNextVoiceMedium(),
		false
	));
}

void TalkToMabel::runCinematicSequencePt2()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_CastleValgrind_CureKing_Mabel_B_TellMeYouSawThat::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Right,
			DialogueEvents::BuildPreviewNode(&this->squally, false),
			DialogueEvents::BuildPreviewNode(&this->mabel, true)
		),
		[=]()
		{
			this->runCinematicSequencePt3();
		},
		Voices::GetNextVoiceMedium(),
		false
	));
}

void TalkToMabel::runCinematicSequencePt3()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_CastleValgrind_CureKing_Mabel_C_WentThroughTheClock::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Right,
			DialogueEvents::BuildPreviewNode(&this->squally, false),
			DialogueEvents::BuildPreviewNode(&this->mabel, true)
		),
		[=]()
		{
			this->runCinematicSequencePt4();
		},
		Voices::GetNextVoiceMedium(),
		false
	));
}

void TalkToMabel::runCinematicSequencePt4()
{
	if (this->gecky != nullptr)
	{
		DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_CastleValgrind_CureKing_Mabel_D_Gecky::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Left,
				DialogueEvents::BuildPreviewNode(&this->gecky, false),
				DialogueEvents::BuildPreviewNode(&this->mabel, true)
			),
			[=]()
			{
				this->runCinematicSequencePt5();
			},
			Voices::GetNextVoiceMedium(),
			false
		));
	}
	else
	{
		DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_CastleValgrind_CureKing_Mabel_D_Guano::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Left,
				DialogueEvents::BuildPreviewNode(&this->guano, false),
				DialogueEvents::BuildPreviewNode(&this->mabel, true)
			),
			[=]()
			{
				this->runCinematicSequencePt5();
			},
			Voices::GetNextVoiceMedium(),
			false
		));
	}
}

void TalkToMabel::runCinematicSequencePt5()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_CastleValgrind_CureKing_Mabel_E_DefeatSpirits::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Right,
			DialogueEvents::BuildPreviewNode(&this->squally, false),
			DialogueEvents::BuildPreviewNode(&this->mabel, true)
		),
		[=]()
		{
			this->runCinematicSequencePt6();
		},
		Voices::GetNextVoiceMedium(),
		true
	));
}

void TalkToMabel::runCinematicSequencePt6()
{
	PlatformerEvents::TriggerGiveItems(PlatformerEvents::GiveItemsArgs({ StudyRoomKey::create() }));
	this->complete();
}
