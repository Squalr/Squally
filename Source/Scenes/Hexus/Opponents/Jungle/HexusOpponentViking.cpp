#include "HexusOpponentViking.h"

const std::string HexusOpponentViking::StringKeyOpponentName = "Squally_Npc_Names_Viking";
HexusOpponentViking* HexusOpponentViking::instance = nullptr;

HexusOpponentViking* HexusOpponentViking::getInstance()
{
	if (HexusOpponentViking::instance == nullptr)
	{
		HexusOpponentViking::instance = new HexusOpponentViking();
	}

	return HexusOpponentViking::instance;
}

HexusOpponentViking::HexusOpponentViking() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Jungle_Enemies_Viking_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameJungle,
	1.0f,
	Vec2(-48.0f, -48.0f),
	Vec2(-16.0f, -48.0f),
	HexusOpponentViking::StringKeyOpponentName,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Earth,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalXor),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalAnd),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalOr),
	},
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Binary3),
		CardList::getInstance()->cardListByName->at(CardKeys::Binary3),
		CardList::getInstance()->cardListByName->at(CardKeys::Binary4),
		CardList::getInstance()->cardListByName->at(CardKeys::Binary5),
		CardList::getInstance()->cardListByName->at(CardKeys::Binary6),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal0),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal1),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal3),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal4),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal5),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal6),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex3),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex3),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex4),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex5),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex6),
		CardList::getInstance()->cardListByName->at(CardKeys::Subtraction),
		CardList::getInstance()->cardListByName->at(CardKeys::Flip3),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalOr),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalXor),
		CardList::getInstance()->cardListByName->at(CardKeys::ShiftLeft),
		CardList::getInstance()->cardListByName->at(CardKeys::ShiftRight),
	})
{
}

HexusOpponentViking::~HexusOpponentViking()
{
}
