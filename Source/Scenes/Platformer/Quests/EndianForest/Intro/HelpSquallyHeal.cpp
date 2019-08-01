#include "HelpSquallyHeal.h"

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

const std::string HelpSquallyHeal::MapKeyQuest = "help-squally-heal";

HelpSquallyHeal* HelpSquallyHeal::create(GameObject* owner, QuestLine* questLine, std::string questTag)
{
	HelpSquallyHeal* instance = new HelpSquallyHeal(owner, questLine, questTag);

	instance->autorelease();

	return instance;
}

HelpSquallyHeal::HelpSquallyHeal(GameObject* owner, QuestLine* questLine, std::string questTag) : super(owner, questLine, HelpSquallyHeal::MapKeyQuest, questTag, true)
{
	this->hasRunEvent = false;
	this->flyBot = static_cast<FlyBot*>(owner);
}

HelpSquallyHeal::~HelpSquallyHeal()
{
}

/*
void HelpSquallyHeal::onStateChange(QuestTask::QuestState questState, QuestTask::QuestState questStatePrevious)
{
}

void HelpSquallyHeal::onActivateRunOnce()
{
	this->listenForMapEvent(HelpSquallyHeal::MapKeyQuest, [=](ValueMap args)
	{
		QuestEvents::TriggerAdvanceToNextQuestTask(QuestEvents::AdvanceNextQuestArgs(this));

		this->runCinematicSequence();
	});
}

void HelpSquallyHeal::enable(bool isSkippable)
{
	if (this->flyBot != nullptr)
	{
		this->flyBot->animationNode->setFlippedX(true);
	}
}

void HelpSquallyHeal::disable()
{
	this->removeAllListeners();

	if (this->flyBot != nullptr)
	{
		this->flyBot->setVisible(false);
	}
}
*/

void HelpSquallyHeal::runCinematicSequence()
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
		PlatformerEvents::TriggerCinematicHijack();

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
				PlatformerEvents::TriggerCinematicRestore();
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
