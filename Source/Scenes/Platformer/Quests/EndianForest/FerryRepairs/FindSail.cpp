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
#include "Entities/Platformer/Npcs/EndianForest/Blackbeard.h"
#include "Events/PlatformerEvents.h"

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
	}, Blackbeard::MapKeyBlackbeard);
}

void FindSail::onActivate(bool isActiveThroughSkippable)
{
	this->runCinematicSequence();
}

void FindSail::onComplete()
{
}

void FindSail::onSkipped()
{
}

void FindSail::runCinematicSequence()
{
	if (this->blackbeard == nullptr)
	{
		return;
	}
	
	this->complete();
}
