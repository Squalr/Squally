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
	EntityResources::Enemies_Cyrogen_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameIceCaps,
	0.85f,
	Vec2(-48.0f, -48.0f),
	Vec2(-64.0f, -48.0f),
	HexusOpponentCryogen::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.72f),
	HexusOpponentData::generateDeck(25, 0.72f,
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
