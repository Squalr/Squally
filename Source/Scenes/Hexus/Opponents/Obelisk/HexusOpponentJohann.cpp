#include "HexusOpponentJohann.h"

const std::string HexusOpponentJohann::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_JOHANN";
HexusOpponentJohann* HexusOpponentJohann::instance = nullptr;

HexusOpponentJohann* HexusOpponentJohann::getInstance()
{
	if (HexusOpponentJohann::instance == nullptr)
	{
		HexusOpponentJohann::instance = new HexusOpponentJohann();
	}

	return HexusOpponentJohann::instance;
}

HexusOpponentJohann::HexusOpponentJohann() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Obelisk_Npcs_Johann_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameObelisk,
	1.0f,
	Vec2(-48.0f, -64.0f),
	Vec2(-16.0f, -48.0f),
	HexusOpponentJohann::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.85f),
	HexusOpponentData::generateDeck(25, 0.85f,
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

HexusOpponentJohann::~HexusOpponentJohann()
{
}
