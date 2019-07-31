#include "Doubloon.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Inventory/CurrencyInventory.h"
#include "Engine/Utils/GameUtils.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"
#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/ObjectResources.h"

#include "Strings/Items/Currency/Doubloons.h"

using namespace cocos2d;

const std::string Doubloon::MapKeyDoubloon = "doubloon";

Doubloon* Doubloon::create(ValueMap& initProperties)
{
	Doubloon* instance = new Doubloon(initProperties);

	instance->autorelease();

	return instance;
}

Doubloon::Doubloon(ValueMap& initProperties) : super(initProperties)
{
	this->doubloon = SmartAnimationSequenceNode::create(ObjectResources::Collectables_Doubloon_Doubloon_0000);

	this->onCollected([=]()
	{
		CurrencyInventory* playerCurrencyInventory = CurrencyInventory::create(SaveKeys::SaveKeySquallyCurrencyInventory);

		playerCurrencyInventory->addCurrency(Doubloon::getIdentifier(), 1);
	});

	this->collectableNode->addChild(this->doubloon);
}

Doubloon::~Doubloon()
{
}

void Doubloon::onEnter()
{
	super::onEnter();

	this->doubloon->playAnimationRepeat(ObjectResources::Collectables_Doubloon_Doubloon_0000, 0.1f);
}

std::string Doubloon::getIdentifier()
{
	return "Doubloons";
}

std::string Doubloon::getIconResource()
{
	return ObjectResources::Collectables_Doubloon_Doubloon_0000;
}

LocalizedString* Doubloon::getString()
{
	return Strings::Items_Currency_Doubloons::create();
}
