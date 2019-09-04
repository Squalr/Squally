#include "TeachHackerMode.h"

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
#include "Entities/Platformer/Helpers/EndianForest/Scrappy.h"
#include "Events/PlatformerEvents.h"

#include "Strings/Platformer/Quests/EndianForest/Intro/HackerMode.h"

using namespace cocos2d;

const std::string TeachHackerMode::MapKeyQuest = "teach-hacker-mode";

TeachHackerMode* TeachHackerMode::create(GameObject* owner, QuestLine* questLine,  std::string questTag)
{
	TeachHackerMode* instance = new TeachHackerMode(owner, questLine, questTag);

	instance->autorelease();

	return instance;
}

TeachHackerMode::TeachHackerMode(GameObject* owner, QuestLine* questLine, std::string questTag) : super(owner, questLine, TeachHackerMode::MapKeyQuest, questTag, false)
{
	this->hasRunEvent = false;
	this->scrappy = nullptr;
}

TeachHackerMode::~TeachHackerMode()
{
}

void TeachHackerMode::onLoad(QuestState questState)
{
	ObjectEvents::watchForObject<Scrappy>(this, [=](Scrappy* scrappy)
	{
		this->scrappy = scrappy;
	});
}

void TeachHackerMode::onActivate(bool isActiveThroughSkippable)
{
	this->listenForMapEvent(TeachHackerMode::MapKeyQuest, [=](ValueMap args)
	{
		this->complete();

		this->runCinematicSequence();
	});
}

void TeachHackerMode::onComplete()
{
}

void TeachHackerMode::onSkipped()
{
	this->removeAllListeners();
}

void TeachHackerMode::runCinematicSequence()
{
	if (this->hasRunEvent)
	{
		return;
	}
	
	this->hasRunEvent = true;

	if (this->scrappy != nullptr)
	{
		PlatformerEvents::TriggerCinematicHijack();

		this->scrappy->runAction(Sequence::create(
			CallFunc::create([=]()
			{
				this->scrappy->droidChatterSound->play();
			}),
			CallFunc::create([=]()
			{
				this->scrappy->speechBubble->runDialogue(Strings::Platformer_Quests_EndianForest_Intro_HackerMode::create());
			}),
			DelayTime::create(4.0f),
			CallFunc::create([=]()
			{
				PlatformerEvents::TriggerCinematicRestore();
				this->scrappy->speechBubble->hideDialogue();
			}),
			nullptr
		));
	}
}
