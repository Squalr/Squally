#include "ReturnToQueen.h"

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

const std::string ReturnToQueen::MapKeyQuest = "return-to-queen";

ReturnToQueen* ReturnToQueen::create(GameObject* owner, QuestLine* questLine,  std::string questTag)
{
	ReturnToQueen* instance = new ReturnToQueen(owner, questLine, questTag);

	instance->autorelease();

	return instance;
}

ReturnToQueen::ReturnToQueen(GameObject* owner, QuestLine* questLine, std::string questTag) : super(owner, questLine, ReturnToQueen::MapKeyQuest, questTag, false)
{
	this->queenLiana = nullptr;
}

ReturnToQueen::~ReturnToQueen()
{
}

void ReturnToQueen::onLoad(QuestState questState)
{
	ObjectEvents::watchForObject<QueenLiana>(this, [=](QueenLiana* queenLiana)
	{
		this->queenLiana = queenLiana;
	}, QueenLiana::MapKeyQueenLiana);
}

void ReturnToQueen::onActivate(bool isActiveThroughSkippable)
{
	this->listenForMapEventOnce(ReturnToQueen::MapKeyQuest, [=](ValueMap args)
	{
		this->complete();

		this->runCinematicSequence();
	});
}

void ReturnToQueen::onComplete()
{
}

void ReturnToQueen::onSkipped()
{
	this->removeAllListeners();
}

void ReturnToQueen::runCinematicSequence()
{
	if (this->queenLiana != nullptr)
	{
	}
}
