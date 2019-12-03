#include "CardShopPoolTier1.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Scenes/Platformer/Inventory/Items/Collectables/HexusCards/HexusCards.h"

using namespace cocos2d;

CardShopPoolTier1* CardShopPoolTier1::create()
{
	CardShopPoolTier1* instance = new CardShopPoolTier1();

	instance->autorelease();

	return instance;
}

CardShopPoolTier1::CardShopPoolTier1() : super(ValueMap(), "card-shop-tool-t1", SampleMethod::Guarantee, 2, 3)
{
	this->addItemToPool(ItemChance::create(Binary0::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(Decimal0::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(Hex0::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(Binary1::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(Decimal1::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(Hex1::create(), ItemChance::Probability::Guaranteed));
}

CardShopPoolTier1::~CardShopPoolTier1()
{
}
