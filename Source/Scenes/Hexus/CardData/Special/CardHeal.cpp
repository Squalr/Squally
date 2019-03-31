#include "CardHeal.h"

#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/HexusResources.h"

CardHeal::CardHeal() : CardData(HexusResources::Special_HealthPotion, CardKeys::Heal, CardType::Special_HEAL, 0)
{
}

CardHeal::~CardHeal()
{
}
