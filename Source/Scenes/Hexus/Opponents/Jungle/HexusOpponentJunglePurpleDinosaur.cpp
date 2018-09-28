#include "HexusOpponentJunglePurpleDinosaur.h"

const std::string HexusOpponentJunglePurpleDinosaur::StringKeyOpponentName = "Squally_Npc_Names_Jungle_Purple_Dinosaur";
HexusOpponentJunglePurpleDinosaur* HexusOpponentJunglePurpleDinosaur::instance = nullptr;

HexusOpponentJunglePurpleDinosaur* HexusOpponentJunglePurpleDinosaur::getInstance()
{
	if (HexusOpponentJunglePurpleDinosaur::instance == nullptr)
	{
		HexusOpponentJunglePurpleDinosaur::instance = new HexusOpponentJunglePurpleDinosaur();
	}

	return HexusOpponentJunglePurpleDinosaur::instance;
}

HexusOpponentJunglePurpleDinosaur::HexusOpponentJunglePurpleDinosaur() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Jungle_Enemies_PurpleDinosaur_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameJungle,
	1.0f,
	Vec2(-48.0f, -64.0f),
	Vec2(0.0f, 0.0f),
	HexusOpponentJunglePurpleDinosaur::StringKeyOpponentName,
	Card::CardStyle::Earth,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Binary0),
		CardList::getInstance()->cardListByName->at(CardKeys::Binary1),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal0),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal1),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal1),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal2),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal3),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal3),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal4),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex0),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex1),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex2),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex2),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex3),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex3),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex4),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex4),
		CardList::getInstance()->cardListByName->at(CardKeys::Addition),
		CardList::getInstance()->cardListByName->at(CardKeys::Addition),
		CardList::getInstance()->cardListByName->at(CardKeys::Subtraction),
		CardList::getInstance()->cardListByName->at(CardKeys::Subtraction),
		CardList::getInstance()->cardListByName->at(CardKeys::ShiftLeft),
		CardList::getInstance()->cardListByName->at(CardKeys::ShiftRight),
	})
{
}

HexusOpponentJunglePurpleDinosaur::~HexusOpponentJunglePurpleDinosaur()
{
}
