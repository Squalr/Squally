#include "MeetScrappy.h"

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
#include "Engine/Events/SceneEvents.h"
#include "Engine/Sound/Sound.h"
#include "Entities/Platformer/Helpers/EndianForest/Scrappy.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/HelperEvents.h"
#include "Events/NotificationEvents.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Cinematic/CinematicMarker.h"

#include "Resources/EntityResources.h"

#include "Strings/Platformer/Quests/EndianForest/Intro/GetYouPatched.h"
#include "Strings/Platformer/Quests/EndianForest/Intro/DistressBeacon.h"
#include "Strings/Platformer/Quests/EndianForest/Intro/YoureAlive.h"
#include "Strings/Platformer/Notifications/Party/ScrappyJoinedParty.h"

using namespace cocos2d;

const std::string MeetScrappy::MapKeyQuest = "meet-scrappy";

MeetScrappy* MeetScrappy::create(GameObject* owner, QuestLine* questLine, std::string questTag)
{
	MeetScrappy* instance = new MeetScrappy(owner, questLine, questTag);

	instance->autorelease();

	return instance;
}

MeetScrappy::MeetScrappy(GameObject* owner, QuestLine* questLine, std::string questTag) : super(owner, questLine, MeetScrappy::MapKeyQuest, questTag, true)
{
	this->hasRunEvent = false;
	this->scrappy = dynamic_cast<Scrappy*>(owner);
}

MeetScrappy::~MeetScrappy()
{
}

void MeetScrappy::onLoad(QuestState questState)
{
	if (this->scrappy != nullptr)
	{
		this->scrappy->getAnimations()->setFlippedX(true);

		if (questState == QuestState::Complete)
		{
			this->scrappy->setVisible(false);
		}
	}
}

void MeetScrappy::onActivate(bool isActiveThroughSkippable)
{
	this->listenForMapEvent(MeetScrappy::MapKeyQuest, [=](ValueMap args)
	{
		this->runCinematicSequence();
	});

	this->addEventListenerIgnorePause(EventListenerCustom::create(SceneEvents::EventBeforeSceneChange, [=](EventCustom* eventCustom)
	{
		this->complete();
	}));
}

void MeetScrappy::onComplete()
{
}

void MeetScrappy::onSkipped()
{
	this->removeAllListeners();
}

void MeetScrappy::runCinematicSequence()
{
	if (this->hasRunEvent)
	{
		return;
	}
	
	this->hasRunEvent = true;
	Vec2 positionA = Vec2::ZERO;

	ObjectEvents::QueryObjects(QueryObjectsArgs<CinematicMarker>([&](CinematicMarker* cinematicMarker)
	{
		switch(cinematicMarker->getId())
		{
			case 0:
			{
				positionA = cinematicMarker->getPosition();
				break;
			}
			default:
			{
				break;
			}
		}
	}));

	if (this->scrappy != nullptr)
	{
		PlatformerEvents::TriggerCinematicHijack();

		this->scrappy->runAction(Sequence::create(
			CallFunc::create([=]()
			{
				this->scrappy->droidAlarmedSound->play();
			}),
			EaseSineInOut::create(MoveTo::create(2.0f, positionA)),
			CallFunc::create([=]()
			{
				this->scrappy->speechBubble->runDialogue(Strings::Platformer_Quests_EndianForest_Intro_YoureAlive::create());
			}),
			DelayTime::create(2.0f),
			CallFunc::create([=]()
			{
				this->scrappy->droidBrief1Sound->play();
				this->scrappy->speechBubble->runDialogue(Strings::Platformer_Quests_EndianForest_Intro_DistressBeacon::create());
			}),
			DelayTime::create(4.0f),
			CallFunc::create([=]()
			{
				this->scrappy->droidBrief1Sound->play();
				this->scrappy->speechBubble->runDialogue(Strings::Platformer_Quests_EndianForest_Intro_GetYouPatched::create());
			}),
			DelayTime::create(4.0f),
			CallFunc::create([=]()
			{
				this->scrappy->speechBubble->hideDialogue();
			}),
			DelayTime::create(1.0f),
			CallFunc::create([=]()
			{
				Vec2 positionB = Vec2::ZERO;

				ObjectEvents::QueryObjects(QueryObjectsArgs<Squally>([&](Squally* squally)
				{
					positionB = squally->getPosition();
				}));

				this->scrappy->runAction(EaseSineInOut::create(MoveTo::create(1.0f, positionB)));
			}),
			DelayTime::create(1.0f),
			CallFunc::create([=]()
			{
				this->scrappy->setVisible(false);

				NotificationEvents::TriggerNotification(NotificationEvents::NotificationArgs(nullptr, Strings::Platformer_Notifications_Party_ScrappyJoinedParty::create(), EntityResources::Helpers_EndianForest_Scrappy_Emblem));
				HelperEvents::TriggerFindScrappy();
				PlatformerEvents::TriggerCinematicRestore();

				this->complete();
			}),
			nullptr
		));
	}
}
