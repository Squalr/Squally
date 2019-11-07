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
#include "Engine/Utils/GameUtils.h"
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
#include "Strings/Platformer/Notifications/Party/HelperJoinedParty.h"

using namespace cocos2d;

const std::string MeetScrappy::MapKeyQuest = "meet-scrappy";
const std::string MeetScrappy::TagScrappyStop = "scrappy-stop";

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
		this->runCinematicSequencePt1();
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

void MeetScrappy::runCinematicSequencePt1()
{
	if (this->hasRunEvent)
	{
		return;
	}
	
	this->hasRunEvent = true;
	Vec2 positionA = Vec2::ZERO;

	ObjectEvents::QueryObjects(QueryObjectsArgs<CinematicMarker>([&](CinematicMarker* cinematicMarker)
	{
		positionA = cinematicMarker->getPosition();
	}), MeetScrappy::TagScrappyStop);

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
				this->scrappy->speechBubble->runDialogue(Strings::Platformer_Quests_EndianForest_Intro_YoureAlive::create(), 2.0f, [=]()
				{
					this->scrappy->droidBrief1Sound->play();
					this->scrappy->speechBubble->runDialogue(Strings::Platformer_Quests_EndianForest_Intro_DistressBeacon::create(), 4.0f, [=]()
					{
						this->scrappy->droidBrief1Sound->play();
						this->scrappy->speechBubble->runDialogue(Strings::Platformer_Quests_EndianForest_Intro_GetYouPatched::create(), 4.0f, [=]()
						{
							this->runCinematicSequencePt2();
						});
					});
				});
			}),
			nullptr
		));
	}
}

void MeetScrappy::runCinematicSequencePt2()
{
	if (this->scrappy != nullptr)
	{
		this->scrappy->runAction(Sequence::create(
			DelayTime::create(1.0f),
			CallFunc::create([=]()
			{
				Vec2 positionB = Vec2::ZERO;

				ObjectEvents::QueryObjects(QueryObjectsArgs<Squally>([&](Squally* squally)
				{
					positionB = GameUtils::getWorldCoords(squally);
				}));

				this->scrappy->runAction(EaseSineInOut::create(MoveTo::create(1.0f, positionB)));
			}),
			DelayTime::create(1.0f),
			CallFunc::create([=]()
			{
				this->scrappy->setVisible(false);

				NotificationEvents::TriggerNotification(NotificationEvents::NotificationArgs(
					nullptr,
					Strings::Platformer_Notifications_Party_HelperJoinedParty::create()->setStringReplacementVariables(this->scrappy->getEntityName()),
					this->scrappy->getEmblemResource()
				));
				HelperEvents::TriggerFindScrappy();
				PlatformerEvents::TriggerCinematicRestore();

				this->complete();
			}),
			nullptr
		));
	}
}
