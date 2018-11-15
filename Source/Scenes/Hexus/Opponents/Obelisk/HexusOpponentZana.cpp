#include "HexusOpponentZana.h"

const std::string HexusOpponentZana::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_ZANA";
HexusOpponentZana* HexusOpponentZana::instance = nullptr;

HexusOpponentZana* HexusOpponentZana::getInstance()
{
	if (HexusOpponentZana::instance == nullptr)
	{
		HexusOpponentZana::instance = new HexusOpponentZana();
	}

	return HexusOpponentZana::instance;
}

HexusOpponentZana::HexusOpponentZana() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Obelisk_Npcs_Zana_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameObelisk,
	1.0f,
	Vec2(-48.0f, -64.0f),
	Vec2(-16.0f, -40.0f),
	HexusOpponentZana::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.88f),
	HexusOpponentData::generateDeck(25, 0.88f,
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

HexusOpponentZana::~HexusOpponentZana()
{
}
