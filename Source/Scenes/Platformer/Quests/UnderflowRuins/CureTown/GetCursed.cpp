#include "GetCursed.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Camera/GameCamera.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Quests/QuestLine.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/Enemies/UnderflowRuins/Medusa.h"
#include "Entities/Platformer/Helpers/EndianForest/Guano.h"
#include "Entities/Platformer/Helpers/EndianForest/Scrappy.h"
#include "Entities/Platformer/Helpers/UnderflowRuins/GuanoPetrified.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/NotificationEvents.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Cinematic/CinematicMarker.h"
#include "Objects/Platformer/Interactables/Doors/Portal.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Visual/EntityQuestVisualBehavior.h"
#include "Scenes/Platformer/Hackables/HackFlags.h"
#include "Scenes/Platformer/Objectives/Objectives.h"
#include "Scenes/Platformer/Save/SaveKeys.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/EntityResources.h"
#include "Resources/ItemResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string GetCursed::MapKeyQuest = "get-cursed";
const std::string GetCursed::TagCinematicExit = "curse-exit";

GetCursed* GetCursed::create(GameObject* owner, QuestLine* questLine)
{
	GetCursed* instance = new GetCursed(owner, questLine);

	instance->autorelease();

	return instance;
}

GetCursed::GetCursed(GameObject* owner, QuestLine* questLine) : super(owner, questLine, GetCursed::MapKeyQuest, false)
{
	this->guano = nullptr;
	this->scrappy = nullptr;
	this->squally = nullptr;
	this->medusa = nullptr;
	this->curseSfx = WorldSound::create(SoundResources::Platformer_Spells_Curse1);

	this->addChild(this->curseSfx);
}

GetCursed::~GetCursed()
{
}

void GetCursed::onLoad(QuestState questState)
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

	ObjectEvents::WatchForObject<Medusa>(this, [=](Medusa* medusa)
	{
		this->medusa = medusa;

		if (questState == QuestState::Active || questState == QuestState::ActiveThroughSkippable)
		{
			this->listenForMapEventOnce(GetCursed::MapKeyQuest, [=](ValueMap)
			{
				this->runCinematicSequencePt1();
			});
		}
		else
		{
			this->medusa->despawn();
		}
	});
}

void GetCursed::onActivate(bool isActiveThroughSkippable)
{
}

void GetCursed::onComplete()
{
	Objectives::SetCurrentObjective(ObjectiveKeys::URHeadToTown);
}

void GetCursed::onSkipped()
{
	this->removeAllListeners();
}

void GetCursed::runCinematicSequencePt1()
{
	// IMPORTANT: Add a redundant save now to prevent possible bypasses.
	SaveManager::SaveProfileData(SaveKeys::SaveKeyHelperName, Value(GuanoPetrified::MapKey));

	// To prevent re-running dialogue on save/quit, mark the quest as complete before dialogue. This is one of the few cases where we do this.
	this->complete();

	PlatformerEvents::TriggerCinematicHijack();

	this->medusa->runAction(Sequence::create(
		CallFunc::create([=]()
		{
			PlatformerEvents::TriggerRunFlashFx(PlatformerEvents::FlashFxArgs(Color3B::PURPLE, 0.25f, 1));
			this->curseSfx->play();
			this->medusa->getAnimations()->playAnimation("AttackCast", SmartAnimationNode::AnimationPlayMode::ReturnToIdle, SmartAnimationNode::AnimParams(1.0f));
		}),
		DelayTime::create(0.15f),
		CallFunc::create([=]()
		{
			this->petrifyGuano();
		}),
		DelayTime::create(1.35f),
		CallFunc::create([=]()
		{
			this->runCinematicSequencePt2();
		}),
		nullptr
	));
}

void GetCursed::runCinematicSequencePt2()
{
	ObjectEvents::WatchForObject<CinematicMarker>(this, [=](CinematicMarker* cinematicMarker)
	{
		this->medusa->setState(StateKeys::CinematicDestinationX, Value(cinematicMarker->getPositionX()));

		this->medusa->listenForStateWriteOnce(StateKeys::CinematicDestinationReached, [=](Value value)
		{
			this->medusa->runAction(Sequence::create(
				FadeTo::create(0.5f, 0),
				CallFunc::create([=]()
				{
					this->medusa->despawn();
				}),
				nullptr
			));
		});
	}, GetCursed::TagCinematicExit);

	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_UnderflowRuins_CureTown_Scrappy_A_Cursed::create()
			->setStringReplacementVariables(Strings::Platformer_Entities_Names_Helpers_EndianForest_Guano::create()),
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
		Voices::GetNextVoiceShort(Voices::VoiceType::Droid),
		false
	));
}

void GetCursed::runCinematicSequencePt3()
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
			this->runCinematicSequencePt4();
		},
		"",
		false
	));
}

void GetCursed::runCinematicSequencePt4()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_UnderflowRuins_CureTown_Scrappy_B_Immune::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Left,
			DialogueEvents::BuildPreviewNode(&this->scrappy, false),
			DialogueEvents::BuildPreviewNode(&this->squally, true)
		),
		[=]()
		{
			this->runCinematicSequencePt5();
		},
		Voices::GetNextVoiceMedium(Voices::VoiceType::Droid),
		false
	));
}

void GetCursed::runCinematicSequencePt5()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_UnderflowRuins_CureTown_Scrappy_C_CarryOn::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Left,
			DialogueEvents::BuildPreviewNode(&this->scrappy, false),
			DialogueEvents::BuildPreviewNode(&this->squally, true)
		),
		[=]()
		{
		},
		Voices::GetNextVoiceShort(Voices::VoiceType::Droid),
		true
	));
}

void GetCursed::petrifyGuano()
{
	if (this->guano != nullptr)
	{
		Vec2 coords = GameUtils::getWorldCoords(this->guano, false);

		this->squally->setState(StateKeys::NewHelperSpawnX, Value(coords.x));
		this->squally->setState(StateKeys::NewHelperSpawnY, Value(coords.y));
	}

	this->squally->setState(StateKeys::NotifyNewHelper, Value(false));
	this->squally->setState(StateKeys::CurrentHelper, Value(GuanoPetrified::MapKey));
}
