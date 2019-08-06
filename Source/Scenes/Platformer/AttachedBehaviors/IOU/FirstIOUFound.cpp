#include "FirstIOUFound.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/AttachedBehavior/AttachedBehavior.h"
#include "Engine/Dialogue/SpeechBubble.h"
#include "Engine/Sound/Sound.h"
#include "Events/NotificationEvents.h"
#include "Objects/Platformer/Collectables/IOU.h"

#include "Strings/Cutscenes/IOU/FoundIOU.h"
#include "Strings/Cutscenes/IOU/IOUDescription.h"

using namespace cocos2d;

const std::string FirstIOUFound::MapKeyAttachedBehavior = "first-iou-found";

FirstIOUFound* FirstIOUFound::create(GameObject* owner, std::string attachedBehaviorArgs)
{
	FirstIOUFound* instance = new FirstIOUFound(owner, attachedBehaviorArgs);

	instance->autorelease();

	return instance;
}

FirstIOUFound::FirstIOUFound(GameObject* owner, std::string attachedBehaviorArgs) : super(owner, attachedBehaviorArgs)
{
	this->iou = static_cast<IOU*>(owner);
}

FirstIOUFound::~FirstIOUFound()
{
}

void FirstIOUFound::onLoad()
{
	this->iou->onCollected([=]()
	{
		NotificationEvents::TriggerNotificationTakeover(NotificationEvents::NotificationTakeoverArgs(Strings::Cutscenes_IOU_FoundIOU::create(), Strings::Cutscenes_IOU_IOUDescription::create()));
	});
}
