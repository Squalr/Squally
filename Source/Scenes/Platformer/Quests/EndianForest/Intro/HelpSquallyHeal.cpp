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
#include "Entities/Platformer/Helpers/EndianForest/FlyBot.h"
#include "Events/PlatformerEvents.h"
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
	this->flyBot = nullptr;
}

HelpSquallyHeal::~HelpSquallyHeal()
{
}

void HelpSquallyHeal::onLoad(QuestState questState)
{
	this->scheduleUpdate();
}

void HelpSquallyHeal::onActivate(bool isActiveThroughSkippable)
{
	this->listenForMapEvent(HelpSquallyHeal::MapKeyQuest, [=](ValueMap args)
	{
		this->complete();

		this->runCinematicSequence();
	});
}

void HelpSquallyHeal::onComplete()
{
}

void HelpSquallyHeal::onSkipped()
{
	this->removeAllListeners();
}

void HelpSquallyHeal::update(float dt)
{
	super::update(dt);

	if (this->flyBot == nullptr)
	{
		ObjectEvents::QueryObjects(QueryObjectsArgs<FlyBot>([&](FlyBot* flyBot)
		{
			this->flyBot = flyBot;
		}));
	}
}

void HelpSquallyHeal::runCinematicSequence()
{
	if (this->hasRunEvent)
	{
		return;
	}

	this->hasRunEvent = true;

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
			nullptr
		));
	}
}
