#include "FindElriel.h"

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

#include "Strings/Platformer/Quests/Intro/HackerMode.h"

using namespace cocos2d;

const std::string FindElriel::MapKeyQuest = "find-elriel";

FindElriel* FindElriel::create(GameObject* owner, QuestLine* questLine,  std::string questTag)
{
	FindElriel* instance = new FindElriel(owner, questLine, questTag);

	instance->autorelease();

	return instance;
}

FindElriel::FindElriel(GameObject* owner, QuestLine* questLine, std::string questTag) : super(owner, questLine, FindElriel::MapKeyQuest, questTag, false)
{
	this->hasRunEvent = false;
	this->blackbeard = nullptr;
}

FindElriel::~FindElriel()
{
}

void FindElriel::onLoad(QuestState questState)
{
	ObjectEvents::watchForObject<Blackbeard>(this, [=](Blackbeard* blackbeard)
	{
		this->blackbeard = blackbeard;
	});
}

void FindElriel::onActivate(bool isActiveThroughSkippable)
{
	this->listenForMapEvent(FindElriel::MapKeyQuest, [=](ValueMap args)
	{
		this->complete();

		this->runCinematicSequence();
	});
}

void FindElriel::onComplete()
{
}

void FindElriel::onSkipped()
{
	this->removeAllListeners();
}

void FindElriel::runCinematicSequence()
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
				this->blackbeard->speechBubble->runDialogue(Strings::Platformer_Quests_Intro_HackerMode::create());
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
