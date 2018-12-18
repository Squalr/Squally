#include "HexusOpponentJasper.h"

const std::string HexusOpponentJasper::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_JASPER";
HexusOpponentJasper* HexusOpponentJasper::instance = nullptr;

HexusOpponentJasper* HexusOpponentJasper::getInstance()
{
	if (HexusOpponentJasper::instance == nullptr)
	{
		HexusOpponentJasper::instance = new HexusOpponentJasper();
	}

	return HexusOpponentJasper::instance;
}

HexusOpponentJasper::HexusOpponentJasper() : HexusOpponentData(
	EntityResources::Npcs_Jasper_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameCaverns,
	1.0f,
	Vec2(-48.0f, -64.0f),
	Vec2(-16.0f, -32.0f),
	HexusOpponentJasper::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Shadow,
	HexusOpponentData::generateReward(0.46f),
	HexusOpponentData::generateDeck(25, 0.46f,
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

HexusOpponentJasper::~HexusOpponentJasper()
{
}
