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
const std::string GetCursed::SaveKeyDespawned = "SAVE_KEY_DESPAWNED";

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

		if (this->loadObjectStateOrDefault(GetCursed::SaveKeyDespawned, Value(false)).asBool())
		{
			this->medusa->despawn();
		}
		else if (questState == QuestState::Active || questState == QuestState::ActiveThroughSkippable)
		{
			this->listenForMapEventOnce(GetCursed::MapKeyQuest, [=](ValueMap)
			{
				this->saveObjectState(GetCursed::SaveKeyDespawned, Value(true));
				this->runCinematicSequencePt1();
			});
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

	PlatformerEvents::TriggerCinematicHijack();

	this->medusa->runAction(Sequence::create(
		CallFunc::create([=]()
		{
			this->medusa->getAnimations()->playAnimation("AttackCast", SmartAnimationNode::AnimationPlayMode::ReturnToIdle, SmartAnimationNode::AnimParams(1.0f));
		}),
		DelayTime::create(0.75f),
		CallFunc::create([=]()
		{
			this->petrifyGuano();
		}),
		DelayTime::create(0.75f),
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

	PlatformerEvents::TriggerCinematicRestore();
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
