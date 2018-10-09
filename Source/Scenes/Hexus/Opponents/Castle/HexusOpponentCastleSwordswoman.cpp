#include "HexusOpponentCastleSwordswoman.h"

const std::string HexusOpponentCastleSwordswoman::StringKeyOpponentName = "Squally_Npc_Names_Castle_Swordswoman";
HexusOpponentCastleSwordswoman* HexusOpponentCastleSwordswoman::instance = nullptr;

HexusOpponentCastleSwordswoman* HexusOpponentCastleSwordswoman::getInstance()
{
	if (HexusOpponentCastleSwordswoman::instance == nullptr)
	{
		HexusOpponentCastleSwordswoman::instance = new HexusOpponentCastleSwordswoman();
	}

	return HexusOpponentCastleSwordswoman::instance;
}

HexusOpponentCastleSwordswoman::HexusOpponentCastleSwordswoman() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Castle_Npcs_Swordswoman_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameRuins,
	0.8f,
	Vec2(-48.0f, -48.0f),
	Vec2(-16.0f, -32.0f),
	HexusOpponentCastleSwordswoman::StringKeyOpponentName,
	Card::CardStyle::Earth,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal4),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalAnd),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex4),
	},
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Binary0),
		CardList::getInstance()->cardListByName->at(CardKeys::Binary1),
		CardList::getInstance()->cardListByName->at(CardKeys::Binary3),
		CardList::getInstance()->cardListByName->at(CardKeys::Binary3),
		CardList::getInstance()->cardListByName->at(CardKeys::Binary4),
		CardList::getInstance()->cardListByName->at(CardKeys::Binary4),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal0),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal1),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal3),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal3),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal4),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal5),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex0),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex2),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex3),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex3),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex4),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex5),
		CardList::getInstance()->cardListByName->at(CardKeys::Addition),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalAnd),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalOr),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalXor),
		CardList::getInstance()->cardListByName->at(CardKeys::ShiftLeft),
		CardList::getInstance()->cardListByName->at(CardKeys::ShiftRight),
	})
{
}

HexusOpponentCastleSwordswoman::~HexusOpponentCastleSwordswoman()
{
}
