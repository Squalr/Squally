#include "TalkToQueen.h"

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
#include "Entities/Platformer/Npcs/EndianForest/QueenLiana.h"
#include "Events/PlatformerEvents.h"

using namespace cocos2d;

const std::string TalkToQueen::MapKeyQuest = "talk-to-queen";

TalkToQueen* TalkToQueen::create(GameObject* owner, QuestLine* questLine,  std::string questTag)
{
	TalkToQueen* instance = new TalkToQueen(owner, questLine, questTag);

	instance->autorelease();

	return instance;
}

TalkToQueen::TalkToQueen(GameObject* owner, QuestLine* questLine, std::string questTag) : super(owner, questLine, TalkToQueen::MapKeyQuest, questTag, false)
{
	this->hasRunEvent = false;
	this->queenLiana = nullptr;
}

TalkToQueen::~TalkToQueen()
{
}

void TalkToQueen::onLoad(QuestState questState)
{
	ObjectEvents::watchForObject<QueenLiana>(this, [=](QueenLiana* queenLiana)
	{
		this->queenLiana = queenLiana;
	}, QueenLiana::MapKeyQueenLiana);
}

void TalkToQueen::onActivate(bool isActiveThroughSkippable)
{
	this->listenForMapEvent(TalkToQueen::MapKeyQuest, [=](ValueMap args)
	{
		this->complete();

		this->runCinematicSequence();
	});
}

void TalkToQueen::onComplete()
{
}

void TalkToQueen::onSkipped()
{
	this->removeAllListeners();
}

void TalkToQueen::runCinematicSequence()
{
	if (this->hasRunEvent)
	{
		return;
	}
	
	this->hasRunEvent = true;

	if (this->queenLiana != nullptr)
	{
	}
}
