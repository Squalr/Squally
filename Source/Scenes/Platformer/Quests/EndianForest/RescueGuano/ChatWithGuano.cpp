#include "ChatWithGuano.h"

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
#include "Entities/Platformer/Helpers/EndianForest/Guano.h"
#include "Events/PlatformerEvents.h"

#include "Strings/Platformer/Quests/EndianForest/Intro/HackerMode.h"

using namespace cocos2d;

const std::string ChatWithGuano::MapKeyQuest = "chat-with-guano";

ChatWithGuano* ChatWithGuano::create(GameObject* owner, QuestLine* questLine,  std::string questTag)
{
	ChatWithGuano* instance = new ChatWithGuano(owner, questLine, questTag);

	instance->autorelease();

	return instance;
}

ChatWithGuano::ChatWithGuano(GameObject* owner, QuestLine* questLine, std::string questTag) : super(owner, questLine, ChatWithGuano::MapKeyQuest, questTag, false)
{
	this->hasRunEvent = false;
	this->guano = nullptr;
}

ChatWithGuano::~ChatWithGuano()
{
}

void ChatWithGuano::onLoad(QuestState questState)
{
	ObjectEvents::watchForObject<Guano>(this, [=](Guano* guano)
	{
		this->guano = guano;
	});
}

void ChatWithGuano::onActivate(bool isActiveThroughSkippable)
{
	this->listenForMapEvent(ChatWithGuano::MapKeyQuest, [=](ValueMap args)
	{
		this->complete();

		this->runCinematicSequence();
	});
}

void ChatWithGuano::onComplete()
{
}

void ChatWithGuano::onSkipped()
{
	this->removeAllListeners();
}

void ChatWithGuano::runCinematicSequence()
{
	if (this->hasRunEvent)
	{
		return;
	}
	
	this->hasRunEvent = true;

	if (this->guano != nullptr)
	{
		PlatformerEvents::TriggerCinematicHijack();

		this->guano->runAction(Sequence::create(
			CallFunc::create([=]()
			{
			}),
			CallFunc::create([=]()
			{
				this->guano->speechBubble->runDialogue(Strings::Platformer_Quests_EndianForest_Intro_HackerMode::create());
			}),
			DelayTime::create(4.0f),
			CallFunc::create([=]()
			{
				PlatformerEvents::TriggerCinematicRestore();
				this->guano->speechBubble->hideDialogue();
			}),
			nullptr
		));
	}
}
