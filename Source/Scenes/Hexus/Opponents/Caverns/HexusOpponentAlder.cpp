#include "HexusOpponentAlder.h"

const std::string HexusOpponentAlder::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_ALDER";
HexusOpponentAlder* HexusOpponentAlder::instance = nullptr;

HexusOpponentAlder* HexusOpponentAlder::getInstance()
{
	if (HexusOpponentAlder::instance == nullptr)
	{
		HexusOpponentAlder::instance = new HexusOpponentAlder();
	}

	return HexusOpponentAlder::instance;
}

HexusOpponentAlder::HexusOpponentAlder() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Caverns_Npcs_Alder_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameCaverns,
	0.85f,
	Vec2(-48.0f, -64.0f),
	Vec2(-16.0f, -32.0f),
	HexusOpponentAlder::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Shadow,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal3),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal2),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal1),
	},
	HexusOpponentData::generateDeck(25, 0.5f,
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

HexusOpponentAlder::~HexusOpponentAlder()
{
}
