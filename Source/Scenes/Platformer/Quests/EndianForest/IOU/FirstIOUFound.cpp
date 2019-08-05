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
#include "Events/NotificationEvents.h"
#include "Objects/Platformer/Collectables/IOU.h"

#include "Strings/Cutscenes/IOU/FoundIOU.h"
#include "Strings/Cutscenes/IOU/IOUDescription.h"

using namespace cocos2d;

const std::string FirstIOUFound::MapKeyQuest = "first-iou-found";

FirstIOUFound* FirstIOUFound::create(GameObject* owner, QuestLine* questLine, std::string questTag)
{
	FirstIOUFound* instance = new FirstIOUFound(owner, questLine, questTag);

	instance->autorelease();

	return instance;
}

FirstIOUFound::FirstIOUFound(GameObject* owner, QuestLine* questLine, std::string questTag) : super(owner, questLine, FirstIOUFound::MapKeyQuest, questTag, true)
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

void FirstIOUFound::onLoad(QuestState questState)
{
}

void FirstIOUFound::onActivate(bool isActiveThroughSkippable)
{
	this->listenForMapEvent(FirstIOUFound::MapKeyQuest, [=](ValueMap args)
	{
		this->complete();

		this->runNotification();
	});
}

void FirstIOUFound::onComplete()
{
}

void FirstIOUFound::onSkipped()
{
}

void FirstIOUFound::runNotification()
{
	NotificationEvents::TriggerNotificationTakeover(NotificationEvents::NotificationTakeoverArgs(Strings::Cutscenes_IOU_FoundIOU::create(), Strings::Cutscenes_IOU_IOUDescription::create()));
}
