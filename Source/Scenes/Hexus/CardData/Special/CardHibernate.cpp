#include "CardHibernate.h"

#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/HexusResources.h"

CardHibernate::CardHibernate() : CardData(HexusResources::Special_Hibernate, CardKeys::Hibernate, CardType::Special_HIBERNATE, 0)
{
}

CardHibernate::~CardHibernate()
{
}
