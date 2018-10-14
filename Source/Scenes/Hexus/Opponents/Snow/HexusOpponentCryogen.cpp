#include "HexusOpponentCryogen.h"

const std::string HexusOpponentCryogen::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_CRYOGEN";
HexusOpponentCryogen* HexusOpponentCryogen::instance = nullptr;

HexusOpponentCryogen* HexusOpponentCryogen::getInstance()
{
	if (HexusOpponentCryogen::instance == nullptr)
	{
		HexusOpponentCryogen::instance = new HexusOpponentCryogen();
	}

	return HexusOpponentCryogen::instance;
}

HexusOpponentCryogen::HexusOpponentCryogen() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Snow_Enemies_Cryogen_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameIceCaps,
	0.85f,
	Vec2(-48.0f, -48.0f),
	Vec2(-64.0f, -48.0f),
	HexusOpponentCryogen::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Earth,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal4),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalAnd),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex4),
	},
	HexusOpponentData::generateDeck(25, 0, 11, 0.33f, 0.33f,
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

HexusOpponentCryogen::~HexusOpponentCryogen()
{
}
