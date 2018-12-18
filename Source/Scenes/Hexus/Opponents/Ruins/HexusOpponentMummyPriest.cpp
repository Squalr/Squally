#include "HexusOpponentMummyPriest.h"

const std::string HexusOpponentMummyPriest::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_MUMMY_PRIEST";
HexusOpponentMummyPriest* HexusOpponentMummyPriest::instance = nullptr;

HexusOpponentMummyPriest* HexusOpponentMummyPriest::getInstance()
{
	if (HexusOpponentMummyPriest::instance == nullptr)
	{
		HexusOpponentMummyPriest::instance = new HexusOpponentMummyPriest();
	}

	return HexusOpponentMummyPriest::instance;
}

HexusOpponentMummyPriest::HexusOpponentMummyPriest() : HexusOpponentData(
	EntityResources::Enemies_UnderflowRuins_MummyPriest_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameRuins,
	0.85f,
	Vec2(-32.0f, -64.0f),
	Vec2(-16.0f, -64.0f),
	HexusOpponentMummyPriest::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.255f),
	HexusOpponentData::generateDeck(25, 0.255f,
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

HexusOpponentMummyPriest::~HexusOpponentMummyPriest()
{
}
