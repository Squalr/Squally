#include "PerceptronFight.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Quests/QuestLine.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/Sound/Sound.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/Enemies/VoidStar/Perceptron.h"
#include "Entities/Platformer/Helpers/EndianForest/Guano.h"
#include "Entities/Platformer/Helpers/EndianForest/Scrappy.h"
#include "Entities/Platformer/Helpers/DataMines/Gecky.h"
#include "Entities/Platformer/Npcs/Mages/Mabel.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Camera/CameraStop.h"
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

const std::string PerceptronFight::MapKeyQuest = "perceptron-fight";

PerceptronFight* PerceptronFight::create(GameObject* owner, QuestLine* questLine)
{
	PerceptronFight* instance = new PerceptronFight(owner, questLine);

	instance->autorelease();

	return instance;
}

PerceptronFight::PerceptronFight(GameObject* owner, QuestLine* questLine) : super(owner, questLine, PerceptronFight::MapKeyQuest, false)
{
	this->lightningStrike = SmartAnimationSequenceNode::create();
	this->lightningSound = Sound::create(SoundResources::Hexus_Attacks_Energy);

	this->lightningStrike->setVisible(false);

	this->addChild(this->lightningStrike);
	this->addChild(this->lightningSound);
}

PerceptronFight::~PerceptronFight()
{
}

void PerceptronFight::onLoad(QuestState questState)
{
	ObjectEvents::WatchForObject<Perceptron>(this, [=](Perceptron* perceptron)
	{
		this->perceptron = perceptron;
		
		if (!this->perceptron->getRuntimeStateOrDefault(StateKeys::IsAlive, Value(true)).asBool())
		{
			this->complete();
		}

		this->perceptron->listenForStateWrite(StateKeys::IsAlive, [=](Value value)
		{
			if (!value.asBool())
			{
				this->complete();
			}
		});
	}, Perceptron::MapKey);

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
}

void PerceptronFight::onActivate(bool isActiveThroughSkippable, bool isInitialActivation)
{
	this->listenForMapEventOnce("gauntlet-start", [=](ValueMap valueMap)
	{
		this->runCinematicSequencePt1();
	});
}

void PerceptronFight::onComplete()
{
}

void PerceptronFight::onSkipped()
{
	this->removeAllListeners();
}

void PerceptronFight::runCinematicSequencePt1()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_VoidStar_PerceptronFight_A_You::create(), 
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Right,
			DialogueEvents::BuildPreviewNode(&this->squally, false),
			DialogueEvents::BuildPreviewNode(&this->perceptron, true)
		),
		[=]()
		{
			if (this->squally != nullptr)
			{
				this->lightningStrike->setVisible(true);
				this->lightningStrike->playAnimation(FXResources::Lightning_Lightning_0000, 0.06f);
				GameUtils::setWorldCoords(this->lightningStrike, GameUtils::getWorldCoords(this->squally) + Vec2(0.0f, 392.0f));
				this->lightningSound->play();

				/*
				this->squally->getComponent<EntityHealthBehavior>([=](EntityHealthBehavior* healthBehavior)
				{
					healthBehavior->kill();
				});

				// Kill with forced map reload to reset the event
				this->squally->getComponent<SquallyRespawnBehavior>([=](SquallyRespawnBehavior* respawnBehavior)
				{
					respawnBehavior->respawnWithMapReload();
				});*/

				this->runAction(Sequence::create(
					DelayTime::create(1.0f),
					CallFunc::create([=]()
					{
						this->runCinematicSequencePt2();
					}),
					nullptr
				));
			}
		},
		Voices::GetNextVoiceMedium(Voices::VoiceType::Ghost),
		true
	));
}

void PerceptronFight::runCinematicSequencePt2()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_VoidStar_PerceptronFight_B_No::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Right,
			DialogueEvents::BuildPreviewNode(&this->squally, false),
			DialogueEvents::BuildPreviewNode(&this->perceptron, true)
		),
		[=]()
		{
			this->runCinematicSequencePt3();
		},
		Voices::GetNextVoiceShort(Voices::VoiceType::Ghost),
		true
	));
}

void PerceptronFight::runCinematicSequencePt3()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_VoidStar_PerceptronFight_C_Risk::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Right,
			DialogueEvents::BuildPreviewNode(&this->squally, false),
			DialogueEvents::BuildPreviewNode(&this->perceptron, true)
		),
		[=]()
		{
			this->runCinematicSequencePt4();
		},
		Voices::GetNextVoiceMedium(Voices::VoiceType::Ghost),
		true
	));
}

void PerceptronFight::runCinematicSequencePt4()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Ellipses::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Left,
			DialogueEvents::BuildPreviewNode(&this->squally, false),
			DialogueEvents::BuildPreviewNode(&this->perceptron, true)
		),
		[=]()
		{
			this->runCinematicSequencePt5();
		},
		"",
		true
	));
}

void PerceptronFight::runCinematicSequencePt5()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_VoidStar_PerceptronFight_D_Reality::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Right,
			DialogueEvents::BuildPreviewNode(&this->squally, false),
			DialogueEvents::BuildPreviewNode(&this->perceptron, true)
		),
		[=]()
		{
			PlatformerEvents::TriggerEngageEnemy(PlatformerEvents::EngageEnemyArgs(this->perceptron, false));
		},
		Voices::GetNextVoiceLong(Voices::VoiceType::Ghost),
		true
	));
}
