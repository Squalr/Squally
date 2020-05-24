#include "ArriveInAthens.h"

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
#include "Entities/Platformer/Helpers/EndianForest/Guano.h"
#include "Entities/Platformer/Helpers/EndianForest/Scrappy.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Objects/Platformer/Camera/CameraTarget.h"
#include "Objects/Platformer/Interactables/Doors/Portal.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Visual/EntityQuestVisualBehavior.h"
#include "Scenes/Platformer/Objectives/Objectives.h"

#include "Resources/EntityResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string ArriveInAthens::MapKeyQuest = "arrive-in-athens";
const std::string ArriveInAthens::TagTownCinematic = "town-cinematic";

ArriveInAthens* ArriveInAthens::create(GameObject* owner, QuestLine* questLine)
{
	ArriveInAthens* instance = new ArriveInAthens(owner, questLine);

	instance->autorelease();

	return instance;
}

ArriveInAthens::ArriveInAthens(GameObject* owner, QuestLine* questLine) : super(owner, questLine, ArriveInAthens::MapKeyQuest, false)
{
	this->guano = nullptr;
	this->scrappy = nullptr;
	this->squally = nullptr;
}

ArriveInAthens::~ArriveInAthens()
{
}

void ArriveInAthens::onLoad(QuestState questState)
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

	if (questState == QuestState::Active || questState == QuestState::ActiveThroughSkippable)
	{
		this->listenForMapEventOnce(ArriveInAthens::MapKeyQuest, [=](ValueMap)
		{
			this->runCinematicSequencePt1();
		});
	}
}

void ArriveInAthens::onActivate(bool isActiveThroughSkippable)
{
}

void ArriveInAthens::onComplete()
{
	Objectives::SetCurrentObjective(ObjectiveKeys::URHeadToTown);
}

void ArriveInAthens::onSkipped()
{
	this->removeAllListeners();
}

void ArriveInAthens::runCinematicSequencePt1()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_UnderflowRuins_CureTown_Ajax_A_HeyCoolStatue::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Left,
			DialogueEvents::BuildPreviewNode(&this->guano, false),
			[=]()
			{
				Sprite* ajax = Sprite::create(EntityResources::Npcs_UnderflowRuins_Ajax_Petrified);

				ajax->setFlippedX(true);
				ajax->setPosition(Vec2(-32.0f, 0.0f));

				return ajax;
			}
		),
		[=]()
		{
			this->runCinematicSequencePt2();
		},
		Voices::GetNextVoiceMedium(),
		false
	));
}

void ArriveInAthens::runCinematicSequencePt2()
{
	ObjectEvents::QueryObjects<CameraTarget>(QueryObjectsArgs<CameraTarget>([&](CameraTarget* cameraTarget)
	{
		GameCamera::getInstance()->pushTarget(cameraTarget->getTrackingData());
	}), ArriveInAthens::TagTownCinematic);

	this->runAction(Sequence::create(
		DelayTime::create(1.0f),
		CallFunc::create([=]()
		{
			this->runCinematicSequencePt3();
		}),
		nullptr
	));
}

void ArriveInAthens::runCinematicSequencePt3()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_UnderflowRuins_CureTown_Ajax_B_MoreStatues::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Left,
			DialogueEvents::BuildPreviewNode(&this->guano, false),
			[=]()
			{
				Sprite* ajax = Sprite::create(EntityResources::Npcs_UnderflowRuins_Athena_Petrified);

				ajax->setFlippedX(true);
				ajax->setPosition(Vec2(-32.0f, 0.0f));

				return ajax;
			}
		),
		[=]()
		{
			GameCamera::getInstance()->popTargetIfMultiple();
			this->runCinematicSequencePt4();
		},
		Voices::GetNextVoiceMedium(),
		false
	));
}

void ArriveInAthens::runCinematicSequencePt4()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_UnderflowRuins_CureTown_Ajax_C_DarkMagic::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Left,
			DialogueEvents::BuildPreviewNode(&this->scrappy, false),
			DialogueEvents::BuildPreviewNode(&this->guano, true)
		),
		[=]()
		{
			this->runCinematicSequencePt5();
		},
		Voices::GetNextVoiceMedium(Voices::VoiceType::Droid),
		false
	));
}

void ArriveInAthens::runCinematicSequencePt5()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Ellipses::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Right,
			DialogueEvents::BuildPreviewNode(&this->scrappy, false),
			DialogueEvents::BuildPreviewNode(&this->squally, true),
			true
		),
		[=]()
		{
			this->runCinematicSequencePt6();
		},
		"",
		false
	));
}

void ArriveInAthens::runCinematicSequencePt6()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_UnderflowRuins_CureTown_Ajax_D_SearchForClues::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Left,
			DialogueEvents::BuildPreviewNode(&this->scrappy, false),
			DialogueEvents::BuildPreviewNode(&this->squally, true)
		),
		[=]()
		{
			this->complete();
		},
		Voices::GetNextVoiceMedium(Voices::VoiceType::Droid),
		true
	));
}
