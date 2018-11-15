#include "HexusOpponentSarude.h"

const std::string HexusOpponentSarude::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_SARUDE";
HexusOpponentSarude* HexusOpponentSarude::instance = nullptr;

HexusOpponentSarude* HexusOpponentSarude::getInstance()
{
	if (HexusOpponentSarude::instance == nullptr)
	{
		HexusOpponentSarude::instance = new HexusOpponentSarude();
	}

	return HexusOpponentSarude::instance;
}

HexusOpponentSarude::HexusOpponentSarude() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Caverns_Npcs_Sarude_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameCaverns,
	1.0f,
	Vec2(-32.0f, -64.0f),
	Vec2(-24.0f, -32.0f),
	HexusOpponentSarude::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Shadow,
	HexusOpponentData::generateReward(0.505f),
	HexusOpponentData::generateDeck(25, 0.505f,
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

HexusOpponentSarude::~HexusOpponentSarude()
{
}
