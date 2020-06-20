#include "CardPoolTier2.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Scenes/Platformer/Inventory/Items/Collectables/HexusCards/HexusCards.h"

using namespace cocos2d;

CardPoolTier2* CardPoolTier2::create(SampleMethod sampleMethod, int min, int max)
{
	CardPoolTier2* instance = new CardPoolTier2(sampleMethod, min, max);

	instance->autorelease();

	return instance;
}

CardPoolTier2::CardPoolTier2(SampleMethod sampleMethod, int min, int max) : super(ValueMap(), "card-pool-t2", sampleMethod, min, max)
{
	this->addItemToPool(ItemChance::create(Binary0::create(), ItemChance::Probability::Rare));
	this->addItemToPool(ItemChance::create(Binary1::create(), ItemChance::Probability::Rare));
	this->addItemToPool(ItemChance::create(Binary2::create(), ItemChance::Probability::Epic));
	this->addItemToPool(ItemChance::create(Binary3::create(), ItemChance::Probability::Legendary));
	this->addItemToPool(ItemChance::create(Binary4::create(), ItemChance::Probability::Artifact));
	
	this->addItemToPool(ItemChance::create(Decimal0::create(), ItemChance::Probability::Rare));
	this->addItemToPool(ItemChance::create(Decimal1::create(), ItemChance::Probability::Rare));
	this->addItemToPool(ItemChance::create(Decimal2::create(), ItemChance::Probability::Epic));
	this->addItemToPool(ItemChance::create(Decimal3::create(), ItemChance::Probability::Legendary));
	this->addItemToPool(ItemChance::create(Decimal4::create(), ItemChance::Probability::Artifact));
	
	this->addItemToPool(ItemChance::create(Hex0::create(), ItemChance::Probability::Rare));
	this->addItemToPool(ItemChance::create(Hex1::create(), ItemChance::Probability::Rare));
	this->addItemToPool(ItemChance::create(Hex2::create(), ItemChance::Probability::Epic));
	this->addItemToPool(ItemChance::create(Hex3::create(), ItemChance::Probability::Legendary));
	this->addItemToPool(ItemChance::create(Hex4::create(), ItemChance::Probability::Artifact));

	this->addItemToPool(ItemChance::create(SpecialFlip1::create(), ItemChance::Probability::Rare));
	this->addItemToPool(ItemChance::create(SpecialFlip2::create(), ItemChance::Probability::Epic));

	this->addItemToPool(ItemChance::create(SpecialMov::create(), ItemChance::Probability::Epic));
	this->addItemToPool(ItemChance::create(SpecialAdd::create(), ItemChance::Probability::Epic));
	this->addItemToPool(ItemChance::create(SpecialShr::create(), ItemChance::Probability::Artifact));
	this->addItemToPool(ItemChance::create(SpecialShl::create(), ItemChance::Probability::Artifact));
}

CardPoolTier2::~CardPoolTier2()
{
}
