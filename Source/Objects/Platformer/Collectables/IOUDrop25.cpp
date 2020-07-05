#include "IOUDrop25.h"

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

const std::string IOUDrop25::MapKey = "iou-25";

IOUDrop25* IOUDrop25::create(ValueMap& properties)
{
	IOUDrop25* instance = new IOUDrop25(properties);

	instance->autorelease();

	return instance;
}

IOUDrop25::IOUDrop25(ValueMap& properties) : super(properties)
{
	this->iou = Sprite::create(ItemResources::Collectables_Currency_IOU25);
	this->collectSound = WorldSound::create(SoundResources::Notifications_NotificationPop1);

	this->collectableNode->addChild(this->iou);
	this->addChild(this->collectSound);
}

IOUDrop25::~IOUDrop25()
{
}

void IOUDrop25::initializeListeners()
{
	super::initializeListeners();

	this->onCollected([=]()
	{
		ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
		{
			squally->watchForAttachedBehavior<EntityInventoryBehavior>([&](EntityInventoryBehavior* entityInventoryBehavior)
			{
				entityInventoryBehavior->getCurrencyInventory()->addCurrency(IOU::getIOUIdentifier(), 25);
			});
		}, Squally::MapKey);

		this->collectSound->play();
	});
}
