#include "Task1.h"

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
#include "Engine/Sound/Sound.h"
#include "Events/PlatformerEvents.h"
#include "Entities/Platformer/Misc/DaemonsHallow/FlyBot.h"
#include "Objects/Platformer/Cinematic/CinematicMarker.h"

#include "Strings/Dialogue/Story/Intro/GetYouPatched.h"
#include "Strings/Dialogue/Story/Intro/YoureAlive.h"

using namespace cocos2d;

const std::string Task1::MapKeyQuest = "task1";

Task1* Task1::create(GameObject* owner, std::string questLine, std::string questTag)
{
	Task1* instance = new Task1(owner, questLine, questTag);

	instance->autorelease();

	return instance;
}

Task1::Task1(GameObject* owner, std::string questLine, std::string questTag) : super(owner, questLine, Task1::MapKeyQuest, questTag, true)
{
	this->hasRunEvent = false;
	this->flyBot = static_cast<FlyBot*>(owner);
}

Task1::~Task1()
{
}

void Task1::onStateChange(QuestTask::QuestState questState, QuestTask::QuestState questStatePrevious)
{
}

void Task1::onActivateRunOnce()
{
	this->listenForMapEvent(Task1::MapKeyQuest, [=](ValueMap args)
	{
		QuestEvents::TriggerAdvanceToNextQuestTask(QuestEvents::AdvanceNextQuestArgs(this));

		this->runCinematicSequence();
	});
}

void Task1::enable(bool isSkippable)
{
	if (this->flyBot != nullptr)
	{
		this->flyBot->animationNode->setFlippedX(true);
	}
}

void Task1::disable()
{
	this->removeAllListeners();
	
	if (this->flyBot != nullptr)
	{
		this->flyBot->setVisible(false);
	}
}

void Task1::runCinematicSequence()
{
	if (this->hasRunEvent)
	{
		return;
	}
	
	this->hasRunEvent = true;
	Vec2 positionA = Vec2::ZERO;
	Vec2 positionB = Vec2::ZERO;

	ObjectEvents::QueryObjects(QueryObjectsArgs<CinematicMarker>([&](CinematicMarker* cinematicMarker)
	{
		switch(cinematicMarker->getId())
		{
			case 0:
			{
				positionA = cinematicMarker->getPosition();
				break;
			}
			case 1:
			{
				positionB = cinematicMarker->getPosition();
				break;
			}
			default:
			{
				break;
			}
		}
	}));

	if (this->flyBot != nullptr)
	{
		this->flyBot->runAction(Sequence::create(
			CallFunc::create([=]()
			{
				this->flyBot->droidAlarmedSound->play();
			}),
			EaseSineInOut::create(MoveTo::create(2.0f, positionA)),
			CallFunc::create([=]()
			{
				this->flyBot->speechBubble->runDialogue(Strings::Dialogue_Story_Intro_YoureAlive::create());
			}),
			DelayTime::create(2.0f),
			CallFunc::create([=]()
			{
				this->flyBot->droidBrief1Sound->play();
				this->flyBot->speechBubble->runDialogue(Strings::Dialogue_Story_Intro_GetYouPatched::create());
			}),
			DelayTime::create(4.0f),
			CallFunc::create([=]()
			{
				this->flyBot->speechBubble->hideDialogue();
			}),
			DelayTime::create(1.0f),
			CallFunc::create([=]()
			{
			}),
			EaseSineInOut::create(MoveTo::create(2.0f, positionB)),
			CallFunc::create([=]()
			{
				this->flyBot->setVisible(false);
			}),
			nullptr
		));
	}
}
