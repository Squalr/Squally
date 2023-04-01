#include "ElricsPlea.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Camera/GameCamera.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Quests/QuestLine.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/Sound/Sound.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/Enemies/VoidStar/EvilEye.h"
#include "Entities/Platformer/Enemies/LambdaCrypts/Zombie.h"
#include "Entities/Platformer/Enemies/LambdaCrypts/ZombieElric.h"
#include "Entities/Platformer/Npcs/LambdaCrypts/Elric.h"
#include "Entities/Platformer/Helpers/EndianForest/Guano.h"
#include "Entities/Platformer/Helpers/EndianForest/Scrappy.h"
#include "Entities/Platformer/Helpers/DataMines/Gecky.h"
#include "Entities/Platformer/Npcs/Mages/Mabel.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Camera/CameraStop.h"
#include "Objects/Platformer/Camera/CameraTarget.h"
#include "Objects/Platformer/Cinematic/CinematicMarker.h"
#include "Objects/Platformer/Interactables/Doors/Portal.h"
#include "Objects/Platformer/Switches/Trigger.h"
#include "Scenes/Platformer/Components/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/Components/Entities/Movement/EntityMovementBehavior.h"
#include "Scenes/Platformer/Components/Entities/Stats/EntityHealthBehavior.h"
#include "Scenes/Platformer/Components/Entities/Squally/Movement/SquallyRespawnBehavior.h"
#include "Scenes/Platformer/Components/Entities/Visual/EntityQuestVisualBehavior.h"
#include "Scenes/Platformer/Components/Objects/Illusions/DispelIllusionBehavior.h"
#include "Scenes/Platformer/Dialogue/Voices.h"
#include "Scenes/Platformer/Level/Physics/PlatformerPhysicsTypes.h"
#include "Scenes/Platformer/Objectives/ObjectiveKeys.h"
#include "Scenes/Platformer/Objectives/Objectives.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/FXResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string ElricsPlea::MapKeyQuest = "elrics-plea";

ElricsPlea* ElricsPlea::create(GameObject* owner, QuestLine* questLine)
{
	ElricsPlea* instance = new ElricsPlea(owner, questLine);

	instance->autorelease();

	return instance;
}

ElricsPlea::ElricsPlea(GameObject* owner, QuestLine* questLine) : super(owner, questLine, ElricsPlea::MapKeyQuest, false)
{
}

ElricsPlea::~ElricsPlea()
{
}

void ElricsPlea::onLoad(QuestState questState)
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

	ObjectEvents::WatchForObject<Elric>(this, [=](Elric* elric)
	{
		this->elric = elric;

		if (questState == QuestState::Complete)
		{
			this->elric->despawn();
		}
	}, Elric::MapKey);

	ObjectEvents::WatchForObject<Zombie>(this, [=](Zombie* zombie)
	{
		this->zombie = zombie;
		
		zombie->watchForComponent<EntityHealthBehavior>([=](EntityHealthBehavior* healthBehavior)
		{
			healthBehavior->kill(false);
		});
	}, "cinematic-zombie");
	

	ObjectEvents::WatchForObject<ZombieElric>(this, [=](ZombieElric* zombieElric)
	{
		this->zombieElric = zombieElric;

		if (questState != QuestState::Active || questState != QuestState::ActiveThroughSkippable)
		{
			this->zombieElric->despawn();
		}
	}, ZombieElric::MapKey);
}

void ElricsPlea::onActivate(bool isActiveThroughSkippable)
{
	this->listenForMapEventOnce(ElricsPlea::MapKeyQuest, [=](ValueMap)
	{
		this->runCinematicSequencePt1();
	});
}

void ElricsPlea::onComplete()
{
}

void ElricsPlea::onSkipped()
{
	this->removeAllListeners();
}

void ElricsPlea::runCinematicSequencePt1()
{
	ObjectEvents::QueryObjects<CameraTarget>([&](CameraTarget* cameraTarget)
	{
		GameCamera::getInstance()->pushTarget(cameraTarget->getTrackingData());
	}, "graveyard-cinematic");

	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_LambdaCrypts_ElricsDemise_A_Travelers::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Right,
			DialogueEvents::BuildPreviewNode(&this->squally, false),
			DialogueEvents::BuildPreviewNode(&this->elric, true)
		),
		[=]()
		{
			this->runCinematicSequencePt2();
		},
		Voices::GetNextVoiceShort(Voices::VoiceType::Human),
		false
	));
}

void ElricsPlea::runCinematicSequencePt2()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_LambdaCrypts_ElricsDemise_B_NeedAssistance::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Right,
			DialogueEvents::BuildPreviewNode(&this->squally, false),
			DialogueEvents::BuildPreviewNode(&this->elric, true)
		),
		[=]()
		{
			this->runCinematicSequencePt3();
		},
		Voices::GetNextVoiceMedium(Voices::VoiceType::Human),
		false
	));
}

void ElricsPlea::runCinematicSequencePt3()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_LambdaCrypts_ElricsDemise_C_Bitten::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Right,
			DialogueEvents::BuildPreviewNode(&this->squally, false),
			DialogueEvents::BuildPreviewNode(&this->elric, true)
		),
		[=]()
		{
			this->runCinematicSequencePt4();
		},
		Voices::GetNextVoiceLong(Voices::VoiceType::Human),
		false
	));
}

void ElricsPlea::runCinematicSequencePt4()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_LambdaCrypts_ElricsDemise_D_SeekHelp::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Right,
			DialogueEvents::BuildPreviewNode(&this->squally, false),
			DialogueEvents::BuildPreviewNode(&this->elric, true)
		),
		[=]()
		{
			this->runCinematicSequencePt5();
		},
		Voices::GetNextVoiceLong(Voices::VoiceType::Human),
		false
	));
}

void ElricsPlea::runCinematicSequencePt5()
{
	if (this->guano != nullptr)
	{
		DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_LambdaCrypts_ElricsDemise_E_Guano_PickHisPockets::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Left,
				DialogueEvents::BuildPreviewNode(&this->guano, false),
				DialogueEvents::BuildPreviewNode(&this->elric, true)
			),
			[=]()
			{
				this->runCinematicSequencePt6();
			},
			Voices::GetNextVoiceMedium(),
			true
		));
	}
	else if (this->gecky != nullptr)
	{
		DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
			Strings::Platformer_Quests_LambdaCrypts_ElricsDemise_E_Gecky_Ok::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Left,
				DialogueEvents::BuildPreviewNode(&this->gecky, false),
				DialogueEvents::BuildPreviewNode(&this->elric, true)
			),
			[=]()
			{
				this->runCinematicSequencePt6();
			},
			Voices::GetNextVoiceMedium(),
			true
		));
	}
	else
	{
		PlatformerEvents::TriggerCinematicRestore();
		this->runCinematicSequencePt6();
	}
}

void ElricsPlea::runCinematicSequencePt6()
{
	GameCamera::getInstance()->popTargetIfMultiple();

	this->complete();
}
