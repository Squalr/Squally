#include "HexusOpponentKingZul.h"

const std::string HexusOpponentKingZul::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_KING_ZUL";
HexusOpponentKingZul* HexusOpponentKingZul::instance = nullptr;

HexusOpponentKingZul* HexusOpponentKingZul::getInstance()
{
	if (HexusOpponentKingZul::instance == nullptr)
	{
		HexusOpponentKingZul::instance = new HexusOpponentKingZul();
	}

	return HexusOpponentKingZul::instance;
}

HexusOpponentKingZul::HexusOpponentKingZul() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Obelisk_Enemies_KingZul_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameObelisk,
	1.0f,
	Vec2(-48.0f, -64.0f),
	Vec2(-16.0f, -64.0f),
	HexusOpponentKingZul::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.92f),
	HexusOpponentData::generateDeck(25, 0.92f,
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

HexusOpponentKingZul::~HexusOpponentKingZul()
{
}
