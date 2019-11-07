#include "FindSail.h"

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

#include "Strings/Platformer/Quests/EndianForest/Intro/HackerMode.h"

using namespace cocos2d;

const std::string FindSail::MapKeyQuest = "find-sail";

FindSail* FindSail::create(GameObject* owner, QuestLine* questLine,  std::string questTag)
{
	FindSail* instance = new FindSail(owner, questLine, questTag);

	instance->autorelease();

	return instance;
}

FindSail::FindSail(GameObject* owner, QuestLine* questLine, std::string questTag) : super(owner, questLine, FindSail::MapKeyQuest, questTag, false)
{
	this->hasRunEvent = false;
	this->blackbeard = nullptr;
}

FindSail::~FindSail()
{
}

void FindSail::onLoad(QuestState questState)
{
	ObjectEvents::watchForObject<Blackbeard>(this, [=](Blackbeard* blackbeard)
	{
		this->blackbeard = blackbeard;
	});
}

void FindSail::onActivate(bool isActiveThroughSkippable)
{
	this->listenForMapEvent(FindSail::MapKeyQuest, [=](ValueMap args)
	{
		this->complete();

		this->runCinematicSequence();
	});
}

void FindSail::onComplete()
{
}

void FindSail::onSkipped()
{
	this->removeAllListeners();
}

void FindSail::runCinematicSequence()
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
				this->blackbeard->speechBubble->runDialogue(Strings::Platformer_Quests_EndianForest_Intro_HackerMode::create(), 4.0f, [=]()
				{
					PlatformerEvents::TriggerCinematicRestore();
				});
			}),
			nullptr
		));
	}
}
