#include "HexusCard.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

HexusCard::HexusCard(CurrencyInventory* cost, ItemMeta itemMeta) : super(cost, ItemStats(), itemMeta)
{
}

HexusCard::~HexusCard()
{
}