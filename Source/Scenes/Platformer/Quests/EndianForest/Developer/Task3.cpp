#include "Task3.h"

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

#include "Strings/Dialogue/Story/Intro/HackerMode.h"

using namespace cocos2d;

const std::string Task3::MapKeyQuest = "task3";

Task3* Task3::create(GameObject* owner, std::string questLine, std::string questTag)
{
	Task3* instance = new Task3(owner, questLine, questTag);

	instance->autorelease();

	return instance;
}

Task3::Task3(GameObject* owner, std::string questLine, std::string questTag) : super(owner, questLine, Task3::MapKeyQuest, questTag, false)
{
	this->hasRunEvent = false;
	this->flyBot = static_cast<FlyBot*>(owner);
}

Task3::~Task3()
{
}

void Task3::onStateChange(QuestTask::QuestState questState, QuestTask::QuestState questStatePrevious)
{
}

void Task3::onActivateRunOnce()
{
	this->listenForMapEvent(Task3::MapKeyQuest, [=](ValueMap args)
	{
		QuestEvents::TriggerAdvanceToNextQuestTask(QuestEvents::AdvanceNextQuestArgs(this));

		this->runCinematicSequence();
	});
}

void Task3::enable(bool isSkippable)
{
	if (this->flyBot != nullptr)
	{
		this->flyBot->animationNode->setFlippedX(true);
	}
}

void Task3::disable()
{
	this->removeAllListeners();
	
	if (this->flyBot != nullptr)
	{
		this->flyBot->setVisible(false);
	}
}

void Task3::runCinematicSequence()
{
	if (this->hasRunEvent)
	{
		return;
	}
	
	this->hasRunEvent = true;
	Vec2 positionB = Vec2::ZERO;

	ObjectEvents::QueryObjects(QueryObjectsArgs<CinematicMarker>([&](CinematicMarker* cinematicMarker)
	{
		switch(cinematicMarker->getId())
		{
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
				this->flyBot->droidChatterSound->play();
			}),
			CallFunc::create([=]()
			{
				this->flyBot->speechBubble->runDialogue(Strings::Dialogue_Story_Intro_HackerMode::create());
			}),
			DelayTime::create(4.0f),
			CallFunc::create([=]()
			{
				this->flyBot->speechBubble->hideDialogue();
			}),
			DelayTime::create(1.0f),
			EaseSineInOut::create(MoveTo::create(2.0f, positionB)),
			CallFunc::create([=]()
			{
				this->flyBot->setVisible(false);
			}),
			nullptr
		));
	}
}
