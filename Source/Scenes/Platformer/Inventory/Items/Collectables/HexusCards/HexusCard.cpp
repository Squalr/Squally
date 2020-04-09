#include "HexusCard.h"

#include "Resources/ItemResources.h"

using namespace cocos2d;

HexusCard::HexusCard(CurrencyInventory* cost, ItemMeta itemMeta) : super(cost, ItemStats(), itemMeta)
{
}

HexusCard::~HexusCard()
{
}