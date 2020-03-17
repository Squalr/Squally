#include "IOUDrop.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Events/ObjectEvents.h"
#include "Engine/Inventory/CurrencyInventory.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Items/EntityInventoryBehavior.h"
#include "Scenes/Platformer/Inventory/Currencies/IOU.h"

#include "Resources/ItemResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string IOUDrop::MapKeyIOUDrop = "iou";

IOUDrop* IOUDrop::create(ValueMap& properties)
{
	IOUDrop* instance = new IOUDrop(properties);

	instance->autorelease();

	return instance;
}

IOUDrop::IOUDrop(ValueMap& properties) : super(properties)
{
	this->iou = Sprite::create(ItemResources::Collectables_Currency_IOU);

	this->onCollected([=]()
	{
		ObjectEvents::watchForObject<Squally>(this, [=](Squally* squally)
		{
			squally->watchForAttachedBehavior<EntityInventoryBehavior>([&](EntityInventoryBehavior* entityInventoryBehavior)
			{
				entityInventoryBehavior->getCurrencyInventory()->addCurrency(IOU::getIOUIdentifier(), 1);
			});
		}, Squally::MapKeySqually);
	});

	this->collectableNode->addChild(this->iou);
}

IOUDrop::~IOUDrop()
{
}
