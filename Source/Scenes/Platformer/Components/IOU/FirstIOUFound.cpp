#include "FirstIOUFound.h"

#include "2d/CCActionEase.h"
#include "2d/CCActionInstant.h"
#include "2d/CCActionInterval.h"
#include "base/CCEventCustom.h"
#include "base/CCEventListenerCustom.h"
#include "base/CCValue.h"

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
			Strings::Platformer_Cutscenes_IOU_FoundIOU::create()->setStringReplacementVariables(Strings::Items_Currency_IOU::create()),
			Strings::Platformer_Cutscenes_IOU_IOUDescription::create(),
			SoundResources::Notifications_NotificationGood1
		));
	});
}

void FirstIOUFound::onDisable()
{
	super::onDisable();
}
