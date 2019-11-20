#include "TrollInTheDungeon.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Dialogue/SpeechBubble.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Events/QuestEvents.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/DialogueEvents.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Cinematic/CinematicMarker.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/SoundResources.h"

#include "Strings/Platformer/Ellipses.h"
#include "Strings/Platformer/Quests/EndianForest/RescueGuano/TrollInTheDungeon.h"

using namespace cocos2d;

const std::string TrollInTheDungeon::MapKeyQuest = "troll-in-the-dungeon";
const std::string TrollInTheDungeon::TagDialoguePause = "dialogue-pause";
const std::string TrollInTheDungeon::TagExit = "exit";

TrollInTheDungeon* TrollInTheDungeon::create(GameObject* owner, QuestLine* questLine,  std::string questTag)
{
	TrollInTheDungeon* instance = new TrollInTheDungeon(owner, questLine, questTag);

	instance->autorelease();

	return instance;
}

TrollInTheDungeon::TrollInTheDungeon(GameObject* owner, QuestLine* questLine, std::string questTag) : super(owner, questLine, TrollInTheDungeon::MapKeyQuest, questTag, false)
{
	this->mage = dynamic_cast<PlatformerEntity*>(owner);
	this->squally = nullptr;
}

TrollInTheDungeon::~TrollInTheDungeon()
{
}

void TrollInTheDungeon::onLoad(QuestState questState)
{
	ObjectEvents::watchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKeySqually);
	
	if (questState == QuestState::Complete)
	{
		this->defer([=]()
		{
			this->mage->despawn();
		});
	}
}

void TrollInTheDungeon::onActivate(bool isActiveThroughSkippable)
{
	this->runAction(Sequence::create(
		DelayTime::create(0.5f),
		CallFunc::create([=]()
		{
			this->runChatSequence();
		}),
		nullptr
	));
}

void TrollInTheDungeon::onComplete()
{
}

void TrollInTheDungeon::onSkipped()
{
	this->removeAllListeners();
}

void TrollInTheDungeon::runChatSequence()
{
	ObjectEvents::watchForObject<CinematicMarker>(this, [=](CinematicMarker* cinematicMarker)
	{
		this->mage->setState(StateKeys::CinematicDestinationX, Value(cinematicMarker->getPositionX()));
		PlatformerEvents::TriggerCinematicHijack();

		this->mage->listenForStateWriteOnce(StateKeys::CinematicDestinationReached, [=](Value value)
		{
			this->mage->getAttachedBehavior<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
			{
				interactionBehavior->getSpeechBubble()->runDialogue(Strings::Platformer_Quests_EndianForest_RescueGuano_TrollInTheDungeon::create(), SoundResources::Platformer_Entities_Generic_ChatterAnnoyed1);
			});

			this->complete();

			this->mage->runAction(Sequence::create(
				DelayTime::create(1.0f),
				CallFunc::create([=]()
				{
					PlatformerEvents::TriggerCinematicRestore();
				}),
				DelayTime::create(1.0f),
				CallFunc::create([=]()
				{
					this->runChatSequencePt2();
				}),
				nullptr
			));
		});
	}, TrollInTheDungeon::TagDialoguePause);
}

void TrollInTheDungeon::runChatSequencePt2()
{
	ObjectEvents::watchForObject<CinematicMarker>(this, [=](CinematicMarker* cinematicMarker)
	{
		this->mage->setState(StateKeys::CinematicDestinationX, Value(cinematicMarker->getPositionX()));
		
		this->mage->getAttachedBehavior<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
		{
			interactionBehavior->getSpeechBubble()->hideDialogue();
		});

		this->mage->listenForStateWriteOnce(StateKeys::CinematicDestinationReached, [=](Value value)
		{
			this->mage->runAction(Sequence::create(
				FadeTo::create(0.5f, 0),
				CallFunc::create([=]()
				{
					this->mage->despawn();
				}),
				nullptr
			));
		});

	}, TrollInTheDungeon::TagExit);
}
