#include "FirstIOUFound.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Dialogue/SpeechBubble.h"
#include "Engine/Sound/Sound.h"
#include "Events/NotificationEvents.h"
#include "Objects/Platformer/Collectables/IOUDrop.h"

#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string FirstIOUFound::MapKey = "first-iou-found";

FirstIOUFound* FirstIOUFound::create(GameObject* owner)
{
	FirstIOUFound* instance = new FirstIOUFound(owner);

	instance->autorelease();

	return instance;
}

FirstIOUFound::FirstIOUFound(GameObject* owner) : super(owner)
{
	this->iou = dynamic_cast<IOUDrop*>(owner);

	if (this->iou == nullptr)
	{
		this->invalidate();
	}
}

FirstIOUFound::~FirstIOUFound()
{
}

void FirstIOUFound::onLoad()
{
	this->iou->onCollected([=]()
	{
		NotificationEvents::TriggerNotificationTakeover(NotificationEvents::NotificationTakeoverArgs(
			Strings::Platformer_Cutscenes_IOU_FoundIOU::create(),
			Strings::Platformer_Cutscenes_IOU_IOUDescription::create(),
			SoundResources::Notifications_NotificationGood1
		));
	});
}

void FirstIOUFound::onDisable()
{
	super::onDisable();
}
