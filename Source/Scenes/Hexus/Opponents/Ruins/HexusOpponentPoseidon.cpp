#include "HexusOpponentPoseidon.h"

const std::string HexusOpponentPoseidon::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_POSEIDON";
HexusOpponentPoseidon* HexusOpponentPoseidon::instance = nullptr;

HexusOpponentPoseidon* HexusOpponentPoseidon::getInstance()
{
	if (HexusOpponentPoseidon::instance == nullptr)
	{
		HexusOpponentPoseidon::instance = new HexusOpponentPoseidon();
	}

	return HexusOpponentPoseidon::instance;
}

HexusOpponentPoseidon::HexusOpponentPoseidon() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Ruins_Npcs_Poseidon_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameRuins,
	1.0f,
	Vec2(-48.0f, -48.0f),
	Vec2(-16.0f, -32.0f),
	HexusOpponentPoseidon::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Earth,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal4),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalAnd),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex4),
	},
	HexusOpponentData::generateDeck(25, 0.285f,
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

HexusOpponentPoseidon::~HexusOpponentPoseidon()
{
}
