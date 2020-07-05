#include "IOUDrop5.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Events/ObjectEvents.h"
#include "Engine/Inventory/CurrencyInventory.h"
#include "Engine/Sound/WorldSound.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Inventory/EntityInventoryBehavior.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string IOUDrop5::MapKey = "iou-5";

IOUDrop5* IOUDrop5::create(ValueMap& properties)
{
	IOUDrop5* instance = new IOUDrop5(properties);

	instance->autorelease();

	return instance;
}

IOUDrop5::IOUDrop5(ValueMap& properties) : super(properties)
{
	this->iou = Sprite::create(ItemResources::Collectables_Currency_IOU5);
	this->collectSound = WorldSound::create(SoundResources::Notifications_NotificationPop1);

	this->collectableNode->addChild(this->iou);
	this->addChild(this->collectSound);
}

IOUDrop5::~IOUDrop5()
{
}

void IOUDrop5::initializeListeners()
{
	super::initializeListeners();

	this->onCollected([=]()
	{
		ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
		{
			squally->watchForAttachedBehavior<EntityInventoryBehavior>([&](EntityInventoryBehavior* entityInventoryBehavior)
			{
				entityInventoryBehavior->getCurrencyInventory()->addCurrency(IOU::getIOUIdentifier(), 5);
			});
		}, Squally::MapKey);

		this->collectSound->play();
	});
}
