#include "Task4.h"

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

#include "Strings/Dialogue/Story/Intro/OgreSpotted.h"

using namespace cocos2d;

const std::string Task4::MapKeyQuest = "task4";

Task4* Task4::create(GameObject* owner, std::string questLine, std::string questTag)
{
	Task4* instance = new Task4(owner, questLine, questTag);

	instance->autorelease();

	return instance;
}

Task4::Task4(GameObject* owner, std::string questLine, std::string questTag) : super(owner, questLine, Task4::MapKeyQuest, questTag, true)
{
	this->hasRunEvent = false;
	this->flyBot = static_cast<FlyBot*>(owner);
}

Task4::~Task4()
{
}

void Task4::onStateChange(QuestTask::QuestState questState, QuestTask::QuestState questStatePrevious)
{
}

void Task4::onActivateRunOnce()
{
	this->listenForMapEvent(Task4::MapKeyQuest, [=](ValueMap args)
	{
		QuestEvents::TriggerAdvanceToNextQuestTask(QuestEvents::AdvanceNextQuestArgs(this));

		this->runCinematicSequence();
	});
}

void Task4::enable(bool isSkippable)
{
	if (this->flyBot != nullptr)
	{
		this->flyBot->animationNode->setFlippedX(true);
	}
}

void Task4::disable()
{
	this->removeAllListeners();
	
	if (this->flyBot != nullptr)
	{
		this->flyBot->setVisible(false);
	}
}

void Task4::runCinematicSequence()
{
	if (this->hasRunEvent)
	{
		return;
	}
	
	this->hasRunEvent = true;

	if (this->flyBot != nullptr)
	{
		this->runAction(Sequence::create(
			CallFunc::create([=]()
			{
				this->flyBot->droidChatterSound->play();
			}),
			CallFunc::create([=]()
			{
				this->flyBot->speechBubble->runDialogue(Strings::Dialogue_Story_Intro_OgreSpotted::create());
			}),
			DelayTime::create(4.0f),
			CallFunc::create([=]()
			{
			}),
			DelayTime::create(4.0f),
			CallFunc::create([=]()
			{
				this->flyBot->speechBubble->hideDialogue();
			}),
			nullptr
		));
	}
}
