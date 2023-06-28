#include "HexusCard.h"

#include "Resources/ItemResources.h"

using namespace cocos2d;

HexusCard::HexusCard(CurrencyInventory* cost, ItemMeta itemMeta) : super(cost, ItemStats(), itemMeta)
{
}

HexusCard::~HexusCard()
{
}

int HexusCard::TuneCost(int attack)
{
    return 4 + int(std::round(double(attack) * 2.5));
}