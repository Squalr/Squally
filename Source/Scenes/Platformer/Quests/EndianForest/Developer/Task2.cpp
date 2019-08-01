#include "Task2.h"

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

#include "Strings/Dialogue/Story/Intro/TentHeal.h"

using namespace cocos2d;

const std::string Task2::MapKeyQuest = "task2";

Task2* Task2::create(GameObject* owner, std::string questLine, std::string questTag)
{
	Task2* instance = new Task2(owner, questLine, questTag);

	instance->autorelease();

	return instance;
}

Task2::Task2(GameObject* owner, std::string questLine, std::string questTag) : super(owner, questLine, Task2::MapKeyQuest, questTag, false)
{
	this->hasRunEvent = false;
	this->flyBot = static_cast<FlyBot*>(owner);
}

Task2::~Task2()
{
}

void Task2::onStateChange(QuestTask::QuestState questState, QuestTask::QuestState questStatePrevious)
{
}

void Task2::onActivateRunOnce()
{
	this->listenForMapEvent(Task2::MapKeyQuest, [=](ValueMap args)
	{
		QuestEvents::TriggerAdvanceToNextQuestTask(QuestEvents::AdvanceNextQuestArgs(this));

		this->runCinematicSequence();
	});
}

void Task2::enable(bool isSkippable)
{
	if (this->flyBot != nullptr)
	{
		this->flyBot->animationNode->setFlippedX(true);
	}
}

void Task2::disable()
{
	this->removeAllListeners();

	if (this->flyBot != nullptr)
	{
		this->flyBot->setVisible(false);
	}
}

void Task2::runCinematicSequence()
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

	if (this->flyBot != nullptr)
	{
		this->flyBot->runAction(Sequence::create(
			CallFunc::create([=]()
			{
				this->flyBot->droidBrief2Sound->play();
			}),
			CallFunc::create([=]()
			{
				this->flyBot->speechBubble->runDialogue(Strings::Dialogue_Story_Intro_TentHeal::create());
			}),
			DelayTime::create(4.0f),
			CallFunc::create([=]()
			{
				this->flyBot->speechBubble->hideDialogue();
			}),
			DelayTime::create(1.0f),
			EaseSineInOut::create(MoveTo::create(2.0f, positionA)),
			CallFunc::create([=]()
			{
				this->flyBot->setVisible(false);
			}),
			nullptr
		));
	}
}
