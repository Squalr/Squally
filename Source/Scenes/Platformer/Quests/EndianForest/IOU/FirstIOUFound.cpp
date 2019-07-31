#include "FirstIOUFound.h"

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
#include "Objects/Platformer/Collectables/IOU.h"

#include "Strings/Cutscenes/IOU/FoundIOU.h"
#include "Strings/Cutscenes/IOU/IOUDescription.h"

using namespace cocos2d;

const std::string FirstIOUFound::MapKeyQuest = "first-iou-found";

FirstIOUFound* FirstIOUFound::create(GameObject* owner)
{
	FirstIOUFound* instance = new FirstIOUFound(owner);

	instance->autorelease();

	return instance;
}

FirstIOUFound::FirstIOUFound(GameObject* owner) : super(owner, FirstIOUFound::MapKeyQuest, true)
{
	this->hasRunEvent = false;
	this->iou = static_cast<IOU*>(owner);

	this->iou->onCollected([=]()
	{
		this->broadcastMapEvent(FirstIOUFound::MapKeyQuest, ValueMap());
	});
}

FirstIOUFound::~FirstIOUFound()
{
}

void FirstIOUFound::onLoad(QuestTask::QuestState questState)
{
	switch (questState)
	{
		case QuestTask::QuestState::Active:
		case QuestTask::QuestState::ActiveThroughSkippable:
		{	
			break;
		}
		default:
		{
			break;
		}
	}
}

void FirstIOUFound::onStateChange(QuestTask::QuestState questState, QuestTask::QuestState questStatePrevious)
{
}

void FirstIOUFound::onActivateRunOnce()
{
	this->listenForMapEvent(FirstIOUFound::MapKeyQuest, [=](ValueMap args)
	{
		QuestEvents::TriggerAdvanceToNextQuestTask(QuestEvents::AdvanceNextQuestArgs(this));

		this->runNotification();
	});
}

void FirstIOUFound::runNotification()
{
	PlatformerEvents::TriggerNotificationTakeover(PlatformerEvents::NotificationTakeoverArgs(Strings::Cutscenes_IOU_FoundIOU::create(), Strings::Cutscenes_IOU_IOUDescription::create()));
}
