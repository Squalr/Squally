#include "RescueGuano.h"

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
#include "Entities/Platformer/Npcs/EndianForest/Blackbeard.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Cinematic/CinematicMarker.h"

#include "Strings/Platformer/Quests/EndianForest/Intro/HackerMode.h"

using namespace cocos2d;

const std::string RescueGuano::MapKeyQuest = "find-elriel";

RescueGuano* RescueGuano::create(GameObject* owner, QuestLine* questLine,  std::string questTag)
{
	RescueGuano* instance = new RescueGuano(owner, questLine, questTag);

	instance->autorelease();

	return instance;
}

RescueGuano::RescueGuano(GameObject* owner, QuestLine* questLine, std::string questTag) : super(owner, questLine, RescueGuano::MapKeyQuest, questTag, false)
{
	this->hasRunEvent = false;
	this->blackbeard = nullptr;
}

RescueGuano::~RescueGuano()
{
}

void RescueGuano::onLoad(QuestState questState)
{
	ObjectEvents::watchForObject<Blackbeard>(this, [=](Blackbeard* blackbeard)
	{
		this->blackbeard = blackbeard;
	});
}

void RescueGuano::onActivate(bool isActiveThroughSkippable)
{
	this->listenForMapEvent(RescueGuano::MapKeyQuest, [=](ValueMap args)
	{
		this->complete();

		this->runCinematicSequence();
	});
}

void RescueGuano::onComplete()
{
}

void RescueGuano::onSkipped()
{
	this->removeAllListeners();
}

void RescueGuano::runCinematicSequence()
{
	if (this->hasRunEvent)
	{
		return;
	}
	
	this->hasRunEvent = true;

	if (this->blackbeard != nullptr)
	{
		PlatformerEvents::TriggerCinematicHijack();

		this->blackbeard->runAction(Sequence::create(
			CallFunc::create([=]()
			{
			}),
			CallFunc::create([=]()
			{
				this->blackbeard->speechBubble->runDialogue(Strings::Platformer_Quests_EndianForest_Intro_HackerMode::create());
			}),
			DelayTime::create(4.0f),
			CallFunc::create([=]()
			{
				PlatformerEvents::TriggerCinematicRestore();
				this->blackbeard->speechBubble->hideDialogue();
			}),
			nullptr
		));
	}
}
