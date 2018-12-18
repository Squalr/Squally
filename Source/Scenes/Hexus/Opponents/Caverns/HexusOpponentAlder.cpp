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
	EntityResources::Npcs_SeaSharpCaverns_Alder_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameCaverns,
	0.85f,
	Vec2(-48.0f, -64.0f),
	Vec2(-16.0f, -32.0f),
	HexusOpponentAlder::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Shadow,
	HexusOpponentData::generateReward(0.43f),
	HexusOpponentData::generateDeck(25, 0.43f,
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
