#include "HexusOpponentAgnes.h"

const std::string HexusOpponentAgnes::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_AGNES";
HexusOpponentAgnes* HexusOpponentAgnes::instance = nullptr;

HexusOpponentAgnes* HexusOpponentAgnes::getInstance()
{
	if (HexusOpponentAgnes::instance == nullptr)
	{
		HexusOpponentAgnes::instance = new HexusOpponentAgnes();
	}

	return HexusOpponentAgnes::instance;
}

HexusOpponentAgnes::HexusOpponentAgnes() : HexusOpponentData(
	EntityResources::Environment_Castle_Enemies_Agnes_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameCastle,
	0.9f,
	Vec2(-32.0f, -16.0f),
	Vec2(-32.0f, 16.0f),
	HexusOpponentAgnes::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Shadow,
	HexusOpponentData::generateReward(0.62f),
	HexusOpponentData::generateDeck(25, 0.62f,
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

HexusOpponentAgnes::~HexusOpponentAgnes()
{
}
