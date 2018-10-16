#include "HexusOpponentPrincessOpal.h"

const std::string HexusOpponentPrincessOpal::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_PRINCESS_OPAL";
HexusOpponentPrincessOpal* HexusOpponentPrincessOpal::instance = nullptr;

HexusOpponentPrincessOpal* HexusOpponentPrincessOpal::getInstance()
{
	if (HexusOpponentPrincessOpal::instance == nullptr)
	{
		HexusOpponentPrincessOpal::instance = new HexusOpponentPrincessOpal();
	}

	return HexusOpponentPrincessOpal::instance;
}

HexusOpponentPrincessOpal::HexusOpponentPrincessOpal() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Castle_Npcs_PrincessOpal_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameCastle,
	1.0f,
	Vec2(-32.0f, -48.0f),
	Vec2(-16.0f, -40.0f),
	HexusOpponentPrincessOpal::OpponentSaveKey,
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

HexusOpponentPrincessOpal::~HexusOpponentPrincessOpal()
{
}
