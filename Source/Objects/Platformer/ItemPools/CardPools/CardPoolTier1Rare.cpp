#include "CardPoolTier1Rare.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
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
	this->addItemToPool(ItemChance::create(Binary0::create(), ItemChance::Probability::Rare));
	this->addItemToPool(ItemChance::create(Binary1::create(), ItemChance::Probability::Rare));
	this->addItemToPool(ItemChance::create(Binary2::create(), ItemChance::Probability::Rare));
	this->addItemToPool(ItemChance::create(Binary3::create(), ItemChance::Probability::Rare));
	this->addItemToPool(ItemChance::create(Binary4::create(), ItemChance::Probability::Epic));
	this->addItemToPool(ItemChance::create(Binary5::create(), ItemChance::Probability::Legendary));
	
	this->addItemToPool(ItemChance::create(Decimal0::create(), ItemChance::Probability::Rare));
	this->addItemToPool(ItemChance::create(Decimal1::create(), ItemChance::Probability::Rare));
	this->addItemToPool(ItemChance::create(Decimal2::create(), ItemChance::Probability::Rare));
	this->addItemToPool(ItemChance::create(Decimal3::create(), ItemChance::Probability::Rare));
	this->addItemToPool(ItemChance::create(Decimal4::create(), ItemChance::Probability::Epic));
	this->addItemToPool(ItemChance::create(Decimal5::create(), ItemChance::Probability::Legendary));
	
	this->addItemToPool(ItemChance::create(Hex0::create(), ItemChance::Probability::Rare));
	this->addItemToPool(ItemChance::create(Hex1::create(), ItemChance::Probability::Rare));
	this->addItemToPool(ItemChance::create(Hex2::create(), ItemChance::Probability::Rare));
	this->addItemToPool(ItemChance::create(Hex3::create(), ItemChance::Probability::Rare));
	this->addItemToPool(ItemChance::create(Hex4::create(), ItemChance::Probability::Epic));
	this->addItemToPool(ItemChance::create(Hex5::create(), ItemChance::Probability::Legendary));
}

CardPoolTier1Rare::~CardPoolTier1Rare()
{
}
