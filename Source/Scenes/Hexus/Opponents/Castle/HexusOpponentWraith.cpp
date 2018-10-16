#include "HexusOpponentWraith.h"

const std::string HexusOpponentWraith::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_WRAITH";
HexusOpponentWraith* HexusOpponentWraith::instance = nullptr;

HexusOpponentWraith* HexusOpponentWraith::getInstance()
{
	if (HexusOpponentWraith::instance == nullptr)
	{
		HexusOpponentWraith::instance = new HexusOpponentWraith();
	}

	return HexusOpponentWraith::instance;
}

HexusOpponentWraith::HexusOpponentWraith() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Castle_Enemies_Wraith_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameCastle,
	0.7f,
	Vec2(-32.0f, -32.0f),
	Vec2(-16.0f, -32.0f),
	HexusOpponentWraith::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Shadow,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal3),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal2),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal1),
	},
	HexusOpponentData::generateDeck(25, 0.6f,
		{
			CardList::getInstance()->cardListByName->at(CardKeys::Addition),
			CardList::getInstance()->cardListByName->at(CardKeys::LogicalAnd),
			CardList::getInstance()->cardListByName->at(CardKeys::LogicalOr),
			CardList::getInstance()->cardListByName->at(CardKeys::LogicalXor),
			CardList::getInstance()->cardListByName->at(CardKeys::ShiftLeft),
			CardList::getInstance()->cardListByName->at(CardKeys::ShiftRight),
		})
	)
{
}

HexusOpponentWraith::~HexusOpponentWraith()
{
}
