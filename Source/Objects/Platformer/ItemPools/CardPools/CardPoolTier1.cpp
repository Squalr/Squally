#include "CardPoolTier1.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Scenes/Platformer/Inventory/Items/Collectables/HexusCards/HexusCards.h"

using namespace cocos2d;

CardPoolTier1* CardPoolTier1::create(int maxCards)
{
	CardPoolTier1* instance = new CardPoolTier1(maxCards);

	instance->autorelease();

	return instance;
}

CardPoolTier1::CardPoolTier1(int maxCards) : super(ValueMap(), "card-pool-t1", SampleMethod::Guarantee, 1, maxCards)
{
	this->addItemToPool(ItemChance::create(Binary0::create(), ItemChance::Probability::VeryCommon));
	this->addItemToPool(ItemChance::create(Binary1::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(Binary2::create(), ItemChance::Probability::Uncommon));
	this->addItemToPool(ItemChance::create(Binary3::create(), ItemChance::Probability::Rare));
	this->addItemToPool(ItemChance::create(Binary4::create(), ItemChance::Probability::Epic));
	this->addItemToPool(ItemChance::create(Binary5::create(), ItemChance::Probability::Legendary));
	
	this->addItemToPool(ItemChance::create(Decimal0::create(), ItemChance::Probability::VeryCommon));
	this->addItemToPool(ItemChance::create(Decimal1::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(Decimal2::create(), ItemChance::Probability::Uncommon));
	this->addItemToPool(ItemChance::create(Decimal3::create(), ItemChance::Probability::Rare));
	this->addItemToPool(ItemChance::create(Decimal4::create(), ItemChance::Probability::Epic));
	this->addItemToPool(ItemChance::create(Decimal5::create(), ItemChance::Probability::Legendary));
	
	this->addItemToPool(ItemChance::create(Hex0::create(), ItemChance::Probability::VeryCommon));
	this->addItemToPool(ItemChance::create(Hex1::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(Hex2::create(), ItemChance::Probability::Uncommon));
	this->addItemToPool(ItemChance::create(Hex3::create(), ItemChance::Probability::Rare));
	this->addItemToPool(ItemChance::create(Hex4::create(), ItemChance::Probability::Epic));
	this->addItemToPool(ItemChance::create(Hex5::create(), ItemChance::Probability::Legendary));
}

CardPoolTier1::~CardPoolTier1()
{
}
