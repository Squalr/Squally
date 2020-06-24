#include "IOUDrop10.h"

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

const std::string IOUDrop10::MapKey = "iou-10";

IOUDrop10* IOUDrop10::create(ValueMap& properties)
{
	IOUDrop10* instance = new IOUDrop10(properties);

	instance->autorelease();

	return instance;
}

IOUDrop10::IOUDrop10(ValueMap& properties) : super(properties)
{
	this->iou = Sprite::create(ItemResources::Collectables_Currency_IOU10);
	this->collectSound = WorldSound::create(SoundResources::Notifications_NotificationPop1);

	this->collectableNode->addChild(this->iou);
	this->addChild(this->collectSound);
}

IOUDrop10::~IOUDrop10()
{
}

void IOUDrop10::initializeListeners()
{
	super::initializeListeners();

	this->onCollected([=]()
	{
		ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
		{
			squally->watchForAttachedBehavior<EntityInventoryBehavior>([&](EntityInventoryBehavior* entityInventoryBehavior)
			{
				entityInventoryBehavior->getCurrencyInventory()->addCurrency(IOU::getIOUIdentifier(), 10);
			});
		}, Squally::MapKey);

		this->collectSound->play();
	});
}
