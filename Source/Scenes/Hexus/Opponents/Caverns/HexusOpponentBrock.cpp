#include "HexusOpponentBrock.h"

const std::string HexusOpponentBrock::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_BROCK";
HexusOpponentBrock* HexusOpponentBrock::instance = nullptr;

HexusOpponentBrock* HexusOpponentBrock::getInstance()
{
	if (HexusOpponentBrock::instance == nullptr)
	{
		HexusOpponentBrock::instance = new HexusOpponentBrock();
	}

	return HexusOpponentBrock::instance;
}

HexusOpponentBrock::HexusOpponentBrock() : HexusOpponentData(
	EntityResources::Platformer_Environment_Caverns_Npcs_Brock_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameCaverns,
	1.0f,
	Vec2(-32.0f, -64.0f),
	Vec2(-16.0f, -32.0f),
	HexusOpponentBrock::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Shadow,
	HexusOpponentData::generateReward(0.4f),
	HexusOpponentData::generateDeck(25, 0.4f,
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

HexusOpponentBrock::~HexusOpponentBrock()
{
}
