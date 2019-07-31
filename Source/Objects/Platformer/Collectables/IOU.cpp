#include "IOU.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Localization/LocalizedString.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Inventory/CurrencyInventory.h"
#include "Engine/Utils/GameUtils.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"
#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/ObjectResources.h"

#include "Strings/Items/Currency/IOUs.h"

using namespace cocos2d;

const std::string IOU::MapKeyIOU = "iou";

IOU* IOU::create(ValueMap& initProperties)
{
	IOU* instance = new IOU(initProperties);

	instance->autorelease();

	return instance;
}

IOU::IOU(ValueMap& initProperties) : super(initProperties)
{
	this->iou = Sprite::create(ObjectResources::Items_Consumables_IOU);

	this->onCollected([=]()
	{
		CurrencyInventory* playerCurrencyInventory = CurrencyInventory::create(SaveKeys::SaveKeySquallyCurrencyInventory);

		playerCurrencyInventory->addCurrency(IOU::getIdentifier(), 1);
	});

	this->collectableNode->addChild(this->iou);
}

IOU::~IOU()
{
}

std::string IOU::getIdentifier()
{
	return "IOU";
}

std::string IOU::getIconResource()
{
	return ObjectResources::Items_Consumables_IOU;
}

LocalizedString* IOU::getString()
{
	return Strings::Items_Currency_IOUs::create();
}
