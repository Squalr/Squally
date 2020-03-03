#include "FightGorgon.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Dialogue/DialogueOption.h"
#include "Engine/Dialogue/DialogueSet.h"
#include "Engine/Dialogue/SpeechBubble.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Events/QuestEvents.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/Enemies/EndianForest/Gorgon.h"
#include "Entities/Platformer/Npcs/SeaSharpCaverns/Sarude.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/NotificationEvents.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Interactables/Ram/Ram.h"
#include "Objects/Platformer/Cinematic/CinematicMarker.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Friendly/LookAtSquallyBehavior.h"
#include "Scenes/Platformer/Hackables/HackFlags.h"
#include "Scenes/Platformer/Save/SaveKeys.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/ObjectResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string FightGorgon::MapKeyQuest = "fight-gorgon";

FightGorgon* FightGorgon::create(GameObject* owner, QuestLine* questLine)
{
	FightGorgon* instance = new FightGorgon(owner, questLine);

	instance->autorelease();

	return instance;
}

FightGorgon::FightGorgon(GameObject* owner, QuestLine* questLine) : super(owner, questLine, FightGorgon::MapKeyQuest, false)
{
	this->gorgon = nullptr;
	this->sarude = nullptr;
	this->ram = nullptr;
}

FightGorgon::~FightGorgon()
{
}

void FightGorgon::onLoad(QuestState questState)
{
	ObjectEvents::watchForObject<Sarude>(this, [=](Sarude* sarude)
	{
		this->sarude = sarude;
	}, Sarude::MapKeySarude);

	ObjectEvents::watchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKeySqually);

	ObjectEvents::watchForObject<Gorgon>(this, [=](Gorgon* gorgon)
	{
		this->gorgon = gorgon;

		if (questState == QuestState::Active)
		{
			this->killRammedEnemies();
			
			this->defer([=]()
			{
				this->gorgon->attachBehavior(LookAtSquallyBehavior::create(this->gorgon));
			});
		}
		else if (questState == QuestState::ActiveThroughSkippable)
		{
			this->runGorgonLoop();
		}
	}, Gorgon::MapKeyGorgon);

	ObjectEvents::watchForObject<Ram>(this, [=](Ram* ram)
	{
		this->ram = ram;
		this->ram->setVisible(questState == QuestState::Active);
		this->ram->getAnimations()->playAnimation("Broken", SmartAnimationNode::AnimationPlayMode::Repeat);
	}, Ram::MapKeyRam);

	if (questState == QuestState::Active)
	{
		this->listenForMapEventOnce(FightGorgon::MapKeyQuest, [=](ValueMap args)
		{
			this->runCinematicSequencePart1();
		});
	}
}

void FightGorgon::onActivate(bool isActiveThroughSkippable)
{
}

void FightGorgon::onComplete()
{
}

void FightGorgon::onSkipped()
{
}

void FightGorgon::runCinematicSequencePart1()
{
	ObjectEvents::watchForObject<CinematicMarker>(this, [=](CinematicMarker* marker)
	{
		this->squally->setState(StateKeys::CinematicDestinationX, Value(GameUtils::getWorldCoords(marker).x));
	}, "walk-to");

	this->squally->listenForStateWriteOnce(StateKeys::CinematicDestinationReached, [=](Value value)
	{
		this->runCinematicSequencePart2();
	});
}

void FightGorgon::runCinematicSequencePart2()
{
	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		Strings::Platformer_Quests_EndianForest_SaveTown_Gorgon_A_MeSmash::create(),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Left,
			DialogueEvents::BuildPreviewNode(&this->gorgon, false),
			DialogueEvents::BuildPreviewNode(&this->squally, true)
		),
		[=]()
		{
			this->runCinematicSequencePart3();
		},
		SoundResources::Platformer_Entities_Orc_GruntDeep1,
		true
	));
}

void FightGorgon::runCinematicSequencePart3()
{
	PlatformerEvents::TriggerEngageEnemy(PlatformerEvents::EngageEnemyArgs(this->gorgon, true));
}

void FightGorgon::killRammedEnemies()
{
	ObjectEvents::QueryObjects(QueryObjectsArgs<PlatformerEnemy>([=](PlatformerEnemy* enemy)
	{
		if (enemy != this->gorgon)
		{
			enemy->setState(StateKeys::IsAlive, Value(false));
		}
	}), PlatformerEnemy::PlatformerEnemyTag);
}

void FightGorgon::runGorgonLoop()
{
	if (this->gorgon == nullptr)
	{
		return;
	}

	this->gorgon->getAnimations()->clearAnimationPriority();

	this->gorgon->getAnimations()->playAnimation("AttackRebound", SmartAnimationNode::AnimationPlayMode::Callback, 1.0f, 0.25f, [=]()
	{
		this->gorgon->getAnimations()->clearAnimationPriority();

		this->gorgon->getAnimations()->playAnimation("AttackStrongRebound", SmartAnimationNode::AnimationPlayMode::Callback, 1.0f, 0.25f, [=]()
		{
			this->gorgon->getAnimations()->clearAnimationPriority();

			this->gorgon->getAnimations()->playAnimation("AttackChargeRebound", SmartAnimationNode::AnimationPlayMode::Callback, 1.0f, 0.25f, [=]()
			{
				this->runGorgonLoop();
			});
		});
	});
}
