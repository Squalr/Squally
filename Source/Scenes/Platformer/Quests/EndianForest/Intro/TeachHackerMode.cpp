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
#include "Events/PlatformerEvents.h"
#include "Entities/Platformer/Misc/DaemonsHallow/FlyBot.h"
#include "Objects/Platformer/Cinematic/CinematicMarker.h"

#include "Strings/Dialogue/Story/Intro/HackerMode.h"

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
	this->flyBot = dynamic_cast<FlyBot*>(owner);
}

TeachHackerMode::~TeachHackerMode()
{
}

void TeachHackerMode::onLoad(QuestState questState)
{
	if (this->flyBot != nullptr)
	{
		this->flyBot->animationNode->setFlippedX(true);
	}
	
	if (!this->isActive())
	{
		if (this->flyBot != nullptr)
		{
			this->flyBot->setVisible(false);
		}
	}
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
	
	if (this->flyBot != nullptr)
	{
		this->flyBot->setVisible(false);
	}
}

void TeachHackerMode::runCinematicSequence()
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
		PlatformerEvents::TriggerCinematicHijack();

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
				PlatformerEvents::TriggerCinematicRestore();
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
