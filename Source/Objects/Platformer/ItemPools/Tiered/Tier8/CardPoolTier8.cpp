#include "CardPoolTier8.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Scenes/Platformer/Inventory/Items/Collectables/HexusCards/HexusCards.h"

using namespace cocos2d;

CardPoolTier8* CardPoolTier8::create(SampleMethod sampleMethod, int min, int max)
{
	CardPoolTier8* instance = new CardPoolTier8(sampleMethod, min, max);

	instance->autorelease();

	return instance;
}

CardPoolTier8::CardPoolTier8(SampleMethod sampleMethod, int min, int max) : super(ValueMap(), "card-pool-t8", sampleMethod, min, max)
{
	this->addItemToPool(ItemChance::create(Binary0::create(), ItemChance::Probability::Rare));
	this->addItemToPool(ItemChance::create(Binary1::create(), ItemChance::Probability::Rare));
	this->addItemToPool(ItemChance::create(Binary2::create(), ItemChance::Probability::Rare));
	this->addItemToPool(ItemChance::create(Binary3::create(), ItemChance::Probability::Rare));
	this->addItemToPool(ItemChance::create(Binary4::create(), ItemChance::Probability::Rare));
	this->addItemToPool(ItemChance::create(Binary5::create(), ItemChance::Probability::Rare));
	this->addItemToPool(ItemChance::create(Binary6::create(), ItemChance::Probability::Rare));
	this->addItemToPool(ItemChance::create(Binary7::create(), ItemChance::Probability::Rare));
	this->addItemToPool(ItemChance::create(Binary8::create(), ItemChance::Probability::Rare));
	this->addItemToPool(ItemChance::create(Binary9::create(), ItemChance::Probability::Rare));
	this->addItemToPool(ItemChance::create(Binary10::create(), ItemChance::Probability::Rare));
	this->addItemToPool(ItemChance::create(Binary11::create(), ItemChance::Probability::Rare));
	this->addItemToPool(ItemChance::create(Binary12::create(), ItemChance::Probability::Rare));
	this->addItemToPool(ItemChance::create(Binary13::create(), ItemChance::Probability::Rare));
	this->addItemToPool(ItemChance::create(Binary14::create(), ItemChance::Probability::Rare));
	this->addItemToPool(ItemChance::create(Binary15::create(), ItemChance::Probability::Rare));

	this->addItemToPool(ItemChance::create(Decimal0::create(), ItemChance::Probability::Rare));
	this->addItemToPool(ItemChance::create(Decimal1::create(), ItemChance::Probability::Rare));
	this->addItemToPool(ItemChance::create(Decimal2::create(), ItemChance::Probability::Rare));
	this->addItemToPool(ItemChance::create(Decimal3::create(), ItemChance::Probability::Rare));
	this->addItemToPool(ItemChance::create(Decimal4::create(), ItemChance::Probability::Rare));
	this->addItemToPool(ItemChance::create(Decimal5::create(), ItemChance::Probability::Rare));
	this->addItemToPool(ItemChance::create(Decimal6::create(), ItemChance::Probability::Rare));
	this->addItemToPool(ItemChance::create(Decimal7::create(), ItemChance::Probability::Rare));
	this->addItemToPool(ItemChance::create(Decimal8::create(), ItemChance::Probability::Rare));
	this->addItemToPool(ItemChance::create(Decimal9::create(), ItemChance::Probability::Rare));
	this->addItemToPool(ItemChance::create(Decimal10::create(), ItemChance::Probability::Rare));
	this->addItemToPool(ItemChance::create(Decimal11::create(), ItemChance::Probability::Rare));
	this->addItemToPool(ItemChance::create(Decimal12::create(), ItemChance::Probability::Rare));
	this->addItemToPool(ItemChance::create(Decimal13::create(), ItemChance::Probability::Rare));
	this->addItemToPool(ItemChance::create(Decimal14::create(), ItemChance::Probability::Rare));
	this->addItemToPool(ItemChance::create(Decimal15::create(), ItemChance::Probability::Rare));
	
	this->addItemToPool(ItemChance::create(Hex0::create(), ItemChance::Probability::Rare));
	this->addItemToPool(ItemChance::create(Hex1::create(), ItemChance::Probability::Rare));
	this->addItemToPool(ItemChance::create(Hex2::create(), ItemChance::Probability::Rare));
	this->addItemToPool(ItemChance::create(Hex3::create(), ItemChance::Probability::Rare));
	this->addItemToPool(ItemChance::create(Hex4::create(), ItemChance::Probability::Rare));
	this->addItemToPool(ItemChance::create(Hex5::create(), ItemChance::Probability::Rare));
	this->addItemToPool(ItemChance::create(Hex6::create(), ItemChance::Probability::Rare));
	this->addItemToPool(ItemChance::create(Hex7::create(), ItemChance::Probability::Rare));
	this->addItemToPool(ItemChance::create(Hex8::create(), ItemChance::Probability::Rare));
	this->addItemToPool(ItemChance::create(Hex9::create(), ItemChance::Probability::Rare));
	this->addItemToPool(ItemChance::create(Hex10::create(), ItemChance::Probability::Rare));
	this->addItemToPool(ItemChance::create(Hex11::create(), ItemChance::Probability::Rare));
	this->addItemToPool(ItemChance::create(Hex12::create(), ItemChance::Probability::Rare));
	this->addItemToPool(ItemChance::create(Hex13::create(), ItemChance::Probability::Rare));
	this->addItemToPool(ItemChance::create(Hex14::create(), ItemChance::Probability::Rare));
	this->addItemToPool(ItemChance::create(Hex15::create(), ItemChance::Probability::Rare));

	this->addItemToPool(ItemChance::create(SpecialReturnToHand::create(), ItemChance::Probability::Artifact));
	this->addItemToPool(ItemChance::create(SpecialPeek::create(), ItemChance::Probability::Artifact));
	this->addItemToPool(ItemChance::create(SpecialBonusMoves::create(), ItemChance::Probability::Artifact));
	this->addItemToPool(ItemChance::create(SpecialPush::create(), ItemChance::Probability::Artifact));
	this->addItemToPool(ItemChance::create(SpecialPop::create(), ItemChance::Probability::Artifact));
	this->addItemToPool(ItemChance::create(SpecialAbsorb::create(), ItemChance::Probability::Artifact));
	this->addItemToPool(ItemChance::create(SpecialSteal::create(), ItemChance::Probability::Artifact));
	this->addItemToPool(ItemChance::create(SpecialGreed::create(), ItemChance::Probability::Artifact));
	this->addItemToPool(ItemChance::create(SpecialShrCircular::create(), ItemChance::Probability::Artifact));
	this->addItemToPool(ItemChance::create(SpecialShlCircular::create(), ItemChance::Probability::Artifact));
	this->addItemToPool(ItemChance::create(SpecialFlip1::create(), ItemChance::Probability::Artifact));
	this->addItemToPool(ItemChance::create(SpecialFlip2::create(), ItemChance::Probability::Artifact));
	this->addItemToPool(ItemChance::create(SpecialFlip3::create(), ItemChance::Probability::Artifact));
	this->addItemToPool(ItemChance::create(SpecialFlip4::create(), ItemChance::Probability::Artifact));
	this->addItemToPool(ItemChance::create(SpecialInv::create(), ItemChance::Probability::Artifact));
	this->addItemToPool(ItemChance::create(SpecialMov::create(), ItemChance::Probability::Artifact));
	this->addItemToPool(ItemChance::create(SpecialAdd::create(), ItemChance::Probability::Artifact));
	this->addItemToPool(ItemChance::create(SpecialSub::create(), ItemChance::Probability::Artifact));
	this->addItemToPool(ItemChance::create(SpecialAnd::create(), ItemChance::Probability::Artifact));
	this->addItemToPool(ItemChance::create(SpecialXor::create(), ItemChance::Probability::Artifact));
	this->addItemToPool(ItemChance::create(SpecialOr::create(), ItemChance::Probability::Artifact));
	this->addItemToPool(ItemChance::create(SpecialShr::create(), ItemChance::Probability::Artifact));
	this->addItemToPool(ItemChance::create(SpecialShl::create(), ItemChance::Probability::Artifact));
}

CardPoolTier8::~CardPoolTier8()
{
}
