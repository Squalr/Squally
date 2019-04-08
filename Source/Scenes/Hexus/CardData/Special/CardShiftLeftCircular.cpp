#include "CardShiftLeftCircular.h"

#include "Scenes/Hexus/CardData/CardKeys.h"

#include "Resources/HexusResources.h"

CardShiftLeftCircular::CardShiftLeftCircular() : CardData(HexusResources::Special_ShiftLeftCircular, CardKeys::ShiftLeftCircular, CardType::Special_ROL, 0)
{
}

CardShiftLeftCircular::~CardShiftLeftCircular()
{
}
