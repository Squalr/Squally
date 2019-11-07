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
#include "Entities/Platformer/Helpers/EndianForest/Scrappy.h"
#include "Events/PlatformerEvents.h"

#include "Strings/Platformer/Quests/EndianForest/Intro/TentHeal.h"

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
	this->scrappy = nullptr;
}

HelpSquallyHeal::~HelpSquallyHeal()
{
}

void HelpSquallyHeal::onLoad(QuestState questState)
{
	ObjectEvents::watchForObject<Scrappy>(this, [=](Scrappy* scrappy)
	{
		this->scrappy = scrappy;
	});
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

void HelpSquallyHeal::runCinematicSequence()
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
				this->scrappy->droidBrief2Sound->play();
			}),
			CallFunc::create([=]()
			{
				this->scrappy->speechBubble->runDialogue(Strings::Platformer_Quests_EndianForest_Intro_TentHeal::create(), 4.0f, [=]()
				{
					PlatformerEvents::TriggerCinematicRestore();
				});
			}),
			nullptr
		));
	}
}
