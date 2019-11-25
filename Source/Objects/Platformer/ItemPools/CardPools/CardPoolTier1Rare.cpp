#include "CardPoolTier1Rare.h"

#include "cocos/base/CCValue.h"

#include "Scenes/Platformer/Inventory/Items/Collectables/HexusCards/HexusCards.h"

using namespace cocos2d;

CardPoolTier1Rare* CardPoolTier1Rare::create()
{
	CardPoolTier1Rare* instance = new CardPoolTier1Rare();

	instance->autorelease();

	return instance;
}

CardPoolTier1Rare::CardPoolTier1Rare() : super(ValueMap(), "card-pool-t1-rare", 1, 1)
{
	this->addItemToPool(nullptr, 85.15f);

	this->addItemToPool(Binary0::create(), 1.75f);
	this->addItemToPool(Binary1::create(), 1.25f);
	this->addItemToPool(Binary2::create(), 0.75f);
	this->addItemToPool(Binary3::create(), 0.15f);
	this->addItemToPool(Binary4::create(), 0.05f);
	this->addItemToPool(Binary5::create(), 0.01f);
	
	this->addItemToPool(Decimal0::create(), 1.75f);
	this->addItemToPool(Decimal1::create(), 1.25f);
	this->addItemToPool(Decimal2::create(), 0.75f);
	this->addItemToPool(Decimal3::create(), 0.15f);
	this->addItemToPool(Decimal4::create(), 0.05f);
	
	this->addItemToPool(Hex0::create(), 1.75f);
	this->addItemToPool(Hex1::create(), 1.25f);
	this->addItemToPool(Hex2::create(), 0.75);
	this->addItemToPool(Hex3::create(), 0.15f);
	this->addItemToPool(Hex4::create(), 0.05f);
}

CardPoolTier1Rare::~CardPoolTier1Rare()
{
}
